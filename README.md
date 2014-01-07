elf
===
I want to write a elf reader. so i read some topic about it.
I wrote this example, it can only analyse 64 bit elf file.

it read the
       |--elf header
       |--section header
       | |--symbol table
       | |--dynamic table
       | |--rela  table
       |--program header
       |  |--program dynamic
when exe file execute ,first the loader will loader the exe file to memory,
second it will find the elf header and get the program header content, it will
load the PT_LOAD type content to the virtual address.
after that it will find the content need to relocated ,named the rela/relac

two type R_386_GLOB_DAT refering the global offset table.
R_386_JMP_SLOT refering the procedure linkage table





we can use it just like
./rd -h to show a list of uses 
