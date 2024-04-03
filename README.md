# MY CHARACTER DEVICE DRIVER

This is kernel module for custom character device driver. Run
```
sudo mknod /dev/my_cdev c 511 0 && sudo chmod 666 /dev/my_cdev
```  
to create a device file which the driver would use. Its major number is 511, minor is zero. (Changing rights is obligatory.)  

For building a driver, run `make` in repository directory.  

Load module with command 
```
sudo insmod ./my_cdev_driver.ko
```
And unload it with
```
sudo rmmod ./my_cdev_driver.ko
```  
# USAGE

Use `cat` for read and `echo "string">/dev/my_cdev` for write. 
>__WARNING:__ don't echo more then 31 symbol. It'll hang your computer, so you have to restart it!  

The write happens in **overwriting** mode.

# PROJECT STRUCTURE
.  
├── Makefile - contains obvious targets `kbuild` and `clean`  
├── Kbuild - declares the module-specific build rules  
├── init_my_cdev.c - provide `init_module` and `cleanup_module` functions  
├── my_cdev.* - the main library, implements necessary device driver routines  
└── README.md - the file you read  

