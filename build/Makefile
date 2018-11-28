.PHONY: clean distclean all

# Define functions to check undefined variables
check_defined = $(if $(value $(strip $1)),,\
$(error $1 undefined !))

$(call check_defined, CONF_BUILD_VM)
$(call check_defined, CONF_INITRAMFS_FINAL)
$(call check_defined, CONF_LINUX_BZIMAGE)
$(call check_defined, CONF_LINUX_SYSTEMMAP)
$(call check_defined, CONF_MODULE_C)

BUILD_VM=$(CONF_BUILD_VM)
INITRAMFS=$(CONF_INITRAMFS_FINAL)
BZIMAGE=$(CONF_LINUX_BZIMAGE)
SYSTEM_MAP=$(CONF_LINUX_SYSTEMMAP)
MODULE_C=$(CONF_MODULE_C)

all:
	cp $(INITRAMFS) $(BUILD_VM)
	cp $(BZIMAGE) $(BUILD_VM)
	cp $(SYSTEM_MAP) $(BUILD_VM)
	cp $(MODULE_C) $(BUILD_VM)

clean:
	rm -rf $(BUILD_VM)
	rm -f *~

distclean: clean
