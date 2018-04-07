
%macro putc16 1
	mov al, %1
	int 10h
%endmacro



;#####################################################

print_str16:
	pusha
	mov ah, 0x0e
print16_start:
	mov al, [bx]
	cmp al, 0
	je print16_finish
 	putc16 al
	inc bx
	jmp print16_start

print16_finish:
	popa
	ret

;#####################################################

print_newline16:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret

;#####################################################

print_hex16:
	pusha 

 	mov cx,5
	mov ah, 0x0e 
	putc16 '0'
	putc16 'x'
print_hex16_loop4:
	rol bx,4
	dec cx
	jz print_hex16_end
	mov dl,bl
	and dl, 0xf
	cmp dl, 0x09
	jle print_hex16_isnum
	cmp dl,0x0f
	jle print_hex16_isalpha
	jmp print_hex16_end
	
print_hex16_isnum:
	add dl,'0'
	putc16 dl 
	jmp print_hex16_loop4

print_hex16_isalpha:
	add dl,'A'-0xa
	putc16 dl 
	jmp print_hex16_loop4

print_hex16_end:
	popa
	ret




