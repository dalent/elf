#include"elflib.h"
#include<stdio.h>
#include<unistd.h>
#include<getopt.h>


struct ELF_t *elf;
int main(int argc , char** argv)
{

	struct option long_options[]={
	
		{"ehdr",         no_argument,0,'e'},
		{"shdr",         no_argument,0,'S'},
		{"phdr",         no_argument,0,'p'},
		{"symbol",       no_argument,0,'s'},
		{"dyn-sym",      no_argument,0, 0},//i don't want give it a abbreviate
		{"dynamic",      no_argument,0, 'd'},
		{"reloc",        no_argument,0,'r'},
		{"help",         no_argument,0,'h'},
		{0,              0,          0, 0 }
	};
	int opt;
	while((opt=getopt_long(argc,argv,"eSpsdr",long_options, NULL))!=-1);

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
	
	while((opt=getopt_long(argc,argv,"eSpsdrh",long_options, NULL))!=-1)
	{
		switch(opt)
		{
			case 0:// it means dyn_symbol
				dump_dynamic(elf);

			case 'e':
				dump_ehdr(elf);
				break;
			case 'S':
				dump_section(elf);
				break;
			case 'p':
				dump_phdr(elf);
				break;
			case 's':
				dump_symbol(elf);
				break;
			case 'd':
				dump_phdr_dynamic(elf);
				break;
			case 'r':
				dump_relac(elf);
				break;
			case 'h':
				{
					for(int i = 0; i < sizeof(long_options)/sizeof(option); i++)
					{
						printf("-%c  --%s\n",(char)long_options[i].val,long_options[i].name);
					}
					break;
				}

			case '?':
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
