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
#include<vector>
#include<map>
using namespace std;

struct elf_section {
	char  name[40];
	Elf64_Shdr header;
	void * value;
};

elf_section *elf_sect;//we can use vector 
std::vector<string> vec;
Elf64_Ehdr elf_head;
int str_index = 0;
//std::map<unsigned, std::vector<elf_section*> > elf_index;
//typedef std::map<unsigned, std::vector<elf_section*> >::iterator ELF_ITE;
extern void printElfHeader(Elf64_Ehdr& elf_head);
extern void printElfSecHeader(Elf64_Shdr& elf_sect);
extern void printElfSec(elf_section &elf_head);
extern void printSymbol(Elf64_Sym &elf_header);
int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		printf("argu not 2");
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	read(fd,&elf_head, sizeof elf_head); 
	printElfHeader(elf_head);

	elf_sect  = (elf_section *)malloc(elf_head.e_shnum * sizeof(elf_section));
	lseek(fd, elf_head.e_shoff, SEEK_SET);

	for(int i =0; i < elf_head.e_shnum;i++)
	{
 		//read header
		read(fd, &(elf_sect[i].header), sizeof elf_sect[i].header);
        // add index 
       // elf_index[elf_sect[i].header.sh_type].push_back(&elf_sect[i]);
	}

	for(int i =1; i < elf_head.e_shnum;i++)//0 is reserved 
	{
		elf_sect[i].value = malloc(elf_sect[i].header.sh_size);
		//read section value
		lseek(fd, elf_sect[i].header.sh_offset, SEEK_SET);
		read(fd, elf_sect[i].value, elf_sect[i].header.sh_size);
	}

	for(int j = 1; j < elf_head.e_shnum; j++)
	{
		//read section name from strtab section
		strcpy(elf_sect[j].name,(char*)elf_sect[elf_head.e_shstrndx].value + elf_sect[j].header.sh_name);
		printElfSec(elf_sect[j]);
		if(elf_sect[j].header.sh_type != elf_head.e_shstrndx && elf_sect[j].header.sh_type == 3)
			str_index = j;

	}


//	ELF_ITE ite = elf_index.find(SHT_SYMTAB);// SHT_SYMTAB is 2
//	if(ite != elf_index.end())
//	{
//
//	}

	for(int j = 1; j < elf_head.e_shnum; j++)
	{
		if(elf_sect[j].header.sh_type == SHT_SYMTAB)
		{
			Elf64_Sym *sym ;
			int size = elf_sect[j].header.sh_size / elf_sect[j].header.sh_entsize;
			sym = (Elf64_Sym*)elf_sect[j].value;
			for(int i = 0 ; i < size ; i ++)
				printSymbol(sym[i]);
		}
	}
	return 0;
}

#define EPRINTF(name,type)\
	printf(#name type,elf_head.name)
void printElfSec(elf_section &elf_head)
{
	EPRINTF(name, "               :%s\n");//type
	printElfSecHeader(elf_head.header);
	printf("\n");
}
const char * symbol_name(Elf64_Sym &sym)
{
	if(str_index != 0)
	return  (char*)elf_sect[str_index].value + sym.st_name;
	else
		return "Unknown";

}
const char * symbol_type(Elf64_Sym &sym)
{
	const char * ret;
	switch(ELF64_ST_TYPE(sym.st_info))
	{

		case STB_LOCAL : ret = "STB_LOCAL";	break;
		case STB_GLOBAL: ret = "STB_GLOBAL"; break;
		case STB_WEAK  : ret = "STB_WEAK"; break;
		case STB_NUM   : ret = "STB_NUM"; break;
		//case STB_LOOS  : ret = "STB_LOOS"; break;
		case STB_GNU_UNIQUE: ret = "STB_GNU_UNIQUE"; break;
		case STB_HIOS  : ret = "STB_HIOS"; break;
		case STB_LOPROC: ret ="STB_LOPROC"; break;
		case STB_HIPROC: ret = "STB_HIPROC"; break;
		default: ret = "unknown"; break;
	}

	return ret;
}
const char * symbol_bind(Elf64_Sym &sym)
{
	const char * ret;
	switch(ELF64_ST_BIND(sym.st_info))
	{
		case STT_NOTYPE : ret = "STT_NOTYPE"; break;
		case STT_OBJECT : ret = "STT_OBJECT"; break;
		case STT_FUNC   : ret = "STT_FUNC"  ; break;
		case STT_SECTION: ret = "STT_SECTION"; break;
		case STT_FILE   : ret = "STT_FILE";    break;
		case STT_COMMON : ret = "STT_COMMON";    break;
		case STT_TLS    : ret = "STT_TLS";    break;
		case STT_NUM    : ret = "STT_NUM";    break;
	//	case STT_LOOS   : ret = "STT_LOOS";    break;
		case STT_GNU_IFUNC    : ret = "STT_GNU_IFUNC";    break;
		case STT_HIOS      : ret = "STT_HIOS";    break;
		case STT_LOPROC    : ret = "STT_LOPROC";    break;
		case STT_HIPROC    : ret = "STT_HIPROC";    break;
		default :
			ret = "Unknown"; break;
	}

	return ret;
}
void printSymbol(Elf64_Sym &elf_head)
{
//	EPRINTF(st_name, "            :%u\n");//name
//	EPRINTF(st_info, "            :%c\n");//type

	printf("name             %s\n", symbol_name(elf_head));
	printf("bind             %s\n", symbol_bind(elf_head));
	printf("type             %s\n", symbol_type(elf_head));
	EPRINTF(st_other, "           :%c\n");//type
	EPRINTF(st_shndx, "           :%hd\n");//type
	EPRINTF(st_value, "           :0x%lx\n");//type
	EPRINTF(st_size, "           :%lu\n");//type
}
void printElfSecHeader(Elf64_Shdr &elf_head)
{
//	EPRINTF(sh_name, "         	  :%u\n");//section name
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

void printElfHeader(Elf64_Ehdr &elf_head)
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
