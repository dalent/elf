#include"elflib.h"
#include<map>
#include<vector>
#include<string>
using namespace std;
#define APRINTF(name,type)\
	printf(type,elf_entity->name)

void PrintElfSec(Elf64_Shdr*elf_entity, const char * name)
{
	//APRINTF(sh_name, "         	  :%-u\n");//section name
	printf("%-20s", &name[elf_entity->sh_name]);//section name
	APRINTF(sh_type, "%-10x");//type
	APRINTF(sh_flags, "%-10lu");//flags
	APRINTF(sh_addr, "%-10lx");//flags
	APRINTF(sh_offset, "%-10lx");//
	APRINTF(sh_size, "%-10lu");//
	APRINTF(sh_link, "%-10u");//link to another section
	APRINTF(sh_info, "%-10u");//link to another section
	APRINTF(sh_addralign, "%-10lu");//section alignment
	APRINTF(sh_entsize, "%-10lu");//entry size if section hold tables
	printf("\n");
}
void PrintHeader()
{
	printf("%-20s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s","name","type","flags","addr","offset","size","link","info","addralign","entsize");
	printf("\n");
}

std::map<unsigned, std::vector<std::pair<string,Elf64_Shdr*> > > g_mapSectionHeader;

void dump_section(ELF_t * elf)
{
	int size = GET_SHDR_SIZE(elf);
	Elf64_Shdr* shdr = GET_SHDR(elf);
	PrintHeader();

	for(int i = 1; i < size; i++)
	{
		PrintElfSec(&shdr[i], elf_offset(elf,shdr[GET_SYM_TAB_POS(elf)].sh_offset));
	}
}

//init
void section_init(ELF_t*elf)
{

	int size = GET_SHDR_SIZE(elf);
	Elf64_Shdr* shdr = GET_SHDR(elf);
	for(int i = 1; i < size; i++)
	{
		g_mapSectionHeader[shdr[i].sh_type]
			.push_back(make_pair(elf_offset(elf,shdr[GET_SYM_TAB_POS(elf)].sh_offset)+shdr[i].sh_name,&shdr[i]));
	}
}

