#include"elflib.h"
#include<map>
#include<string>
#include<vector>
#include<string.h>
using namespace std;
extern std::map<unsigned , std::vector<pair<string,Elf64_Shdr*> > > g_mapSectionHeader;
typedef std::map<unsigned , std::vector<pair<string, Elf64_Shdr*> > >::iterator SEC_ITE;
const char * symbol_type(Elf64_Sym &sym)
{
	const char * ret;
	switch(ELF64_ST_TYPE(sym.st_info))
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

const char * symbol_bind(Elf64_Sym &sym)
{
	const char * ret;
	switch(ELF64_ST_BIND(sym.st_info))
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

const char* get_sym_name(ELF_t* elf,unsigned offset)
{
	//get the symbol name
	static const char * s_name = NULL;
	if(s_name == NULL && elf != NULL)
	{
		SEC_ITE str_ite = g_mapSectionHeader.find(SHT_STRTAB);
		if(str_ite != g_mapSectionHeader.end())
		{
			std::vector<pair<string ,Elf64_Shdr*> >::iterator ite_tmp =  str_ite->second.begin();
			while(ite_tmp != str_ite->second.end())
			{
				if(strcasecmp(ite_tmp->first.c_str(), ".strtab") == 0)//tag name is strtab
				{
					s_name =(const char*)elf_offset(elf, (*ite_tmp).second->sh_offset); 
					break;
				}

				ite_tmp++;
			}
		}
	}

	if(s_name == NULL)
		return NULL;

	return &s_name[offset];
}
static const char* get_other(char other)
{
	const char* ret;
	switch(ELF64_ST_VISIBILITY(other))
	{
		case STV_DEFAULT:
			ret = "STV_DEFAULT";
			break;
		case STV_INTERNAL:
			ret = "STV_INTERNAL";
			break;
		case STV_HIDDEN:
			ret = "STV_HIDDEN";
			break;
		case STV_PROTECTED:
			ret ="STV_PROTECTED";
			break;

		dafault:
			ret = "unknown";
			break;
	}

	return ret;
}
static void print_symbol_header()
{
	printf("%-10s%-5s%-15s%-15s%-15s%-10s%-60s\n","value","size","type","bind","other","shndx","name"); 
}
void printSymbol(Elf64_Sym *elf_entity)
{
//	EPRINTF(st_name, "            :%u\n");//name
//	EPRINTF(st_info, "            :%c\n");//type

	//printf("name             %s\n", symbol_name(elf_head));
//	printf("st_name            :%s\n",get_sym_name(NULL,elf_entity->st_name)); 
//	printf("bind               :%s\n", symbol_bind(*elf_entity));
//	printf("type               :%s\n", symbol_type(*elf_entity));
//	EPRINTF(st_other, "           :%c\n");//type
//	EPRINTF(st_shndx, "           :%hd\n");//type
//	EPRINTF(st_value, "           :0x%lx\n");//type
//	EPRINTF(st_size, "            :%lu\n");//type
	printf("%-10lx", elf_entity->st_value); 
	printf("%-5lu", elf_entity->st_size); 
	printf("%-15s", symbol_type(*elf_entity)); 
	printf("%-15s", symbol_bind(*elf_entity)); 
	//because it is reserved, so i don't want to show it
	printf("%-15s", get_other(elf_entity->st_other)); 
	printf("%-10hd", elf_entity->st_shndx); 
	std::string str = get_sym_name(NULL,elf_entity->st_name);
	if(str.size() > 60)
		str=str.substr(0,60);

	printf("%-60s", str.c_str()); 
	printf("\n");
}
void init_symbol_table(ELF_t*elf)
{
	//init it
	get_sym_name(elf,0);
}

void dump_symbol(ELF_t* elf)
{

	//init it
	get_sym_name(elf,0);
	//find the symbol table
	SEC_ITE ite = g_mapSectionHeader.find(SHT_SYMTAB);
	if(ite != g_mapSectionHeader.end())
	{
		std::vector<pair<string, Elf64_Shdr*> >::iterator ite_tmp =  ite->second.begin();
		while(ite_tmp != ite->second.end())
		{
			int size = (*ite_tmp).second->sh_size / (*ite_tmp).second->sh_entsize;
			Elf64_Sym *sym = (Elf64_Sym*)elf_offset(elf, (*ite_tmp).second->sh_offset);
			printf("section name %s\n", ite_tmp->first.c_str());

			//print header
			print_symbol_header();
			for(int i = 1; i < size; i++)
				printSymbol(&sym[i]);

			ite_tmp++;
		}
	}
}

