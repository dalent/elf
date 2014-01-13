#include"elflib.h"
#include<map>
#define CASE_NO(num,type1)\
	case  type1:ret = #type1;*type=num;break;
using namespace std;
extern std::map<unsigned, Elf64_Phdr*> g_mapPhdr;
static const  char* is_dval(Elf64_Dyn *dyn, int*type)
{
	const char* ret;
	switch(dyn->d_tag)
	{
		*type =  0;
		CASE_NO(0, DT_NEEDED);
		CASE_NO(0, DT_PLTRELSZ);
		CASE_NO(0, DT_RELASZ);
		CASE_NO(0, DT_RELAENT);
		CASE_NO(0, DT_STRSZ);
		CASE_NO(0, DT_SYMENT);
		CASE_NO(0, DT_SONAME);
		CASE_NO(0, DT_RPATH);
		CASE_NO(0, DT_RELSZ);
		CASE_NO(0, DT_RELENT);
		CASE_NO(0, DT_PLTREL);
		CASE_NO(0, DT_INIT_ARRAYSZ);
		CASE_NO(0, DT_FINI_ARRAYSZ);

		CASE_NO(1, DT_PLTGOT);
		CASE_NO(1, DT_HASH);
		CASE_NO(1, DT_STRTAB);
		CASE_NO(1, DT_SYMTAB);
		CASE_NO(1, DT_RELA);
		CASE_NO(1, DT_INIT);
		CASE_NO(1, DT_FINI);
		CASE_NO(1, DT_SYMBOLIC);
		CASE_NO(1, DT_REL);
		CASE_NO(1, DT_DEBUG);
		CASE_NO(1, DT_TEXTREL);
		CASE_NO(1, DT_JMPREL);
		CASE_NO(1, DT_BIND_NOW);
		CASE_NO(1, DT_INIT_ARRAY);
		CASE_NO(1, DT_FINI_ARRAY);
		CASE_NO(1, DT_RUNPATH);
			*type =1;
			break;
		default:
			ret = "unknown";
			*type = 2;
			break;
	}
	return ret;
}
static void print_dyn(Elf64_Dyn* dyn)
{
	const char * ret;
	int type = 0;
	ret = is_dval(dyn, &type);
	printf("%-20s", ret);
	if(type == 0)
		printf("%-10lx", dyn->d_un.d_val);
	else if(type == 1)
		printf("%-10s%-10lx","",dyn->d_un.d_ptr);
	printf("\n");

}
static void print_header( int size)
{
	printf("\ndynamic for program header entry has entry %d\n", size);
	printf("%-20s%-10s%-10s\n", "d_tag","d_val","d_ptr");
}
void dump_phdr_dynamic(ELF_t *elf )
{

	std::map<unsigned,Elf64_Phdr*>::iterator ite = g_mapPhdr.find(PT_DYNAMIC);
	if(ite != g_mapPhdr.end())
	{
		int size = ite->second->p_filesz / sizeof(Elf64_Dyn);
		Elf64_Dyn * dyn = (Elf64_Dyn*) elf_offset(elf, (*ite).second->p_offset);

		print_header(size);
		for(int i =0 ;i < size; i++)
		{
			print_dyn(&dyn[i]);
		}
	}
}
