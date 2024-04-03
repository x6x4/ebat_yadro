KDIR=/lib/modules/`uname -r`/build

kbuild:
	$(MAKE) -C $(KDIR) M=`pwd` modules

clean:
	make -C $(KDIR) M=`pwd` clean 
