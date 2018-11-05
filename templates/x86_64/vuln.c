#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Simon Duret");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("A simple Linux Kernel Module to learn SLUB overflows");

#define VULN_DEVICE_NAME "vuln_ipc"
#define VULN_MAX_CHANNELS 2048
#define VULN_MAX_BUFFER_SIZE 2048

#define VULN_IOCTL_NEW   0xdead0001
#define VULN_IOCTL_DEL   0xdead0002
#define VULN_IOCTL_READ  0xdead0003
#define VULN_IOCTL_WRITE 0xdead0004

/* Structure IPC
   Allow processus to share buffers called "channel" identified
   by an ID. */
struct vuln_ipc_channel {
  unsigned long id;
  char *buffer;
  size_t size;
  void (*destroy)(int);
};

/* Structures for IOCTL arguments messages (new, del, read, write) */
struct vuln_ipc_new_arg {
  unsigned long id;
  size_t size;
};

struct vuln_ipc_del_arg {
  unsigned long id;
};

struct vuln_ipc_read_arg {
  unsigned long id;
  size_t size;
  char *buffer;
};

struct vuln_ipc_write_arg {
  unsigned long id;
  size_t size;
  const char *buffer;
};

/* Globales variables : array of channels + mutex to avoid race conditions */
static struct vuln_ipc_channel *g_channels[VULN_MAX_CHANNELS] = {NULL};
static struct mutex g_mutex;

static int vuln_open(struct inode *, struct file *);
static int vuln_release(struct inode *, struct file *);
static long vuln_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static const struct file_operations g_fops = {
  .owner = THIS_MODULE,
  .open = vuln_open,
  .release = vuln_release,
  .unlocked_ioctl = vuln_ioctl,
};

static struct miscdevice g_device = {
  .minor = MISC_DYNAMIC_MINOR,
  .name = VULN_DEVICE_NAME,
  .fops = &g_fops,
  .mode = 0666
};

/*
 * Called during a DEL command. (free memory of the channel)
 */
static void vuln_destroy_channel(int idx) {
  if (g_channels[idx] != NULL) {
    kfree(g_channels[idx]->buffer);
    kfree(g_channels[idx]);
    g_channels[idx] = NULL;
  }
}

/*
 * Open the device.
 */
static int vuln_open(struct inode *inode, struct file *file) {
  return 0;
}

/*
 * Close the device.
 */
static int vuln_release(struct inode *inode, struct file *file) {
  return 0;
}

/*
 * Used to find a channel by its id. Return index of channel or -1 if
 * not found.
 */
static int vuln_find_channel(unsigned long id) {
  int i;

  for (i = 0; i < VULN_MAX_CHANNELS; i++) {
    if (g_channels[i] != NULL) {
      if (g_channels[i]->id == id)
        return i;
    }
  }
  return -1;
}

/*
 * Allocate a new channel using kmalloc. And initialize all fields.
 */
static int vuln_alloc_channel(unsigned long id, size_t size) {
  int i, err;

  for (i = 0; i < VULN_MAX_CHANNELS; i++) {
    /* Find free slot... */
    if (g_channels[i] == NULL) {

      /* Allocate a channel */
      g_channels[i] = kmalloc(sizeof(struct vuln_ipc_channel), GFP_KERNEL);
      if (IS_ERR(g_channels[i]))
        return PTR_ERR(g_channels[i]);

      /* Allocate the internal buffer */
      g_channels[i]->buffer = kzalloc(size, GFP_KERNEL);
      if (IS_ERR(g_channels[i]->buffer)) {
        err = PTR_ERR(g_channels[i]->buffer);
        kfree(g_channels[i]);
        g_channels[i] = NULL;
        return err;
      }

      /* Initialize fields of the structure */
      g_channels[i]->size = size;
      g_channels[i]->destroy = vuln_destroy_channel;
      g_channels[i]->id = id;

      printk(KERN_INFO "vuln: created %d\n", i);
      return 0;
    }
  }
  return -ENOMEM;
}

/*
 * Called during VULN_IOCTL_NEW command :
 * allocate a new channel identified by an ID.
 */
