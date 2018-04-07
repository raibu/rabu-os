#ifndef STR_H__
#define STR_H__


#include "../cpu/types.h"
void itoa(int x, char* str);
void itob(i32 x, char* str);
void itoh(i32 x, char* str);

int strlen(char* s);
void backspace(char* s);
void append(char* s, char n);
int strcmp(char* s1, char* s2);


#endif