
[org 0x7c00] ; tell the assembler that our offset is bootsector code

%include "defs.asm"

%macro puts16 1
	push bx
	mov bx, %1
	call print_str16
	pop bx
%endmacro

%macro putsn16 1
	push bx
	mov bx, %1
	call print_str16
	pop bx
	call print_newline16
%endmacro

%macro puthex16 1
	push bx
	mov bx, %1
	call print_hex16
	pop bx
%endmacro


%macro disk_read16 6 ;SECS, SEC, CYL, HEAD, DRIVE, BUFPTR
	pusha
		mov ah, D_READ
		mov al, %1
		mov cl, %2
		mov ch, %3
		mov dh, %4
		mov dl, %5
		mov bx, %6
		call disk_operation16
	popa
%endmacro

KERNEL_OFFSET equ 0x1000

;mov [BOOT_DRIVE], byte 0x80 
mov bp, 0x9000 ; set the stack safely away from us
mov sp, bp
putsn16 MSG_REAL_MODE
call load_kernel
call switch_to_pm


jmp $



[bits 16]
load_kernel:
    putsn16 MSG_LOAD_KERNEL
    disk_read16 31, 2, 0, 0, 0x0, KERNEL_OFFSET
    ret


; remember to include subroutines below the hang
%include "print16.asm"
%include "disk16.asm"



[bits 32]

%macro puts32 1
    push ebx
    mov ebx, %1
    call print_string_pm
    pop ebx
%endmacro

BEGIN_PM: ; after the switch we will get here
    ;puts32 MSG_PROT_MODE
    call KERNEL_OFFSET
    jmp $

;BOOT_DRIVE db 0 ; It is a good idea to store it in memory because 'dl' may get overwritten
MSG_REAL_MODE db "Started in 16bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel", 0

%include "gdt32.asm"
%include "switch1632.asm"
%include "print32.asm"

; padding and magic number
times 510-($-$$) db 0
;db 0,0,0,0,0
dw 0xaa55

