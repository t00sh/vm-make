.PHONY: all clean distclean help

-include Makefile.inc

all:
	make -C $(CONF_LINUX_BUILD)
	make -C $(CONF_BUSYBOX_BUILD)
	make -C $(CONF_MODULE_BUILD)
	make -C $(CONF_INITRAMFS_BUILD)
	make -C $(CONF_BUILD)

clean:
	make -C $(CONF_MODULE_BUILD) clean ; \
	make -C $(CONF_LINUX_BUILD) clean ; \
	make -C $(CONF_BUSYBOX_BUILD) clean ; \
	make -C $(CONF_INITRAMFS_BUILD) clean ; \
	make -C $(CONF_BUILD) clean
	rm -f *~

distclean:
	make -C $(CONF_MODULE_BUILD) distclean ; \
	make -C $(CONF_LINUX_BUILD) distclean ; \
	make -C $(CONF_BUSYBOX_BUILD) distclean ; \
	make -C $(CONF_INITRAMFS_BUILD) distclean ; \
	make -C $(CONF_BUILD) distclean
	rm -f *~
help:
	@echo "make <all>      Build the VM"
	@echo "make clean      Reset some files to start rebuild"
	@echo "make distclean  Remove all generated files"
	@echo "make help       Print this help"