static int vuln_ioctl_new(void __user *argp) {

  struct vuln_ipc_new_arg arg_struct;
  int err;

  if (copy_from_user(&arg_struct, argp, sizeof arg_struct))
    return -EFAULT;

  if (arg_struct.size > VULN_MAX_BUFFER_SIZE)
    return -EFAULT;

  if (vuln_find_channel(arg_struct.id) >= 0)
    return -ENOMEM;

  if ((err = vuln_alloc_channel(arg_struct.id, arg_struct.size)) < 0)
    return err;
  return 0;
}

/*
 * Called during VULN_IOCTL_DEL command :
 * destroy a channel.
 */
static int vuln_ioctl_del(void __user *argp) {
  struct vuln_ipc_del_arg arg_struct;
  int idx;

  if (copy_from_user(&arg_struct, argp, sizeof arg_struct))
    return -EFAULT;

  if ((idx = vuln_find_channel(arg_struct.id)) < 0)
    return -EINVAL;

  g_channels[idx]->destroy(idx);
  printk(KERN_INFO "vuln: destroyed %d\n", idx);
  return 0;
}

/*
 * Called during VULN_IOCTL_WRITE :
 * write to channel buffer.
 */
static int vuln_ioctl_write(void __user *argp) {
  struct vuln_ipc_write_arg arg_struct;
  int idx;

  if (copy_from_user(&arg_struct, argp, sizeof arg_struct))
    return -EFAULT;

  if ((idx = vuln_find_channel(arg_struct.id)) < 0)
    return -EINVAL;

  if (arg_struct.size > g_channels[idx]->size + sizeof(unsigned long))
    return -EINVAL;

  if (copy_from_user(g_channels[idx]->buffer,
                     arg_struct.buffer, arg_struct.size))
    return -EFAULT;
  printk(KERN_INFO "vuln: write %zu bytes to %d\n", arg_struct.size, idx);
  return 0;
}

/*
 * Called during VULN_IOCTL_READ :
 * read from a channel.
 */
static int vuln_ioctl_read(void __user *argp) {
  struct vuln_ipc_read_arg arg_struct;
  size_t size;
  int idx;

  if (copy_from_user(&arg_struct, argp, sizeof arg_struct))
    return -EFAULT;

  if ((idx = vuln_find_channel(arg_struct.id)) < 0)
    return -EINVAL;

  size = min(arg_struct.size, g_channels[idx]->size);

  if (copy_to_user(arg_struct.buffer, g_channels[idx]->buffer, size))
    return -EFAULT;
  printk(KERN_INFO "vuln: read %zu bytes from %d\n", size, idx);
  return 0;
}

/*
 * Handle ioctl calls.
 */
static long vuln_ioctl(struct file *file, unsigned int cmd,
                       unsigned long arg) {

  void __user *argp = (void __user *) arg;
  int err = 0;

  if (!mutex_trylock(&g_mutex))
    return -EAGAIN;

  switch (cmd) {
  case VULN_IOCTL_NEW:
    err = vuln_ioctl_new(argp);
    break;
  case VULN_IOCTL_DEL:
    err = vuln_ioctl_del(argp);
    break;
  case VULN_IOCTL_WRITE:
    err = vuln_ioctl_write(argp);
    break;
  case VULN_IOCTL_READ:
    err = vuln_ioctl_read(argp);
    break;
  default:
    err = -EINVAL;
  }

  mutex_unlock(&g_mutex);
  return err;
}

/*
 * Initialisation function.
 */
static int __init vuln_init(void) {
  int err;

  mutex_init(&g_mutex);

  /* Create the device */
  err = misc_register(&g_device);
  if (err < 0) {
    printk(KERN_ALERT "vuln: Failed to misc_register\n");
    return err;
  }

  printk(KERN_INFO "vuln: module initialized\n");
  return 0;
}

/*
 * Cleanup function.
 */
static void __exit vuln_exit(void) {
  misc_deregister(&g_device);
  printk(KERN_INFO "vuln: module exited\n");
}

module_init(vuln_init);
module_exit(vuln_exit);
