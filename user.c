#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
char write_bytes[]="Embl";

int main()
{
	int fd,len,wr;

	fd = open("./node1",O_WRONLY);
	if(fd == -1)
	printf("error in opening file\n");
	else
	printf("file open sucessfully\n");
	len = strlen(write_bytes);
	wr = write(fd,write_bytes,len);
	if(wr == 4)
	printf("data write successfully\n");
	else
	printf("error in writing\n");		
	//close(fd);
	return 0;

}
     /* #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <unistd.h>

       int mknod(const char *pathname, mode_t mode, dev_t dev);

       #include <fcntl.h>          //  Definition of AT_* constants 
       #include <sys/stat.h>

       int mknodat(int dirfd, const char *pathname, mode_t mode, dev_t dev);*/