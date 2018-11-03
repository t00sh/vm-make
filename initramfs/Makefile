.PHONY: clean distclean all

-include ../Makefile.inc

BUILD=$(CONF_INITRAMFS_BUILD)/build
FS=$(CONF_INITRAMFS_BUILD)/fs
INITRAMFS=$(CONF_INITRAMFS_FINAL)

all: $(CONF_BUSYBOX_DONE) $(CONF_MODULE_KO)
	mkdir -p $(BUILD)
	cd $(BUILD) && mkdir -p bin sbin etc proc sys usr/bin usr/sbin
	cp -a $(CONF_BUSYBOX_INSTALL)/* $(BUILD)/
	cp -a $(CONF_MODULE_KO) $(BUILD)/
	cp -a $(FS)/* $(BUILD)/
	cp -a $(CONF_LINUX_SYSTEMMAP) $(BUILD)/
	cd $(BUILD) && find . -print0 | cpio --null -ov --format=newc \
		| gzip -9 > $(INITRAMFS)

clean:
	rm -rf $(INITRAMFS)

distclean:
	rm -rf $(BUILD) $(INITRAMFS) *~
