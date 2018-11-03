.PHONY: clean distclean

-include ../Makefile.inc

URL=$(CONF_LINUX_URL)
BUILD=$(CONF_LINUX_BUILD)/build
SRC=$(CONF_LINUX_BUILD)/src
CONFIG=$(CONF_LINUX_BUILD)/config
BZIMAGE=$(CONF_LINUX_BZIMAGE)
SYSTEM_MAP=$(CONF_LINUX_SYSTEMMAP)
ARCHIVE=$(CONF_LINUX_BUILD)/$(CONF_LINUX_ARCHIVE)
SRC_DONE=$(SRC)/.done

all: $(BZIMAGE)

$(BZIMAGE): $(SRC_DONE)
	mkdir -p $(BUILD)
	make -C $(SRC) O=$(BUILD) allnoconfig
	cp $(CONFIG) $(BUILD)/.config
	make -C $(BUILD) menuconfig
	make -C $(BUILD) -j$(CONF_CPUS)
	cp $(BUILD)/System.map $(SYSTEM_MAP)
	cp $(BUILD)/arch/x86/boot/bzImage $@

$(SRC_DONE): $(ARCHIVE)
	mkdir -p $(SRC)
	tar --strip 1 -xvf $(ARCHIVE) -C $(SRC)/
	touch $@

$(ARCHIVE):
	wget $(URL) -O $(ARCHIVE)

clean:
	rm -rf $(BZIMAGE)

distclean:
	rm -rf $(SYSTEM_MAP) $(ARCHIVE) $(BUILD) $(BZIMAGE) $(SRC) *~
