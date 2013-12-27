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

#define GET_SHDR(elf)\
	(Elf64_Shdr*)(elf->data + ((Elf64_Ehdr*)(elf->data))->e_shoff);

#define GET_SHDR_SIZE(elf)\
	((Elf64_Ehdr*)(elf->data))->e_shnum;

#define EPRINTF(name,type)\
	printf(#name type,elf_entity->name)


#include<stdio.h>
#define ERROR_RET(msg,code) do{\
	printf("file: %s, line: %d, msg: %s", __FILE__, __LINE__, msg);\
	return code;\
}while(0);
	
int open_elf(struct ELF_t *elf, char* filename);

extern int verify_file_format(ELF_t * elf);
extern void dump_ehdr(ELF_t *elf);
extern void dump_section(ELF_t * elf);

#endif
