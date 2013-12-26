#include"elflib.h"
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

void printSymbol(Elf64_Sym *elf_entity)
{
//	EPRINTF(st_name, "            :%u\n");//name
//	EPRINTF(st_info, "            :%c\n");//type

	//printf("name             %s\n", symbol_name(elf_head));
	printf("bind             %s\n", symbol_bind(*elf_entity));
	printf("type             %s\n", symbol_type(*elf_entity));
	EPRINTF(st_other, "           :%c\n");//type
	EPRINTF(st_shndx, "           :%hd\n");//type
	EPRINTF(st_value, "           :0x%lx\n");//type
	EPRINTF(st_size, "           :%lu\n");//type
}
