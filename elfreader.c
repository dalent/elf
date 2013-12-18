#include<stdio.h>
#include<elf.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<vector>
#include<string>
#include<string.h>
#define EPRINTF(name,type)\
	printf(#name type,elf_head.name)


extern void printElfHeader(Elf64_Ehdr elf_head);
extern void printElfSecHeader(Elf64_Shdr elf_sect);
using namespace std;
std::vector<string> vec;
int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		printf("argu not 2");
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	Elf64_Ehdr elf_head;
	read(fd,&elf_head, sizeof elf_head); 
	printElfHeader(elf_head);
	Elf64_Shdr *elf_sect  = (Elf64_Shdr *)malloc(elf_head.e_shnum * sizeof(Elf64_Shdr));
	lseek(fd, elf_head.e_shoff, SEEK_SET);
	if(elf_head.e_shentsize != sizeof *elf_sect)
		printf("sect size %ld", sizeof *elf_sect);
	for(int i =0; i < elf_head.e_shnum;i++)
	{
		read(fd, &elf_sect[i], sizeof *elf_sect);
		printElfSecHeader(elf_sect[i]);
	}
	for(int j = 0; j < elf_head.e_shnum; j++)
	{
		if(elf_sect[j].sh_type == 3)
		{
			char name[4096];
			char *tmp = name ;
			unsigned long iSize = 0;
			lseek(fd, elf_sect[j].sh_offset, SEEK_SET);
			read(fd,name, elf_sect[j].sh_size);
			while(tmp - name < elf_sect[j].sh_size)
			{
				if(*tmp == 0)
				{
					tmp += 1;
					continue;
				}

				vec.push_back(tmp);
				tmp += strlen(tmp) + 1;
			}
		}
	}
	for(int i =0 ; i < vec.size(); i++)
		printf("%d: %s\n", i, vec[i].c_str());

	free(elf_sect);

	return 0;
}
void printElfSecHeader(Elf64_Shdr elf_head)
{
	EPRINTF(sh_name, "         	  :%u\n");//section name
	EPRINTF(sh_type, "         	  :0x%x\n");//type
	EPRINTF(sh_flags, "        	  :%lu\n");//flags
	EPRINTF(sh_addr, "         	  :0x%lx\n");//flags
	EPRINTF(sh_offset, "       	  :0x%lx\n");//
	EPRINTF(sh_size, "         	  :%lu\n");//
	EPRINTF(sh_link, "         	  :%u\n");//link to another section
	EPRINTF(sh_info, "         	  :%u\n");//link to another section
	EPRINTF(sh_addralign, "       :%lu\n");//section alignment
	EPRINTF(sh_entsize, "         :%lu\n");//entry size if section hold tables

}
void printElfHeader(Elf64_Ehdr elf_head)
{
	printf("e_ident: ELFMAG0: 0x%x\n", elf_head.e_ident[0]);
	printf("e_ident: ELFMAG1: %c\n",   elf_head.e_ident[1]);
	printf("e_ident: ELFMAG2: %c\n",   elf_head.e_ident[2]);
	printf("e_ident: ELFMAG3: %c\n",   elf_head.e_ident[3]);
	printf("e_ident: ELFCLASS: %d\n",elf_head.e_ident[4]);
	printf("e_ident: EI_DATA: %d\n",elf_head.e_ident[5]);
	printf("e_ident: EI_VERSION: %d\n",elf_head.e_ident[6]);
	printf("e_ident: EI_PAD: %d\n",elf_head.e_ident[7]);
	EPRINTF(e_type, "        :%hd\n");//object file type
	EPRINTF(e_machine, "     :%hd\n");//architecture
	EPRINTF(e_version, "     :%d\n");//object file version
	EPRINTF(e_entry, "       :0x%lx\n");//virtual address
	EPRINTF(e_phoff, "       :%ld\n");//program header table offset
	EPRINTF(e_shoff, "       :%ld\n");//section header offset
	EPRINTF(e_flags, "       :%d\n");//processor spec flags
	EPRINTF(e_ehsize, "      :%hd\n");//elf header size
	EPRINTF(e_phentsize, "   :%hd\n");//program header table entry size 
	EPRINTF(e_phnum, "       :%hd\n");//program header entry count 
	EPRINTF(e_shentsize, "   :%hd\n");//section header size
	EPRINTF(e_shnum, "       :%hd\n");//section header entry count
	EPRINTF(e_shstrndx, "    :%hd\n");//section header index string table
}
