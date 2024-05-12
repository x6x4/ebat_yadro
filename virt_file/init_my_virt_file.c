#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/seq_file.h>

MODULE_AUTHOR("Me");
MODULE_LICENSE("Dual BSD/GPL");

static int ct_seq_show(struct seq_file *s, void *v)
{
 	//loff_t *spos = (loff_t *) v;
 	//seq_printf(s, "%Ld\n", *spos);
 	seq_printf(s, "hui");
	return 0;
}

static int ct_open(struct inode *inode, struct file *file)
{
 	return single_open(file, &ct_seq_show, NULL);
};

//  since kernel 5.6
static const struct proc_ops ct_file_ops = {
 	.proc_open    = ct_open,
 	.proc_read    = seq_read,
 	.proc_lseek  = seq_lseek,
 	.proc_release = single_release
};

static int ct_init(void)
{
 	struct proc_dir_entry *entry;
 	entry = proc_create_single("my_virt", 0, NULL, &ct_seq_show);
 	return 0;
}

static void ct_exit(void)
{
 	remove_proc_entry("my_virt", NULL);
}

module_init(ct_init);
module_exit(ct_exit);

