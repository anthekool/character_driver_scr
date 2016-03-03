#include "scull.h"
#include "header.h"
#include "declaration.h"
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

extern ssize_t  write_dev(struct file *, const char *, size_t , loff_t *);


struct scull_qset *first;
ssize_t write_dev(struct file *fops, const char *buf, size_t count, loff_t *f_pos)
{
	struct scull_dev *ldev;
	int counter=0,i=0,no_of_qset_item=0,no_of_quantum,j=0;
	int llqset,llquantum,datasize;
	long could_not_copy,length_write=0;
	size_t lcount;
	
	/*read outside memory pointing  I/O address */
	ldev = fops->private_data; 
	llqset = ldev->qset;
	llquantum = ldev->quantum;
	datasize = (llqset*llquantum);
	/*calculate number of qset item means no of qset structure*/
	no_of_qset_item = count /datasize;
	if(count%datasize)
	no_of_qset_item++;
	/*calculate number of quantum*/
	no_of_quantum = (count/llquantum);
	if(count %llquantum)
	no_of_quantum++;
	
	lcount = count;
	
	printk(KERN_INFO "Enter in write file with quantum no %d\n",no_of_quantum);
	
	
	for(i = 0; i < no_of_qset_item; i++)
	{
		
		printk(KERN_INFO "qset item no is = %d\n",no_of_qset_item);
		if(i == 0)
		{

			/*First qset item to be initialized*/
			 ldev->qset_struc  = (struct scull_qset *)kmalloc(sizeof(struct scull_qset),GFP_KERNEL);
			first = ldev->qset_struc;
			if(!first)
			{
				
				printk(KERN_INFO "Error in first qset item memory allocation\n");
				return 0;
			}
			
			else
			{
				memset(first,0,sizeof(struct scull_qset));
				printk(KERN_INFO "Error in first qset item memory allocation\n");
				
			
			}


			first->data = (void **)kmalloc(sizeof(char *)*ldev->qset,GFP_KERNEL);
			if(!first->data)
			{
				printk(KERN_INFO "Error in data memory allocation\n");
				return 0;	
			}
			else
			{
				memset(first->data,0,sizeof(char *)*ldev->qset);

				
			}
		}
					/*qset item to be initialized one by one */
		else

		{
			//printk(KERN_INFO "present in second file %d",no_of_qset_struc);
			first->next = (struct scull_qset *)kmalloc(sizeof(struct scull_qset),GFP_KERNEL);
						
			if(first->next)
			{
			
				printk(KERN_INFO "next qset crtead successfully\n");
				//first = first->next;
				memset(first->next,0,sizeof(struct scull_qset));
				first = first->next;
				//return 0;
			}
			else
			{
				printk(KERN_INFO "Error in second item memory allocation\n");
				return 0;
			}
		
		
			first->data = (void **)kmalloc(sizeof(char *)*ldev->qset,GFP_KERNEL);
			if(!first->data)
			{
				printk(KERN_INFO "Error in data memory allocation\n");
				return 0;	
			}
			else
			{
				memset(first->data,0,sizeof(char *)*ldev->qset);
			}
	
	
		}
	}
	
	//return 0;	
	first = ldev->qset_struc ;
	//return 0;
	for(counter = 0; counter< no_of_quantum; counter++)
	{
		first->data[j]= (void **)kmalloc(ldev->quantum,GFP_KERNEL);
		if(!first->data[j])
		{

			printk(KERN_INFO "Error in quantum allocation\n");
			return 0;
		}
		else
		{
			printk(KERN_INFO "quantum allocated successfully\n");
			memset(first->data[j],0,sizeof(ldev->quantum));
		}	
		
		if(lcount >= llquantum)
			llquantum = ldev->quantum;
		else
			llquantum = lcount;
		could_not_copy = copy_from_user(first->data[j],&buf[length_write],llquantum);
		printk(KERN_INFO "data value is %s\n",(char *)first->data[j]);
		if(j == ldev->qset-1)
		{
			j = 0;
			if(first->next)
			first = first->next;


		}
		else
		j++;
		
		length_write = length_write - could_not_copy+llquantum;
		lcount = lcount - llquantum;

				
	}
	

	if(length_write == count)
	{
		printk(KERN_INFO "copy from user successfully %ld \n",length_write);///(char *)(ldev->qset_struc->data[0]));////,could_not_copy);
	}

	printk(KERN_INFO "copy from user %ld %d  %ld\n",length_write,no_of_quantum,lcount);///(char *)(ldev->qset_struc->data[0]));////,could_not_copy);


	return (length_write);


}
