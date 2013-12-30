#ifndef __ELFLIB_H__
#define __ELFLIB_H__
#include<elf.h>
struct ELF_t{
char *name;
int fd;
int size;
char *data;
};


#define GET_EHDR(elf) ({\
	(Elf64_Ehdr*)elf->data;})

//get section header array
#define GET_SHDR(elf)\
	(Elf64_Shdr*)(elf->data + ((Elf64_Ehdr*)(elf->data))->e_shoff);

//get program header array
#define GET_PHDR(elf)\
	(Elf64_Phdr*)(elf->data + ((Elf64_Ehdr*)(elf->data))->e_phoff);

//get section header string tab
#define GET_SYM_TAB_POS(elf)\
	((Elf64_Ehdr*)(elf->data))->e_shstrndx

#define GET_SHDR_SIZE(elf)\
	((Elf64_Ehdr*)(elf->data))->e_shnum;

#define GET_PHDR_SIZE(elf)\
	((Elf64_Ehdr*)(elf->data))->e_phnum

#define EPRINTF(name,type)\
	printf(#name type,elf_entity->name)


#include<stdio.h>
#define ERROR_RET(msg,code) do{\
	printf("file: %s, line: %d, msg: %s", __FILE__, __LINE__, msg);\
	return code;\
}while(0);
	
extern int open_elf(struct ELF_t *elf, char* filename);
extern char* elf_offset(ELF_t* elf, int offset);

extern int verify_file_format(ELF_t * elf);
extern void dump_ehdr(ELF_t *elf);
extern void dump_section(ELF_t * elf);
extern void dump_symbol(ELF_t *elf_entity);

extern void dump_phdr(ELF_t *elf);
extern void dump_relac(ELF_t *elf);
//for now i moved it here
#include<map>
#include<string>
#include<vector>
#include<string.h>
using namespace std;
extern std::map<unsigned , std::vector<pair<string,Elf64_Shdr*> > > g_mapSectionHeader;
typedef std::map<unsigned , std::vector<pair<string, Elf64_Shdr*> > >::iterator SEC_ITE;

#endif
