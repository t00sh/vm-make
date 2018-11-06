.PHONY: clean distclean all

# Define functions to check undefined variables
check_defined = $(if $(value $(strip $1)),,\
$(error $1 undefined !))

$(call check_defined, CONF_INITRAMFS_BUILD)
$(call check_defined, CONF_INITRAMFS_FINAL)
$(call check_defined, CONF_BUSYBOX_DONE)
$(call check_defined, CONF_MODULE_KO)
$(call check_defined, CONF_INITRAMFS_BUILD)
$(call check_defined, CONF_BUSYBOX_INSTALL)
$(call check_defined, CONF_BUSYBOX_INSTALL)
$(call check_defined, CONF_LINUX_SYSTEMMAP)

BUILD=$(CONF_INITRAMFS_BUILD)/build
FS=$(CONF_INITRAMFS_BUILD)/fs
INITRAMFS=$(CONF_INITRAMFS_FINAL)
BUSYBOX_DONE=$(CONF_BUSYBOX_DONE)
MODULE_KO=$(CONF_MODULE_KO)
BUSYBOX_INSTALL=$(CONF_BUSYBOX_INSTALL)
SYSTEMMAP=$(CONF_LINUX_SYSTEMMAP)

all: $(BUSYBOX_DONE) $(MODULE_KO)
	mkdir -p $(BUILD)
	cd $(BUILD) && mkdir -p bin sbin etc proc sys usr/bin usr/sbin
	cp -a $(BUSYBOX_INSTALL)/* $(BUILD)/
	cp -a $(MODULE_KO) $(BUILD)/
	cp -a $(FS)/* $(BUILD)/
	cp -a $(SYSTEMMAP) $(BUILD)/
	cd $(BUILD) && find . -print0 | cpio --null -ov --format=newc \
		| gzip -9 > $(INITRAMFS)

clean:
	rm -rf $(INITRAMFS) $(BUILD) $(FS) *~

distclean: clean
