#include "../libc/mem.h"
#include "../cpu/types.h"
 

uint memcpy(void* dst, void* src, uint bytes){
	for (int i = 0; i < bytes; ++i)
	{
		*(char*)(dst++) = *(char*)(src++);
	}
	return bytes;
}


uint memset(void* dst, char val, uint bytes){
	for (uint i = 0; i < bytes; ++i)
	{
		*(char*)(dst+i) = val;
	}
	return bytes;
}

