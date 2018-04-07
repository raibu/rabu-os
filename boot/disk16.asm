


disk_operation16: ;; load 'dh' sectors from drive 'dl' into ES:BX
	pusha
	push ax
	int 13h
	jc disk_load16_error
	pop dx
	cmp dl,al 
	jne disk_load16_sectors_error
	popa 
	ret 

disk_load16_error: 
	putsn16 DISK16_ERROR 
	mov dh,ah
	puthex16 dx 
	jmp disk_load16_loop


disk_load16_sectors_error:
	putsn16 SECTORS16_ERROR
	puthex16 dx
	call print_newline16
	puthex16 ax


disk_load16_loop:
	jmp $




DISK16_ERROR: db "Disk read error", 0
SECTORS16_ERROR: db "Incorrect number of sectors read", 0