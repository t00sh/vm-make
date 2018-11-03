-include ../Makefile.inc

obj-m += vuln.o

all:
	make -C $(CONF_LINUX_HEADERS) M=$(shell realpath ./) modules
clean:
	rm -f *~
	make -C $(CONF_LINUX_HEADERS) M=$(shell realpath ./) clean

distclean: clean
