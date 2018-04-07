#ifndef MEM_H__
#define MEM_H__


#include "../cpu/types.h"
uint memcpy(void* dst, void* src, uint bytes);
uint memset(void* dst, char val, uint bytes);


#endif