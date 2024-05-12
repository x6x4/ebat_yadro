#include "my_cdev.h"

struct my_device_data devs[MY_MAX_MINORS];

const struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .read = my_read,
    .write = my_write,
    .release = my_release,
    .unlocked_ioctl = my_ioctl
};

char data = 0;

int init_module(void)
{
    int err = register_chrdev_region(MKDEV(MY_MAJOR, 0), MY_MAX_MINORS,
                                 "my_device_driver");
    if (err != 0) {
        /* report error */
        return err;
    }

    for (int i = 0; i < MY_MAX_MINORS; i++) {
        /* initialize devs[i] fields */
        cdev_init(&devs[i].cdev, &my_fops);
        cdev_add(&devs[i].cdev, MKDEV(MY_MAJOR, i), 1);
		devs[i].buffer = &data;
		devs[i].size = 32;
    }

    pr_info("inited");
	return 0;	
}

void cleanup_module(void)
{
    for(int i = 0; i < MY_MAX_MINORS; i++) {
        /* release devs[i] fields */
        cdev_del(&devs[i].cdev);
    }
    unregister_chrdev_region(MKDEV(MY_MAJOR, 0), MY_MAX_MINORS);
	pr_info("exited");
}

