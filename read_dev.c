#include "scull.h"
#include "header.h"
#include "declaration.h"
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

extern ssize_t  read_dev(struct file *,char *, size_t , loff_t *);
long could_read_not_copy,final_nof_byte=0,length_write =0;



ssize_t read_dev(struct file *fops, char *buf, size_t count, loff_t *f_pos)
{

	struct scull_dev *ldev;
	int no_of_quantum,llquantum,q_pos,q_pos_rest;//,j;
	int counter,llqset,datasize,j =0;
	long no_of_byte=0,g_count;
	loff_t *fpos;
	int no_qset_struc;

	g_count = count;
	ldev = fops->private_data;
	*f_pos = fops->f_pos;
 	fpos = f_pos;
	g_count = count - *fpos;
	
	llqset = ldev->qset;
	llquantum = ldev->quantum;
	datasize = llqset*llquantum;

	q_pos = (*fpos / ldev->quantum);
	q_pos_rest = (*fpos % ldev->quantum);

	/*no of qset item*/
	no_qset_struc = count/datasize;
	if(count%datasize)
	no_qset_struc++;

	/*no of quantum*/
	no_of_quantum = count/llquantum;
	if(count % llquantum)
	no_of_quantum++;
	
	printk(KERN_INFO "file position = %d %d\n",(int)fops->f_pos,(int)*fpos);


	printk(KERN_INFO "persent in read file with count value %ld\n",g_count);
	if(!ldev->qset_struc)

	{
		printk(KERN_INFO "error in allocating reading file\n");

	}
//	ldev->qset_struc = (struct scull_qset *)kmalloc(sizeof(struct scull_qset),GFP_KERNEL);
//	lqset->data = (void **)kmalloc(sizeof(char *)*ldev->qset,GFP_KERNEL);
//	memset(lqset->data,0,sizeof(char *)*ldev->qset);
//	lqset->data[0]= (void **)kmalloc(ldev->quantum,GFP_KERNEL);
	
	j = q_pos;
	printk(KERN_INFO "no of qset structure %d\n",no_qset_struc);

	for(counter = q_pos;counter < no_of_quantum; counter++)
//	while(ldev->qset_struc->data[j]+q_pos_rest != NULL)
{



		if(g_count < llquantum)
		{

			llquantum = g_count;

			printk(KERN_INFO "counter value is less than quantum\n");
		} 

		could_read_not_copy = copy_to_user(&buf[no_of_byte],ldev->qset_struc->data[j]+q_pos_rest,llquantum- q_pos_rest);

		no_of_byte = no_of_byte + llquantum - could_read_not_copy- q_pos_rest;
		g_count = g_count - llquantum + q_pos_rest;
		*fpos = *fpos + llquantum- q_pos_rest -could_read_not_copy;
		printk(KERN_INFO "no of byte value %ld %s\n",no_of_byte,(char *)ldev->qset_struc->data[j]+q_pos_rest);
		q_pos_rest = 0;
		if(j == ldev->qset-1)
		{
			j = 0;			
			if(ldev->qset_struc)
			ldev->qset_struc = ldev->qset_struc->next;
			else
			printk(KERN_INFO "error in next  qset location\n");
				
			
		
		}
		else
			j++;


	}




	printk(KERN_INFO "file position = %d %d\n",(int)fops->f_pos,(int)*fpos);
	printk(KERN_INFO "copy from read user %s %ld %d %ld %ld%d%d\n",buf,length_write,no_of_quantum,g_count,no_of_byte,ldev->quantum,ldev->qset);

	printk(KERN_INFO "read string %s\n",buf);

	return (no_of_byte);



}
