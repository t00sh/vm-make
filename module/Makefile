ifndef CONF_LINUX_HEADERS
$(error CONF_LINUX_HEADERS undefined)
endif

obj-m += vuln.o

all:
	make -C $(CONF_LINUX_HEADERS) M=$(shell realpath ./) modules
clean:
	rm -f *~
	make -C $(CONF_LINUX_HEADERS) M=$(shell realpath ./) clean || true

distclean: clean
	rm vuln.c
