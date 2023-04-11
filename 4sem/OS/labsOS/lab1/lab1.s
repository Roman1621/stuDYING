org 100h
jmp start

%define end_str	0xD, 0xA, '$'

section .data

	strend   	db end_str
	pc_hex_str 	db 'Unkown type of PC: 0x', '$'
	user_ser_str	db 'User`s serial number: ', '$'
    oem_ser_str	db 'OEM`s serial number: ', '$'
	dos_ver_str	db 'version of DOS: ', '$'
	pc_type_str	db 'type of PC: ', '$'

	pcstr0	db 'PS2 model 80', end_str	; 0xF8
	pcstr1	db 'PC Convertible', end_str	; 0xF9
	pcstr2	db 'PS2 model 30', end_str	; 0xFA
	pcstr3	db 'PC/XT', end_str		; 0xFB
	pcstr4	db 'PS2 module 50 or 60', end_str; 0xFC
	pcstr5  db 'PCjr', end_str		; 0xFD
	pcstr6	db 'PC/XT', end_str		; 0xFE
	pcstr7	db 'PC', end_str			; 0xFF

	pc_str_table:
	dw pcstr0
    dw pcstr1
    dw pcstr2
    dw pcstr3
    dw pcstr4
    dw pcstr5
    dw pcstr6
    dw pcstr7

section .text
output_of_hex_byte:
	push ax
	push dx

	mov  dl, cl
	shr  dl, 4
	cmp  dl, 10
	jae  .hex1
	add  dl, '0'
	jmp .out
	.hex1:
	sub  dl, 10
	add  dl, 'A'
	.out:
	mov  ah, 0x2
	int  0x21

	mov  dl, cl
	and  dl, 0x0F
	cmp  dl, 10
	jae  .hex_2
	add  dl, '0'
	jmp .out2
	.hex_2:
	sub  dl, 10
	add  dl, 'A'
	.out2:
	mov  ah, 0x2
	int  0x21

	pop dx
	pop ax
	ret

output_of_dec_byte.outstr db '000', '$'
output_of_dec_byte:
	push ax
	push bx
	push dx
	push di

	; reset output string
	mov  byte [output_of_dec_byte.outstr], '0'
	mov  byte [output_of_dec_byte.outstr + 1], '0'
	mov  byte [output_of_dec_byte.outstr + 2], '0'

	mov  di, 2

	.conv_dec:
		xor  dx, dx
		mov  ax, cx
		mov  bx, 10
		div  bx	
		mov  cx, ax
		add  dl, '0'
		mov  [output_of_dec_byte.outstr + di], dl
		dec  di
	cmp cx, 0
	jne .conv_dec

	mov  dx, output_of_dec_byte.outstr + 1
	mov  ah, 0x9
	int 0x21

	pop di
	pop dx
	pop bx
	pop ax

	ret

output_type_of_pc:
	push ax
	push dx

	cmp  cx, 0xF8
	jb   .output_of_hex

	.output_of_string:
	mov  ah, 0x9
	mov  dx, pc_type_str
	int  0x21
	sub  cx, 0xF8
	mov  bx, cx
	shl  bx, 1

	mov  dx, [pc_str_table + bx]	
	mov  ah, 0x9			
	int 0x21
	jmp .finish

	.output_of_hex:
	mov  dx, pc_hex_str
	mov  ah, 0x9
	int 0x21
	call output_of_hex_byte
	mov  dx, strend
	int 0x21

	.finish:
	pop dx
	pop ax
	ret

output_info_of_dos:
	push  ax
	push  bx
	push  cx
	push  dx

	mov  ah, 0x30
	int  0x21
	push cx
	push bx

	mov  ah, 0x9
	mov  dx, dos_ver_str
	int  0x21

	xor  cx, cx
	mov  cl, al
	call output_of_dec_byte
	mov  cl, ah
	mov  ah, 0x2
	mov  dl, '.'
	int  0x21
	call output_of_dec_byte
	mov  ah, 0x9
	mov  dx, strend
	int  0x21

	mov  ah, 0x9
	mov  dx, oem_ser_str
	int  0x21
	pop  bx
	mov  cl, bh
	call output_of_hex_byte
	mov  ah, 0x9
	mov  dx, strend
	int  0x21

	mov  ah, 0x9
	mov  dx, user_ser_str
	int  0x21
	pop  dx
	mov  cl, bl
	call output_of_hex_byte
	mov  cl, dh
	call output_of_hex_byte
	mov  cl, dl
	call output_of_hex_byte
	mov  ah, 0x9
	mov  dx, strend
	int  0x21

	pop  dx
	pop  cx
	pop  bx
	pop  ax
	ret


start:
	mov  bx, ds	
	mov  cx, 0xF000
	mov  ds, cx	
	xor  cx, cx
	mov  cl, [0xFFFE]
	mov  ds, bx	

	call output_type_of_pc

	call output_info_of_dos

	int  0x20