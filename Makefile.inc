# Name of the Linux TAR archive
CONF_LINUX_ARCHIVE=linux-4.18.16.tar.xz

# URL of Linux archive
CONF_LINUX_URL=https://cdn.kernel.org/pub/linux/kernel/v4.x/$(CONF_LINUX_ARCHIVE)

# Name of the Busybox TAR archive
CONF_BUSYBOX_ARCHIVE=busybox-1.29.3.tar.bz2

# URL of Busybox archive
CONF_BUSYBOX_URL=https://busybox.net/downloads/$(CONF_BUSYBOX_ARCHIVE)

# Number of CPUs for compilation
CONF_CPUS=3

# Root directory
CONF_ROOT=$(PWD)

# Linux build directory
CONF_LINUX_BUILD=$(CONF_ROOT)/linux
CONF_LINUX_BZIMAGE=$(CONF_LINUX_BUILD)/bzImage
CONF_LINUX_HEADERS=$(CONF_LINUX_BUILD)/build
CONF_LINUX_SYSTEMMAP=$(CONF_LINUX_BUILD)/System.map

# Busybox build directory
CONF_BUSYBOX_BUILD=$(CONF_ROOT)/busybox
CONF_BUSYBOX_DONE=$(CONF_BUSYBOX_BUILD)/build/.done
CONF_BUSYBOX_INSTALL=$(CONF_BUSYBOX_BUILD)/build/_install

# Initramfs build directory
CONF_INITRAMFS_BUILD=$(CONF_ROOT)/initramfs
CONF_INITRAMFS_FINAL=$(CONF_INITRAMFS_BUILD)/initramfs.cpio.gz

# Module build directory
CONF_MODULE_BUILD=$(CONF_ROOT)/module
CONF_MODULE_KO=$(CONF_MODULE_BUILD)/vuln.ko

# Build directory
CONF_BUILD=$(CONF_ROOT)/build
