#include<stdio.h>
#include<elf.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		printf("argu not 2");
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	Elf64_Ehdr elf_head;
	read(fd,&elf_head, sizeof elf_head); 
	printf("indent: %s", elf_head.e_ident);
	return 0;
}
