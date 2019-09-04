#include "timer.h" 
#include "../drivers/screen.h"
#include "isr.h"
#include "../drivers/ports.h"
#include "../kernel/kernel.h"

//u32 tick = 0;

static void timer_callback(registers_t regs) {
    next_pixel(); 
    
}

void init_timer(u32 freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    u32 divisor = 1193180 / freq;
    u8 low  = low_8(divisor);
    u8 high = high_8(divisor);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}