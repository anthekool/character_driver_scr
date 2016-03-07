#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
char write_bytes[]="8888888888888888888888888888888888888889889898989891111111111111111111111111111111111111111111199999999999109999999999999666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666667777777777777777777777777777777777777777777777000000";


int main()
{
	int fd,len,wr,rd;

	fd = open("./link",O_WRONLY);
	if(fd == -1)
	printf("error in opening file\n");
	else
	printf("file open sucessfully\n");
	len = strlen(write_bytes);
	wr = write(fd,write_bytes,len);
	if(wr == len)
	printf("data write successfully\n");
	else
	printf("error in writing\n");
	
	printf("write no of byte is = %d\n",wr);	
	
	close(fd);
	return 0;

}
     
