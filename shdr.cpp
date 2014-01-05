#include"elflib.h"
#include<map>
#include<vector>
#include<string>
using namespace std;
#define APRINTF(name,type)\
	printf(type,elf_entity->name)
#define CASE_RET(type)\
	case type: ret=#type;break
static const char * get_type(unsigned type)
{
	const char * ret;
	switch(type)
	{
		CASE_RET(SHT_NULL);
		CASE_RET(SHT_PROGBITS);
		CASE_RET(SHT_SYMTAB);
		CASE_RET(SHT_STRTAB);
		CASE_RET(SHT_RELA);
		CASE_RET(SHT_HASH);
		CASE_RET(SHT_DYNAMIC);
		CASE_RET(SHT_NOTE);
		CASE_RET(SHT_NOBITS);
		CASE_RET(SHT_REL);
		CASE_RET(SHT_SHLIB);
		CASE_RET(SHT_DYNSYM);
		CASE_RET(SHT_INIT_ARRAY);
		CASE_RET(SHT_FINI_ARRAY);
		CASE_RET(SHT_PREINIT_ARRAY);
		CASE_RET(SHT_GROUP);
		CASE_RET(SHT_GNU_ATTRIBUTES);
		CASE_RET(SHT_GNU_HASH);
		CASE_RET(SHT_GNU_LIBLIST);
		default:
		 ret = "unknown";
		 break;
	}
	return ret;
}
static const char* get_flag(unsigned cflag)
{
	static char flag[40];
	memset(flag,0,sizeof(flag));
	if(cflag & SHF_WRITE)
		strcat(flag,"W|");
	if(cflag & SHF_EXECINSTR)
		strcat(flag, "X|");
	if(cflag &SHF_ALLOC)
		strcat(flag, "ALLOC|");
	if(cflag & SHF_MERGE)
		strcat(flag,"Merge|"); 
	if(SHF_STRINGS & cflag)
		strcat(flag, "STR|");
	if(cflag & SHF_INFO_LINK)
		strcat(flag, "INFO_LINK|");
	if(cflag & SHF_LINK_ORDER)
		strcat(flag, "LINK_ORDER|");

	return flag;
}

void PrintElfSec(Elf64_Shdr*elf_entity, const char * name)
{
	//APRINTF(sh_name, "         	  :%-u\n");//section name
	printf("%-20s", &name[elf_entity->sh_name]);//section name
	printf("%-15s", get_type(elf_entity->sh_type));//type
	printf("%-15s", get_flag(elf_entity->sh_flags));//flags
//	APRINTF(sh_flags, "%-10lx");//flags
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
	printf("\n %50s \n", "section header");
	printf("%-20s%-15s%-15s%-10s%-10s%-10s%-10s%-10s%-10s%-10s","name","type","flags","addr","offset","size","link","info","addralign","entsize");
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
			.push_back(make_pair(elf_offset(elf,shdr[GET_SYM_TAB_POS(elf)].sh_offset)+shdr[i].sh_name, &shdr[i]));
	}
}

