#include <linux/fs.h>
#include <linux/cdev.h>

#define MY_MAJOR       511
#define MY_MAX_MINORS  1

struct my_device_data {
    struct cdev cdev;
	size_t size;
	char* buffer;
};

typedef int my_ioctl_data;

struct my_device_data devs[MY_MAX_MINORS];

static int my_open(struct inode *inode, struct file *file)
{
	struct my_device_data *my_data =
			             container_of(inode->i_cdev, struct my_device_data, cdev);

	/* validate access to device */
	file->private_data = my_data;

	/* initialize device */
	pr_info("File opened");
	
	return 0;
}

static int my_release(struct inode *inode, struct file *file) {pr_info("File released"); return 0;}

static ssize_t my_read(struct file *file, char __user *user_buffer, size_t size, loff_t *offset)
{
    struct my_device_data *my_data = (struct my_device_data *) file->private_data;

	ssize_t len = min(my_data->size - *offset, size);

    pr_info("Offset: %lld, size: %ld, len: %d\n", *offset, size, len); 

    if (len <= 0) {
        pr_info("Non-positive length is not allowed");
		return 0;
	}

	/* read data from my_data->buffer to user buffer*/
    if (copy_to_user(user_buffer, my_data->buffer + *offset, len))
        return -EFAULT;

	*offset+=len;
	pr_info("Something read");
    
	return len;
}

static ssize_t my_write(struct file *file, const char __user *user_buffer,
                    size_t size, loff_t * offset)
{;
	struct my_device_data *my_data = (struct my_device_data *) file->private_data;
    ssize_t len = min(my_data->size - *offset, size);

    if (len <= 0) {
        pr_info("Non-positive length is not allowed");
		return 0;
	}

    /* read data from user buffer to my_data->buffer */
    if (copy_from_user(my_data->buffer + *offset, user_buffer, len))
        return -EFAULT;
    
	pr_info("Offset: %lld, size: %ld, len: %d\n", *offset, size, len); 

    *offset += len;

	pr_info("Something written");
    return len;
}

#include <asm/ioctl.h>

#define MY_IOCTL_IN _IOC(_IOC_WRITE, 'k', 1, sizeof(my_ioctl_data))

static long my_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
    struct my_device_data *my_data =
         (struct my_device_data*) file->private_data;
    my_ioctl_data mid;

    switch(cmd) {
    case MY_IOCTL_IN:
        if( copy_from_user(&mid, (my_ioctl_data *) arg,
                           sizeof(my_ioctl_data)) )
            return -EFAULT;

        /* process data and execute command */

        break;
    default:
        return -ENOTTY;
    }

    return 0;
}

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
    int i;

    for(i = 0; i < MY_MAX_MINORS; i++) {
        /* release devs[i] fields */
        cdev_del(&devs[i].cdev);
    }
    unregister_chrdev_region(MKDEV(MY_MAJOR, 0), MY_MAX_MINORS);
	pr_info("exited");
}

 MODULE_LICENSE("GPL");
