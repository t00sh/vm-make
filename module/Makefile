ifndef CONF_LINUX_HEADERS
$(error CONF_LINUX_HEADERS undefined)
endif

export ARCH=$(CONF_LINUX_ARCH)
export CROSS_COMPILE=$(CONF_CROSS_COMPILE_PREFIX)

obj-m += vuln.o

all:
	make -C $(CONF_LINUX_HEADERS) M=$(shell realpath ./) modules
clean:
	rm -f *~
	make -C $(CONF_LINUX_HEADERS) M=$(shell realpath ./) clean || true

distclean: clean
	rm -f vuln.c
