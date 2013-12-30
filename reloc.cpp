#include"elflib.h"
void print_rel(Elf64_Rel *elf_entity)
{
	EPRINTF(r_offset, "         :0x%lx\n");//type
	printf("symbol              :%lu\n", ELF64_R_SYM(elf_entity->r_info));
	printf("type              :%lu\n", ELF64_R_TYPE(elf_entity->r_info));
	EPRINTF(r_info, "           :0x%lx\n");//type
	printf("\n");
}

void print_rela(Elf64_Rela*elf_entity)
{
	EPRINTF(r_offset, "           :0x%lx\n");//type
	printf("symbol              :%lu\n", ELF64_R_SYM(elf_entity->r_info));
	printf("type              :%lu\n", ELF64_R_TYPE(elf_entity->r_info));
	EPRINTF(r_info, "             :0x%lx\n");//type
	EPRINTF(r_addend, "           :%lu\n");//type
	printf("\n");
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
			if(type == SHT_REL)
			{
				Elf64_Rel *sym = (Elf64_Rel*)elf_offset(elf, (*ite_tmp).second->sh_offset);
				for(int i = 1; i < size; i++)
					print_rel(&sym[i]);
			}
			else
			{
				Elf64_Rela*sym = (Elf64_Rela*)elf_offset(elf, (*ite_tmp).second->sh_offset);
				for(int i = 1; i < size; i++)
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
