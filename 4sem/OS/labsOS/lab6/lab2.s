org 100h
jmp start

section .data
	%define endstr	0xD, 0xA, '$'
	str_end   	     db endstr
	mem_lmt_str	     db 'First byte of unadressable memory: 0x', '$'
	envrmnt_adr_str	 db 'Environment segment address: 0x', '$'
	cmd_arg_str	     db 'Command line arguments:', '$'
	envrmnt_cont_str db 'Environment content:', endstr
	path_mod_str	 db 'Path to module: ', '$'

section .text
output_of_hex_byte:
	push ax
	push dx

	mov  dl, cl	
	shr  dl, 4
	cmp  dl, 10
	jae  .hex_1
	add  dl, '0'
	jmp .out_1
	.hex_1:
	sub  dl, 10
	add  dl, 'A'
	.out_1:
	mov  ah, 0x2
	int  0x21

	mov  dl, cl
	and  dl, 0x0F
	cmp  dl, 10
	jae  .hex_2
	add  dl, '0'
	jmp .out_2
	.hex_2:
	sub  dl, 10
	add  dl, 'A'
	.out_2:
	mov  ah, 0x2
	int  0x21

	pop dx
	pop ax
	ret

output_of_hex_word:
	push cx
	shr  cx, 8
	call output_of_hex_byte
	pop  cx
	call output_of_hex_byte
	ret

output_of_lmtd_str:
	push ax
	push cx
	push dx

	mov  cl, [di + bx]
	mov  byte [di + bx], '$'

	mov  dx, di
	mov  ah, 0x9
	int  0x21

	mov  [di + bx], cl

	pop  dx
	pop  cx
	pop  ax
	ret

output_of_nltrm_str:
	push ax
	push bx
	push dx

	xor  ax, ax
	xor  bx, bx
	.null_term:
		cmp  byte[di + bx], 0x0
		je   .null_term_end
		inc  bx
		jmp  .null_term
	.null_term_end:
	mov  byte [di + bx], '$'
	mov  ah, 0x9
	mov  dx, di
	int  0x21
	mov  byte [di + bx], 0x0

	pop  dx
	pop  bx
	pop  ax
	ret

output_of_env:
	push ax
	push bx
	push cx
	push dx

	mov  ah, 0x9
	mov  cx, ds	
	mov  ds, [0x2C]
	xor  di, di	

	.string_loop:
	xor  bx, bx	
	.null_term:
		cmp  byte [di + bx], 0x0
		je   .null_term_end
		inc  bx
		jmp  .null_term
	.null_term_end:
	mov  byte [di + bx], '$'
	mov  dx, di
	int  0x21
	mov  byte [di + bx], 0x0

	cmp  bx, 0x0
	je   .ret
	inc  bx
	add  di, bx

	mov  ds, cx
	mov  dx, str_end
	int  0x21
	mov  ds, [0x2C]
	jmp .string_loop

	.ret:
	add  di, 3
	mov  ds, cx
	pop  dx
	pop  cx
	pop  bx
	pop  ax
	ret

output_of_psp:
	push ax
	push cx
	push dx
	push di

	mov  ah, 0x9
	mov  dx, mem_lmt_str
	int  0x21
	mov  cx, [0x2]
	call output_of_hex_word
	mov  dx, str_end
	int  0x21

	mov  dx, envrmnt_adr_str
	int  0x21
	mov  cx, [0x2C]
	call output_of_hex_word
	mov  dx, str_end
	int  0x21

	mov  dx, cmd_arg_str
	int  0x21
	mov  di, 0x81
	mov  bl, [0x80]
	call output_of_lmtd_str
	mov  dx, str_end
	int  0x21

	mov  dx, envrmnt_cont_str
	int  0x21
	call output_of_env

	mov  dx, path_mod_str
	int  0x21
	mov  cx, ds
	mov  ds, [0x2C]
	call output_of_nltrm_str
	mov  ds, cx
	mov  dx, str_end
	int  0x21

	pop di
	pop dx
	pop cx
	pop ax
	ret


start:
	call output_of_psp
	mov  ah, 0x1
	int  0x21
	mov  ah, 0x4C
	int  0x21