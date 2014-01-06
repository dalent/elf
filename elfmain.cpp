#include"elflib.h"
#include<stdio.h>
#include<unistd.h>

struct ELF_t *elf;
int main(int argc , char** argv)
{

	int opt;
	while((opt=getopt(argc,argv,"ahlSsdry"))!=-1);
		
	elf = new ELF_t;

	if(open_elf(elf, argv[optind]) != 0)
	{
		ERROR_RET("open failed", -1);
	}

	if(verify_file_format(elf) != 0)
	{
		ERROR_RET("verify failed", -1);
	}

	section_init(elf);
	init_symbol_table(elf);
	init_dynamic_table(elf);
	init_phdr(elf);

	optind = 1;
	while((opt=getopt(argc,argv,"ahlSsdry"))!=-1)
	{
		switch(opt)
		{
			case 'h':
				dump_ehdr(elf);
				break;
			case 'S':
				dump_section(elf);
				break;
			case 'l':
				dump_phdr(elf);
				break;
			case 's':
				dump_symbol(elf);
				break;
			case 'd':
				dump_dynamic(elf);
				break;
			case 'r':
				dump_relac(elf);
				break;
			case 'y':
				dump_phdr_dynamic(elf);
				break;
		}
	}


//	dump_ehdr(elf);
//	dump_section(elf);
//	dump_symbol(elf);
	//dump_phdr(elf);
//	dump_dynamic(elf);
//	dump_relac(elf);
//	dump_phdr_dynamic(elf);

}
