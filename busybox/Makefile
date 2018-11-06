.PHONY: clean distclean

# Define functions to check undefined variables
check_defined = $(if $(value $(strip $1)),,\
$(error $1 undefined !))

$(call check_defined, CONF_BUSYBOX_URL)
$(call check_defined, CONF_BUSYBOX_BUILD)
$(call check_defined, CONF_BUSYBOX_ARCHIVE)

URL=$(CONF_BUSYBOX_URL)
BUILD=$(CONF_BUSYBOX_BUILD)/build
SRC=$(CONF_BUSYBOX_BUILD)/src
ARCHIVE=$(CONF_BUSYBOX_BUILD)/$(CONF_BUSYBOX_ARCHIVE)
CONFIG=$(CONF_BUSYBOX_BUILD)/config
SRC_DONE=$(SRC)/.done
BUILD_DONE=$(CONF_BUSYBOX_DONE)

all: $(BUILD_DONE)

$(ARCHIVE):
	wget $(URL) -O $@

$(SRC_DONE): $(ARCHIVE)
	mkdir -p $(SRC)
	tar --strip 1 -jxvf $(ARCHIVE) -C $(SRC)
	touch $@

$(BUILD_DONE): $(SRC_DONE)
	mkdir -p $(BUILD)
	make -C $(SRC) O=$(BUILD) defconfig
	cp $(CONFIG) $(BUILD)/.config
	make -C $(BUILD) menuconfig
	make -C $(BUILD) -j$(CONF_CPUS)
	make -C $(BUILD) install
	touch $@


clean:
	rm -rf $(BUILD_DONE) $(CONFIG)

distclean:
	rm -rf $(BUILD) $(SRC) $(ARCHIVE) *~
	rm -rf $(BUILD_DONE) $(CONFIG)
