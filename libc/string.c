//#include "screen.h"
#include "../cpu/types.h"

void itoa(i32 x, char* str){
	int chars = 0;
	int i = 0;
	__asm__(
			"pushl %%eax           		\n\t" //push x
			"finit                		\n\t" //;init fpu
			"fldlg2               		\n\t" //;load log(2)10 to st1
			"fildl (%%esp)         		\n\t" //;load x to fpu st0
			"popl %%eax            		\n\t" //pop eax
			"fabs               		\n\t"
			"pushl %%ebx           		\n\t" //push chars
			"fyl2x                		\n\t" //;calculate st1 = st1*log2(st0) == log10(x) and pop st0
			"fisttpl  (%%esp)         	\n\t" // store result in stack 'n truncate
			"popl %%ebx                 \n\t"
			: "=b"(chars) : "a"(x): "memory");
	if(x<0){
		x=-x;
		chars++;
		i=1;
		*str = '-';
	}
	str[chars+1] = 0;
	for (; chars>=i; chars--)
	{
		*(str+chars) = x%10+'0';
		x/=10;
	}
}


void itob(i32 x, char* str){
	for (int i = 0; i < 32; ++i)
	{
		str[i] = '0'+((x & (0x80000000 >> i))!=0);
		//x=x<<1;
	}
	str[32]=0;
}

void itoh(i32 x, char* str){
	for (int i = 7; i >= 0; --i)
	{
		str[i] = '0'+ (x & 0xf) + 8*((x & 0xf)>0x09);
		x=x>>4;
	}
	str[8]=0;
}

int strcmp(char* s1, char* s2) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char* s, char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char* s) {
    int len = strlen(s);
    s[len-1] = '\0';
}









