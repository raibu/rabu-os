#include "types.h"
#include "cpuid.h"

int cpuid_supp(){
	int ret;
	__asm__(
		"pushf \n\t"
		"pushf \n\t"
		"popl %%ebx \n\t"
		"xorl $0x00200000, %%ebx\n\t"
		"pushl %%ebx \n\t"
		"popf \n\t"
		"pushf \n\t"
		"popl %%eax \n\t"
		"popl %%ebx \n\t"
		"xorl %%ebx, %%eax \n\t"
		:"=a"(ret));
	return ret;
}


void cpuid(u32* __eax, u32* __ebx, u32* __ecx, u32* __edx){
	//if(!cpuid_supp())return; 
	__asm__(
		"cpuid \n\t"
		:"=a"(*__eax),
		"=b"(*__ebx),
		"=c"(*__ecx),
		"=d"(*__edx) 
		:"a"(*__eax));
}
