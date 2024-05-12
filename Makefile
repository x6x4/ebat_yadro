DIRS= cdev virt_file

KDIR=/lib/modules/`uname -r`/build

kbuild:
	$(foreach mdir, $(DIRS), \
		$(MAKE) -C $(KDIR) M=`pwd`/$(mdir) modules;)
clean:
	$(foreach mdir, $(DIRS), \
		$(MAKE) -C $(KDIR) M=`pwd`/$(mdir) clean;)
