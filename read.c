#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>


char read_bytes[1024];
int main()
{
	int fd,len,wr,rd;

	fd = open("./link",O_RDONLY);
	if(fd == -1)
	printf("error in opening file\n");
	else
	printf("file open sucessfully\n");
	len = strlen(read_bytes);

	lseek(fd,10,SEEK_SET);
	len = 268;
	rd = read(fd,read_bytes,len);
	if(rd == len-10)
	printf("read successfully\n");
	else
	printf("error in reading file\n");
	
	printf("read num of byte is %d \n",rd);
	printf("read string is = %s %d\n",read_bytes,fd);	
	close(fd);
	return 0;

}
     
