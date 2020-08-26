#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct student{
	int id;
	char name[128];
	int age;
};
int main()
{
	//struct student stu;
	struct student *p;
	int fd;
	fd = open("wuqinyuan",O_RDONLY);
	if(fd < 0)
	{
		perror("open file");
		exit(1);
	}

	off_t lseek_ret = lseek(fd, 0, SEEK_END);
	p = (struct student *)mmap(NULL,lseek_ret, PROT_READ, MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap error");
		exit(1);
	}
	close(fd);
	while(1)
	{
		printf("id = %d,name is %s, age is %d\n",p->id,p->name,p->age);
		sleep(1);
		
	}
	munmap(p,lseek_ret);
	return 0;
}