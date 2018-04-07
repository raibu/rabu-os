#ifndef __CPUID__H
#define __CPUID__H
#include "types.h"

int cpuid_supp();
void cpuid(u32* __eax, u32* __ebx, u32* __ecx, u32* __edx);


#endif