.PHONY: clean distclean all

# Define functions to check undefined variables
check_defined = $(if $(value $(strip $1)),,\
$(error $1 undefined !))

$(call check_defined, CONF_BUILD)
$(call check_defined, CONF_INITRAMFS_FINAL)
$(call check_defined, CONF_LINUX_BZIMAGE)
$(call check_defined, CONF_LINUX_SYSTEMMAP)
$(call check_defined, CONF_MODULE_C)

BUILD=$(CONF_BUILD)
INITRAMFS=$(CONF_INITRAMFS_FINAL)
BZIMAGE=$(CONF_LINUX_BZIMAGE)
SYSTEM_MAP=$(CONF_LINUX_SYSTEMMAP)
MODULE_C=$(CONF_MODULE_C)

BUILD_DIR=$(BUILD)/build

all: clean
	mkdir $(BUILD_DIR)
	cp $(INITRAMFS) $(BUILD_DIR)
	cp $(BZIMAGE) $(BUILD_DIR)
	cp $(SYSTEM_MAP) $(BUILD_DIR)
	cp $(MODULE_C) $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -f *~

distclean: clean
