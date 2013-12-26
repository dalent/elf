#include"elflib.h"
void printElfSec(Elf64_Shdr*elf_entity)
{
	EPRINTF(sh_name, "         	  :%u\n");//section name
	EPRINTF(sh_type, "            :0x%x\n");//type
	EPRINTF(sh_flags, "           :%lu\n");//flags
	EPRINTF(sh_addr, "            :0x%lx\n");//flags
	EPRINTF(sh_offset, "          :0x%lx\n");//
	EPRINTF(sh_size, "            :%lu\n");//
	EPRINTF(sh_link, "            :%u\n");//link to another section
	EPRINTF(sh_info, "            :%u\n");//link to another section
	EPRINTF(sh_addralign, "       :%lu\n");//section alignment
	EPRINTF(sh_entsize, "         :%lu\n");//entry size if section hold tables
}

void dump_section(ELF_t * elf)
{
	int size = GET_SHDR_SIZE(elf);
	Elf64_Shdr* ehdr = GET_SHDR(elf);
	for(int i = 1; i < size; i++)
	{
		printElfSec(&ehdr[i]);
	}
}

