#include"elflib.h"
#include<map>
#include<vector>
#include<string>
using namespace std;
void printElfSec(Elf64_Shdr*elf_entity, const char * name)
{
	//EPRINTF(sh_name, "         	  :%u\n");//section name
	printf("sh_name            :%s\n", &name[elf_entity->sh_name]);//section name
	EPRINTF(sh_type, "            :0x%x\n");//type
	EPRINTF(sh_flags, "           :%lu\n");//flags
	EPRINTF(sh_addr, "            :0x%lx\n");//flags
	EPRINTF(sh_offset, "          :0x%lx\n");//
	EPRINTF(sh_size, "            :%lu\n");//
	EPRINTF(sh_link, "            :%u\n");//link to another section
	EPRINTF(sh_info, "            :%u\n");//link to another section
	EPRINTF(sh_addralign, "       :%lu\n");//section alignment
	EPRINTF(sh_entsize, "         :%lu\n");//entry size if section hold tables
	printf("\n");
}

std::map<unsigned, std::vector<std::pair<string,Elf64_Shdr*> > > g_mapSectionHeader;
void dump_section(ELF_t * elf)
{
	int size = GET_SHDR_SIZE(elf);
	Elf64_Shdr* shdr = GET_SHDR(elf);
	for(int i = 1; i < size; i++)
	{
		g_mapSectionHeader[shdr[i].sh_type]
			.push_back(make_pair(elf_offset(elf,shdr[GET_SYM_TAB_POS(elf)].sh_offset)+shdr[i].sh_name,&shdr[i]));

		printElfSec(&shdr[i], elf_offset(elf,shdr[GET_SYM_TAB_POS(elf)].sh_offset));
	}
}

