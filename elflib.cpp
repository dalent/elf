#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>
#include"elflib.h"

int get_file_size(int fd)
{
	struct stat st;
	if(fstat(fd, &st) < 0)
		return 0;

	return st.st_size;
}
int open_elf(struct ELF_t *elf, char* filename)
{
	int fd ;
	int filesize;
	char *data;
	if(!filename)
	{
		printf("file name is null\n");
		return -1;
	}
	if((fd = open(filename, O_RDONLY)) < 0)
	{
		printf("file open failed!\n");
		return -1;
	}
	
	filesize = get_file_size(fd);

	if(filesize <= 0)
	{
		close(fd);
		return -1;
	}
	
	data = (char*)mmap(0, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
	if(!data)
	{
		close(fd);
		return -1;
	}

	elf->name = strdup(filename);
	elf->fd = fd;
	elf->size = filesize;
	elf->data = data;

	return 0;
}

void free_elf(ELF_t * elf)
{
	if(!elf)
		return ;

	if(elf->name)
		free(elf->name);

	elf->name = NULL;

	if(elf->fd && elf->data)
	{
		munmap(elf->data, elf->size);
		close(elf->fd);
	}

	elf->data = NULL;
	free(elf);
}

char* elf_offset(ELF_t* elf, int offset)
{
	if(!elf && elf->data && elf->size < offset)
		return NULL;

	return elf->data + offset;
}
