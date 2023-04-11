code segment
	assume cs:code, ds:data, ss:_stack

output_of_hex_byte proc near
	push ax
	push bx
	push dx

	mov  bl, cl

	push cx
	mov  al, bl
	mov  cl, 4
	shr  al, cl
	mov  bl, al
	pop  cx

	cmp  bl, 10
	jae  .addhex_1
	add  bl, '0'
	jmp .out_1
	.addhex_1:
	sub  bl, 10
	add  bl, 'A'
	.out_1:
	xor  ax, ax
	mov  ah, 2h
	mov  dl, bl
	int  21h

	mov  bl, cl

	push cx
	mov  al, bl
	mov  cl, 4
	shl  al, cl
	shr  al, cl
	mov  bl, al
	pop  cx

	cmp  bl, 10
	jae  .addhex_2
	add  bl, '0'
	jmp .out_2
	.addhex_2:
	sub  bl, 10
	add  bl, 'A'
	.out_2:
	xor  ax, ax
	mov  ah, 2h
	mov  dl, bl
	int  21h

	pop dx
	pop bx
	pop ax
	ret
output_of_hex_byte endp

output_of_nullterm_str proc near
	push ax
	push dx

	mov  ah, 2h
	.nullterm_loop:
		mov  dl, es:[di]
		cmp  dl, 0h
		je  .nullterm_end

		int  21h
		inc  di
		jmp  .nullterm_loop
	.nullterm_end:

	pop  dx
	pop  ax
	ret
output_of_nullterm_str endp

set_prm proc near
	mov  ax, es:[2Ch]
	mov  param_block, ax
	mov  param_block + 2, es
	mov  param_block + 4, 80h
set_prm endp

free_mem proc near
	push ax
	push bx
	push cx

	lea  bx, exec_end
	mov  ax, es
	sub  bx, ax
	mov  cl, 4
	shr  bx, cl
	inc  bx

	mov  ah, 4Ah
	int  21h
	jnc  .free_mem_cleanup

	lea  dx, str_err_dos7
	cmp  ax, 7h
	je  .print_err
	lea  dx, str_err_dos8
	cmp  ax, 8h
	je  .print_err
	lea  dx, str_err_dos9
	cmp  ax, 9h
	je  .print_err

	jmp .free_mem_cleanup
	.print_err:
	mov  ah, 09h
	int  21h

	.free_mem_cleanup:
	pop  cx
	pop  bx
	pop  ax
	ret
free_mem endp

set_mod_name proc near
	push ax
	push bx
	push cx
	push dx
	push es

	mov  es, es:[2Ch]
	xor  di, di
	.str_nullterm_loop:
		mov  al, es:[di]
		cmp  al, 0h
		je   .str_nullterm_end
		inc  di
		jmp  .str_nullterm_loop
	.str_nullterm_end:
	inc  di
	mov  al, es:[di]
	cmp  al, 0h
	jne  .str_nullterm_loop

	add  di, 3h
	mov  cx, di

	xor  bx, bx
	.mpath_write_loop:
		mov  al, es:[di]
		cmp  al, 0h
		je  .mpath_write_end
		mov  mod_path[bx], al
		inc  di
		inc  bx
		jmp  .mpath_write_loop
	.mpath_write_end:

	.mpath_slash_loop:
		mov  al, mod_path[bx]
		cmp  al, '\'
		je   .mpath_slash_end
		dec  bx
		jmp  .mpath_slash_loop
	.mpath_slash_end:

	inc  bx
	xor  di, di
	.lpath_write_loop:
		mov  al, mod_fname[di]
		cmp  al, 0h
		je  .lpath_write_end
		mov  mod_path[bx], al
		inc  di
		inc  bx
		jmp  .lpath_write_loop
	.lpath_write_end:

	lea  dx, start_str
	mov  ah, 09h
	int  21h

	lea  di, mod_path
	mov  cx, ds
	mov  es, cx
	call output_of_nullterm_str

	lea  dx, newline_str
	int  21h

	pop  es
	pop  dx
	pop  cx
	pop  bx
	pop  ax
	ret
set_mod_name endp

start_mod proc near
	push ax
	push bx
	push dx

	lea  dx, newline_str
	mov  ah, 09h
	int  21h

	push ds
	push es
	mov  backup_sp, sp
	mov  backup_ss, ss
	mov  ax, ds
	mov  es, ax

	lea  dx, mod_path
	lea  bx, param_block
	mov  ax, 4B00h
	int 21h

	mov  ss, backup_ss
	mov  sp, backup_sp
	pop  es
	pop  ds

	jc  .start_mod_cleanup

	.ret_handle:
	lea  dx, newline_str
	mov  ah, 09h
	int  21h

	mov  ax, 4D00h 
	int  21h

	mov  cx, ax
	lea  dx, str_ret_dos0
	cmp  ch, 0h
	je   .print_ret
	lea  dx, str_ret_dos1
	cmp  ch, 1h
	je   .print_ret
	lea  dx, str_ret_dos2
	cmp  ch, 2h
	je   .print_ret
	jmp  .start_mod_cleanup

	.print_ret:
	mov  ah, 09h
	int  21h

	cmp  ch, 0h
	jne  .start_mod_cleanup
	call output_of_hex_byte

	clc
	.start_mod_cleanup:
	jnc  .ret
	lea  dx, str_err_dosmodl
	mov  ah, 09h
	int  21h

	.ret:
	lea  dx, newline_str
	mov  ah, 09h
	int  21h

	pop  dx
	pop  bx
	pop  ax
	ret
start_mod endp


main proc far
	xor  ax, ax
	push ax
	mov  ax, data
	mov  ds, ax

	call free_mem
	call set_prm
	call set_mod_name
	call start_mod

	xor  al, al
	mov  ah, 4Ch
	int 21h
main endp

exec_end:
code ends

_stack segment stack
	dw 64 dup(?)
_stack ends

data segment
	param_block	dw 0
			dd 0
			dd 0
			dd 0

	backup_ss 	dw 0
	backup_sp 	dw 0

	mod_path 	db 64 dup (0)
	mod_fname 	db 'LAB2.COM', 0h

	newline_str	db 0Dh, 0Ah, '$'

	start_str	db 'Launching module $'

	str_err_dosmodl	db 'Error: cant find module file$'
    str_ret_dos0	db 'Normal termination, code: 0x$'
	str_ret_dos1	db 'Ctrl-Break termination$'
	str_ret_dos2	db 'Critical device error$'
	str_ret_dos3	db 'Termination by int 21, 31$'
	str_err_dos7	db 'Error: memory control blocks destroyed$'
	str_err_dos8	db 'Error: insufficient memory$'
	str_err_dos9	db 'Error: invalid memory block address$'

data ends

end main