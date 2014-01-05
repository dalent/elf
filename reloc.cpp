#include"elflib.h"
#define CASE_TYPE(type)\
	case type: ret = #type;break 
const char* get_type(unsigned long type)
{
	const char* ret;
	switch(type)
	{
		CASE_TYPE(R_X86_64_NONE);
		CASE_TYPE(R_X86_64_64);
		CASE_TYPE(R_X86_64_PC32);
		CASE_TYPE(R_X86_64_GOT32);
		CASE_TYPE(R_X86_64_PLT32);
		CASE_TYPE(R_X86_64_COPY);
		CASE_TYPE(R_X86_64_GLOB_DAT);
		CASE_TYPE(R_X86_64_JUMP_SLOT);
		CASE_TYPE(R_X86_64_RELATIVE);
		CASE_TYPE(R_X86_64_GOTPCREL);
		CASE_TYPE(R_X86_64_32);
		default:
		 ret = "Unknown";
		 break;
	}
	return ret;
}
void print_rel(Elf64_Rel *elf_entity)
{
//	EPRINTF(r_offset, "         :0x%lx\n");//type
//	printf("symbol            :%lu\n", ELF64_R_SYM(elf_entity->r_info));
//	printf("type              :%s\n", get_type(ELF64_R_TYPE(elf_entity->r_info)));
//	EPRINTF(r_info, "           :0x%lx\n");//type
//	printf("\n");

	printf("%12.12lx%4s", elf_entity->r_offset,"");
	printf("%-20s",get_type(ELF64_R_TYPE(elf_entity->r_info))); 
	printf("%-15.12lx", elf_entity->r_info);
	printf("%-20s", get_dyn_syn_name(ELF64_R_SYM(elf_entity->r_info)));
	printf("\n");
}

void print_rela(Elf64_Rela*elf_entity)
{
//	EPRINTF(r_offset, "           :0x%lx\n");//type
//	//printf("symbol             :%lu\n", ELF64_R_SYM(elf_entity->r_info));
//	printf("symbol name          :%s\n",get_dyn_syn_name(ELF64_R_SYM(elf_entity->r_info)));
//	printf("type               :%s\n", get_type(ELF64_R_TYPE(elf_entity->r_info)));
//	EPRINTF(r_info, "             :0x%lx\n");//type
//	EPRINTF(r_addend, "           :%lu\n");//type
//	printf("\n");
	printf("%12.12lx%4s", elf_entity->r_offset,"");
	printf("%-20s",get_type(ELF64_R_TYPE(elf_entity->r_info))); 
	printf("%-15.12lx", elf_entity->r_info);
	printf("%-10lu", elf_entity->r_addend);
	printf("%-20s", get_dyn_syn_name(ELF64_R_SYM(elf_entity->r_info)));
	printf("\n");

}
void print_rela_header()
{
	printf("%-16s%-20s%-15s%-10s%-20s\n","offset", "type","info", "addend","symbol name");
}

void print_real(ELF_t*elf,int type)
{

	SEC_ITE ite = g_mapSectionHeader.find(type);
	if(ite != g_mapSectionHeader.end())
	{
		std::vector<pair<string, Elf64_Shdr*> >::iterator ite_tmp =  ite->second.begin();
		while(ite_tmp != ite->second.end())
		{
			int size = (*ite_tmp).second->sh_size / (*ite_tmp).second->sh_entsize;

			printf("%s ", ite_tmp->first.c_str());
			printf("has entry %d\n", size);
			print_rela_header();
			if(type == SHT_REL)
			{
				Elf64_Rel *sym = (Elf64_Rel*)elf_offset(elf, (*ite_tmp).second->sh_offset);
				for(int i = 0; i < size; i++)
					print_rel(&sym[i]);
			}
			else
			{
				Elf64_Rela*sym = (Elf64_Rela*)elf_offset(elf, (*ite_tmp).second->sh_offset);
				for(int i = 0; i < size; i++)
					print_rela(&sym[i]);

			}

			ite_tmp++;
		}
	}
}
void dump_relac(ELF_t*elf)
{
	print_real(elf,SHT_REL);
	print_real(elf,SHT_RELA);

}
