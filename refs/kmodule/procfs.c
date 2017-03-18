/*
 * procfs.c - create a "file" in /proc, use the file_operation way
 *            to manage the file.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define PROC_ENTRY_FILENAME  "buffer2k"
#define PROCFS_MAX_SIZE      2048

static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;
static struct proc_dir_entry *our_proc_file;

static ssize_t procfs_read(struct file *filp, char *buffer,
			   size_t length, loff_t *offset)
{
	static int finished = 0;

	if (finished) {
		printk(KERN_INFO "procfs_read: END\n");
		finished = 0;
		return 0;
	}

	finished = 1;

	/*
	 * we use put_to_user to copy the string from the kernel's
	 * memory segment to the memory segment of the process
	 * that called use. get_from_user, BTW, is used for the
	 * reverse.
	 */
	if (copy_to_user(buffer, procfs_buffer, procfs_buffer_size))
		return -EFAULT;

	printk(KERN_INFO "procfs_read: read %lu bytes\n", procfs_buffer_size);

	return procfs_buffer_size;
}

static ssize_t procfs_write(struct file *file, const char *buffer,
			    size_t len, loff_t *off)
{
	if (len > PROCFS_MAX_SIZE)
		procfs_buffer_size = PROCFS_MAX_SIZE;
	else
		procfs_buffer_size = len;

	if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size))
		return -EFAULT;

	printk(KERN_INFO "procfs_write: write %lu bytes\n", procfs_buffer_size);

	return procfs_buffer_size;
}

/*
 * This function decides whether to allow an operation
 * (return zero) or not allow it (return a non-zero
 * which indicates why it is not allowed).
 *
 * The operation can be one of the following values:
 * 0 - Execute (run the "file" - meaningless in our case)
 * 2 - Write (input to the kernel module)
 * 4 - Read (output from the kernel module)
 *
 * This is the real function that checks file permissions.
 * The permissions returned by ls -l are for referece only,
 * and can be overridden here.
 */
static int module_permission(struct inode *inode, int op, struct nameidata *foo)
{
	/*
	 * We allow everybody to read from our module, but only root
	 * (uid 0) may write to it
	 */
	if (op == 4 || (op == 2 && current->euid) == 0)
		return 0;

	/*
	 * If it's anything else, access is denied
	 */
	return -EACCES;
}

/*
 * The file is opened - we don't really care about that,
 * but it does mean we need to increment the module's
 * reference count.
 */
int procfs_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);
	return 0;
}

/*
 * The file is closed - again, interesting only because of
 * the reference count.
 */
int procfs_close(struct inode *inode, struct file *file)
{
	module_get(THIS_MODULE);
	return 0;
}

static struct file_operations fops = {
	.read    = procfs_read,
	.write   = procfs_write,
	.open    = procfs_ open,
	.release = procfs_close,
};

/*
 * Inode operations for our proc file. We need it so we'll have
 * some place to specify the file operations structure we want
 * to use, and the function we use for permissions. It's also
 * possible to specify functions to be called for anything else
 * which could be done to an inode (although we don't bother,
 * we just put NULL).
 */
static struct inode_operations iops = {
	.permission = module_permission,
};

int init_module(void)
{
	our_proc_file = create_proc_entry(PROC_ENTRY_FILENAME, 0644, NULL);

	if (our_proc_file == NULL) {
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
		       PROC_ENTRY_FILENAME);
		return -ENOMEM;
	}

	our_proc_file->owner     = THIS_MODULE;
	our_proc_file->proc_iops = &iops;
	our_proc_file->proc_fops = &fops;
	our_proc_file->mode      = S_IFREG | S_IRUGO | S_IWUSR;
	our_proc_file->uid       = 0;
	our_proc_file->gid       = 0;
	our_proc_file->size      = 80;

	printk(KERN_INFO "/proc/%s created\n", PROC_ENTRY_FILENAME);

	return 0;
}

void cleanup_module(void)
{
	remove_proc_entry(PROC_ENTRY_FILENAME, &proc_root);

	printk(KERN_INFO "/proc/%s removed\n", PROC_ENTRY_FILENAME);
}
