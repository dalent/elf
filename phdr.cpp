#include"elflib.h"
#include<map>
using namespace std;
#define CASE_NAME(name) \
	case name: ret = #name;break; 
static const char * get_type(int type)
{
	const char * ret;
	switch(type)
	{
		
		CASE_NAME(PT_NULL);
		CASE_NAME(PT_LOAD);
		CASE_NAME(PT_DYNAMIC);
		CASE_NAME(PT_INTERP);
		CASE_NAME(PT_NOTE);
		CASE_NAME(PT_SHLIB);
		CASE_NAME(PT_PHDR);
		CASE_NAME(PT_TLS);
		CASE_NAME(PT_NUM);
		CASE_NAME(PT_GNU_EH_FRAME);
		CASE_NAME(PT_GNU_STACK);
		CASE_NAME(PT_GNU_RELRO);
		default:
			ret = "Unknown";
			break;
	}

	return ret;
}
static const char* get_flag(int flag)
{
	static char ret[10];
	memset(ret ,0 , 10);
	if(flag & PF_X)
		strcat(ret,"X|");
	if(flag & PF_W)
		strcat(ret, "W|");
	if(flag& PF_R)
		strcat(ret, "R|");

	return ret;


}
void print_phdr(Elf64_Phdr * elf_entity)
{
	//EPRINTF(p_type, "             :%d\n");//type
//	printf("p_type          :%s\n",get_type(elf_entity->p_type));
//	EPRINTF(p_flags, "            :%u\n");//flags
//	EPRINTF(p_offset, "           :0x%lx\n");//flags
//	EPRINTF(p_vaddr, "            :0x%lx\n");//
//	EPRINTF(p_paddr, "            :0x%lx\n");
//	EPRINTF(p_filesz, "           :%lu\n");//link to another section
//	EPRINTF(p_memsz, "            :%lu\n");//section alignment
//	EPRINTF(p_align, "            :%lu\n");//entry size if section hold tables
  	printf("%-20s",get_type(elf_entity->p_type));
  	printf("%-10s",get_flag(elf_entity->p_flags));
  	printf("%-10lx",elf_entity->p_offset);
  	printf("%-10lx",elf_entity->p_vaddr);
  	printf("%-10lx",elf_entity->p_paddr);
  	printf("%-10lu",elf_entity->p_filesz);
  	printf("%-10lu",elf_entity->p_memsz);
  	printf("%-10lu",elf_entity->p_align);

	printf("\n");
}
void print_phdr_header()
{

	printf("\n %50s \n", "program header ");
	printf("%-20s%-10s%-10s%-10s%-10s%-10s%-10s%-10s","type","flags","offset","vaddr","paddr","filesz","memsz","aligin");
	printf("\n");
}
std::map<unsigned,Elf64_Phdr*> g_mapPhdr; 
void init_phdr(ELF_t *elf)
{
	Elf64_Phdr *phdr = GET_PHDR(elf);	
	for(int i = 0; i <GET_PHDR_SIZE(elf); i++)
		g_mapPhdr[phdr[i].p_type] =  &phdr[i];

}
void dump_phdr(ELF_t *elf)
{

	Elf64_Phdr *phdr = GET_PHDR(elf);	
	print_phdr_header();
	for(int i = 0; i <GET_PHDR_SIZE(elf); i++) 
		print_phdr(&phdr[i]);
}
