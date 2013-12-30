#include"elflib.h"
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
void print_phdr(Elf64_Phdr * elf_entity)
{
	//EPRINTF(p_type, "             :%d\n");//type
	printf("p_type          :%s\n",get_type(elf_entity->p_type));
	EPRINTF(p_flags, "            :%u\n");//flags
	EPRINTF(p_offset, "           :0x%lx\n");//flags
	EPRINTF(p_vaddr, "            :0x%lx\n");//
	EPRINTF(p_paddr, "            :0x%lx\n");
	EPRINTF(p_filesz, "           :%lu\n");//link to another section
	EPRINTF(p_memsz, "            :%lu\n");//section alignment
	EPRINTF(p_align, "            :%lu\n");//entry size if section hold tables
	printf("\n");

}
void dump_phdr(ELF_t *elf)
{

	Elf64_Phdr *phdr = GET_PHDR(elf);	
	for(int i = 0; i <GET_PHDR_SIZE(elf); i++) 
		print_phdr(&phdr[i]);
}
