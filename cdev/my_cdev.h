#include <linux/fs.h>
#include <linux/cdev.h>

#define MY_MAJOR       511
#define MY_MAX_MINORS  1

struct my_device_data {
	struct cdev cdev;
	size_t size;
	char* buffer;
};


int my_open(struct inode *inode, struct file *file);
int my_release(struct inode *inode, struct file *file);
ssize_t my_read(struct file *file, char __user *user_buffer, size_t size, loff_t *offset);
ssize_t my_write(struct file *file, const char __user *user_buffer,
                    size_t size, loff_t * offset);
long my_ioctl (struct file *file, unsigned int cmd, unsigned long arg);


MODULE_DESCRIPTION("My kernel module");
MODULE_AUTHOR("Me");
MODULE_LICENSE("GPL");
