#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>

int main()
{//有亲缘关系的mmap
	int fd;
	char *p;
	fd = open("testmmap",O_CREAT|O_RDWR|O_TRUNC,0644);
	if(fd < 0)
	{
		perror("fd");
		exit(1);
	}
	
	/*lseek(fd, 10, SEEK_END);//和ftruncate效果一样
	write(fd, '\0', 1);
	*/
	
	int trunc_ret = ftruncate(fd, 20); //需要写权限
	if(trunc_ret == -1)
	{
		perror("truncate error");
		exit(1);
	}
	int len = lseek(fd, 0, SEEK_END);//用lseek返回值确定文件大小
	//如果传结构体,则p = (struct student *)mmap();
	p = (char *)mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap error");
		exit(1);
	}
	close(fd);//创建完内存映射后即可关闭fd
	strcpy(p, "hello world");//memcpy，strncpy
	printf("mmap is %s\n",p);
	int ret = munmap(p,len);//删除mmap
	if(ret == -1)
	{
		perror("munmap error");
		exit(1);
	}
	
	return 0;
}
