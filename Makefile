MODULE_NAME = my_cdev_driver
SOURCE_FILE = my_cdev

obj-m += $(MODULE_NAME).o
$(MODULE_NAME)-objs := $(SOURCE_FILE).o
 
MAKEFILE_DIR=$(CURDIR)

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(MAKEFILE_DIR) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(MAKEFILE_DIR) clean 
