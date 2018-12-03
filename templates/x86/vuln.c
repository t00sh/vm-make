#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Simon Duret");
MODULE_DESCRIPTION("Test module");
MODULE_VERSION("1.0");

/*
 * Initialisation function.
 */
static int __init vuln_init(void) {
  printk(KERN_INFO "vuln: Module initialized\n");
  return 0;
}

/*
 * Cleanup function.
 */
static void __exit vuln_exit(void) {
  printk(KERN_INFO "vuln: Module exited\n");
}

module_init(vuln_init);
module_exit(vuln_exit);
