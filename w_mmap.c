#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct student
{
	int id;
	char name[128];
	int age;
};
int main()
{
	struct student stu;
	stu.id = 1;
	memcpy(stu.name,"Lilei",sizeof("Lilei"));
	stu.age = 18;
	struct student *p;
	int fd;
	fd = open("wuqinyuan",O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(fd < 0)
		{
			perror("open file");
			exit(1);
		}
	int ftrunc_ret = ftruncate(fd,sizeof(stu));
	if(ftrunc_ret == -1)
		{
			perror("trunc error");
			exit(1);
		}
	off_t lseek_ret = lseek(fd, 0, SEEK_END);
	p = (struct student *)mmap(NULL,lseek_ret, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
		{
			perror("mmap error");
			exit(1);
		}
	close(fd);
	while(1)
		{
			memcpy(p,&stu,sizeof(stu));
			stu.id++;
			sleep(1);
		}
	munmap(p,lseek_ret);

	return 0;
}