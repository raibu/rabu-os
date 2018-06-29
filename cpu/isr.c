#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../drivers/ports.h"
#include "../drivers/keyboard.h"
#include "../cpu/timer.h"

isr_t interrupt_handlers[256];
/* Can't do this with a loop because we need the address
 * of the function names 
 * ##################################################
 * of course we can do this
 * */
uint isr_array[] = {
(u32)isr0,
(u32)isr1,
(u32)isr2,
(u32)isr3,
(u32)isr4,
(u32)isr5,
(u32)isr6,
(u32)isr7,
(u32)isr8,
(u32)isr9,
 (u32)isr10,
 (u32)isr11,
 (u32)isr12,
 (u32)isr13,
 (u32)isr14,
 (u32)isr15,
 (u32)isr16,
 (u32)isr17,
 (u32)isr18,
 (u32)isr19,
 (u32)isr20,
 (u32)isr21,
 (u32)isr22,
 (u32)isr23,
 (u32)isr24,
 (u32)isr25,
 (u32)isr26,
 (u32)isr27,
 (u32)isr28,
 (u32)isr29,
 (u32)isr30,
 (u32)isr31
};
uint irq_array[] = {
(u32)irq0,
(u32)irq1,
(u32)irq2,
(u32)irq3,
(u32)irq4,
(u32)irq5,
(u32)irq6,
(u32)irq7,
(u32)irq8,
(u32)irq9,
(u32)irq10,
(u32)irq11,
(u32)irq12,
(u32)irq13,
(u32)irq14,
(u32)irq15
};



void isr_install() {
  uint i=0;
  for(; i<32; i++)
    set_idt_gate(i, isr_array[i]);

    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0); 

    // Install the IRQs 
    // the same
    for(;i<48; i++)
      set_idt_gate(i, irq_array[i-IRQ0]);

    set_idt(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault", 
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t r) {
    kprint("received interrupt: ");
    char s[16];
    itoa(r.int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r.int_no]);
    kprint("\n");
}



void register_interrupt_handler(u8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40) port_byte_out(0xA0, 0x20); /* slave */
    port_byte_out(0x20, 0x20); /* master */

    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}

void irq_install() {
    /* Enable interruptions */
    __asm__("sti");
    /* IRQ0: timer */
    init_timer(50);
    /* IRQ1: keyboard */
    init_keyboard();
}
