[bits 32] ; using 32-bit protected mode



; this is how constants are defined
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f ; the color byte for each character

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY
    add edx, [cur_pos]
    add edx, [cur_pos]

print_string_pm_loop:
    mov al, [ebx] ; [ebx] is the address of our character
    mov ah, WHITE_ON_BLACK
    cmp al, 0 ; check if end of string
    je print_string_pm_done

    mov [edx], ax ; store character + attribute in video memory
    add ebx, 1 ; next char
    add edx, 2 ; next video memory position
    inc word [cur_pos]
    cmp [cur_pos], word 25*80-1
    jne print_string_pm_loop
    mov [cur_pos], word 0
    mov edx, VIDEO_MEMORY
    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret


; print_newline_pm:
;     pusha
;     mov dl, 20h
;     mov dh, WHITE_ON_BLACK ; dx 3abit
;     mov esi, VIDEO_MEMORY
;     add esi, [cur_pos]
;     add esi, [cur_pos]
;     mov ax, [cur_pos]
;     mov bh, 80
;     div bh
;     mov bl, 80
;     sub bl, ah
;     inc bl
; print_newline_pm_fill_loop:
;     dec bl
;     jz print_newline_pm_end
;     mov [esi], word dx 
;     add esi,2
;     inc word [cur_pos]
;     cmp [cur_pos], word 25*80-1
;     jne print_newline_pm_fill_loop
;     mov [cur_pos], word 0
;     mov esi, VIDEO_MEMORY
;     jmp print_newline_pm_fill_loop

; print_newline_pm_end:
;     popa
;     ret


    
    





cur_pos:
    dw 0000h  