.PHONY: clean distclean

# Define functions to check undefined variables
check_defined = $(if $(value $(strip $1)),,\
$(error $1 undefined !))

$(call check_defined, CONF_LINUX_BUILD)
$(call check_defined, CONF_LINUX_BZIMAGE)
$(call check_defined, CONF_LINUX_SYSTEMMAP)
$(call check_defined, CONF_LINUX_ARCHIVE)
$(call check_defined, CONF_LINUX_ARCH)
$(call check_defined, CONF_LINUX_IMG)

# General setup
BUILD=$(CONF_LINUX_BUILD)/build
SRC=$(CONF_LINUX_BUILD)/src
CONFIG=$(CONF_LINUX_BUILD)/config
BZIMAGE=$(CONF_LINUX_BZIMAGE)
SYSTEM_MAP=$(CONF_LINUX_SYSTEMMAP)
ARCHIVE=$(CONF_LINUX_BUILD)/$(CONF_LINUX_ARCHIVE)
SRC_DONE=$(SRC)/.done

# Architecture setup
export ARCH=$(CONF_LINUX_ARCH)
export CROSS_COMPILE=$(CONF_CROSS_COMPILE_PREFIX)

all: $(BZIMAGE)

$(BZIMAGE): $(SRC_DONE)
	mkdir -p $(BUILD)
	make -C $(SRC) O=$(BUILD) allnoconfig
	cp $(CONFIG) $(BUILD)/.config
	make -C $(BUILD) menuconfig
	make -C $(BUILD) -j$(CONF_CPUS)
	cp $(BUILD)/System.map $(SYSTEM_MAP)
	cp $(BUILD)/arch/$(ARCH)/boot/$(CONF_LINUX_IMG) $@

$(SRC_DONE): $(ARCHIVE)
	mkdir -p $(SRC)
	tar --strip 1 -xvf $(ARCHIVE) -C $(SRC)/
	touch $@

$(ARCHIVE):
	if test -z "$(CONF_LINUX_URL)"; then \
	  cp ../$(CONF_TEMPLATE)/$(CONF_LINUX_ARCHIVE) $(ARCHIVE); \
	else \
	  wget $(CONF_LINUX_URL) -O $(ARCHIVE); \
	fi;

clean:
	rm -rf $(BZIMAGE) $(CONFIG)

distclean:
	rm -rf $(SYSTEM_MAP) $(ARCHIVE) $(BUILD) $(SRC) *~
	rm -rf $(BZIMAGE) $(CONFIG)
