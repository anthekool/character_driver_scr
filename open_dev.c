#include "header.h"
#include "declaration.h"
#include "scull.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/fcntl.h>

extern ssize_t read_dev(struct file *, char *, size_t , loff_t *);
extern int scull_trim(struct scull_dev *);
extern int open_dev(struct inode *,struct file *);
extern int close_dev(struct inode *,struct file *);
ssize_t write_dev(struct file *, const char *, size_t , loff_t *);


struct file_operations foper =   
{
		read: 	read_dev,
		write:	 write_dev,
//		read:    read_dev,
          	open: 	open_dev,
         	release: close_dev     
 
   };


int open_dev(struct inode *inode,struct file *fops)
{
	struct scull_dev *ldev;
	
	ldev = dev;
	printk(KERN_INFO "open device\n");
	if(ldev == NULL)
	printk(KERN_INFO "error in device open\n");
	ldev = container_of(inode->i_cdev,struct scull_dev,c_dev);
	if(ldev == NULL)
	printk(KERN_INFO "error in device I/O memory allocation\n");
	else
	printk(KERN_INFO "memory is pointing outside kernal\n");
	if((fops->f_flags & O_ACCMODE) == O_WRONLY)
	{
		scull_trim(ldev);
	}
	fops->private_data = ldev;
	
	return 0;


}

int close_dev(struct inode *inode,struct file *fops)
{

	printk(KERN_INFO "close device\n");
	return 0;

}

int scull_trim(struct scull_dev *temp)
{

	printk(KERN_INFO "triming done\n");
	return 0;

}



