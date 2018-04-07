#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../libc/string.h"
#include "kernel.h"
#include "../cpu/cpuid.h"


int main() { 
	isr_install();
	__asm__("sti");
    
    kprintcol("[loaded kernel]\n",2);
    if(cpuid_supp()){
    	kprintcol("[CPUID instruction supported]\n",5);
    
    char buf[16];
    u32 a=0,b,c,d;
    cpuid(&a,&b,&c,&d);
    *(int*)buf = b;
    *(int*)(buf+4) = d;
    *(int*)(buf+8) = c;
    buf[13]=0;
    kprintcol("[CPU vendor: ", 5);
    kprintcol(buf,5);
    kprintcol("]\n",5);
	}
    //init_timer(100);
    init_keyboard();
    kprintcol("[inited keyboard]\n",2);

    __asm__("hlt");
    return 0;
}


 

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        __asm__("hlt");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n[root@rabu /] # ");
}




