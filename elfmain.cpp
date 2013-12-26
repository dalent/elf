#include"elflib.h"
#include<stdio.h>

struct ELF_t *elf;
int main(int argc , char** argv)
{
	if(argc != 2)
	{
		ERROR_RET("no file", -1);
	}

	elf = new ELF_t;

	if(open_elf(elf, argv[1]) != 0)
	{
		ERROR_RET("open failed", -1);
	}

}
