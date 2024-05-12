# MY CHARACTER DEVICE DRIVER

This is kernel module for custom character device driver. Run
```
sudo mknod /dev/my_cdev c 511 0 && sudo chmod 666 /dev/my_cdev
```  
to create a device file which the driver would use. Its major number is 511, minor is zero. (Changing rights is obligatory.)  

# USAGE

Use `cat` for read and `echo "string">/dev/my_cdev` for write. 
>__WARNING:__ don't echo more then 31 symbol. It'll hang your computer, so you have to restart it!  

The write happens in **overwriting** mode.  
