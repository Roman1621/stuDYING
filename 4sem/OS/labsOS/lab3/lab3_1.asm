testpc segment
	assume cs:testpc, ds:testpc, es:nothing, ss:nothing
	org 100h
start: jmp begin

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
	and  bl, 0fh
	cmp  bl, 10
	jae  .addhex_2
	add  bl, '0'
	jmp .out_2
	.addhex_2:
	sub  bl, 10
	add  bl, 'A'
	.out_2:
	mov  ah, 2h
	mov  dl, bl
	int  21h

	pop dx
	pop bx
	pop ax
	ret
output_of_hex_byte endp

output_of_hex_word proc near
	push cx
	mov  cl, ch
	call output_of_hex_byte
	pop  cx
	call output_of_hex_byte

	ret
output_of_hex_word endp

output_of_dec_word proc near
	push ax
	push bx
	push dx
	push di


	xor  di, di
	.reset_loop:
		mov  [output_of_dec_word_outstr + di], '0'
	inc  di
	cmp  di, 5
	jne .reset_loop


	mov  di, 5

	.div_loop:
		xor  dx, dx
		mov  ax, cx
		mov  bx, 10
		div  bx
		mov  cx, ax
		add  dl, '0'
		mov  [output_of_dec_word_outstr + di], dl
	dec  di
	cmp  cx, 0
	jne .div_loop

	lea  dx, output_of_dec_word_outstr + 1
	add  dx, di
	mov  ah, 9h
	int 21h

	pop  di
	pop  dx
	pop  bx
	pop  ax

	ret
output_of_dec_word endp

output_of_dec_dword proc near
	push di

	mov  ax, dx
	mov  dx, cx
	mov  di, 10000
	div  di
	cmp  ax, 0h
	je   .print_2nd_part
	mov  cx, ax
	call output_of_dec_word
	.print_2nd_part:
	mov  cx, dx
	call output_of_dec_word

	pop  di
	ret
output_of_dec_dword endp

output_of_str_nullterm proc near
        push ax
	push bx
        push cx
        push dx

	xor  bx, bx
	.seek_loop:
		mov  cl, [di + bx]
		cmp  cl, 0
		je  .seek_loop_end
		inc  bx
		jmp .seek_loop
	.seek_loop_end:

        mov  cl, [di + bx]
        mov  byte ptr [di + bx], 24h	
        mov  dx, di
        mov  ah, 9h
        int  21h

        mov  [di + bx], cl

        pop  dx
        pop  cx
	pop  bx
        pop  ax
        ret
output_of_str_nullterm endp


output_of_avl_memory proc near
	push ax
	push bx
	push cx
	push dx
	push di

	mov  ah, 4Ah
	mov  bx, 0ffffh
	int  21h

	mov  ah, 9h
	lea  dx, av_mem_str
	int  21h

	mov  ax, bx
	mov  di, 16
	mul  di
	mov  cx, dx
	mov  dx, ax

	call output_of_dec_dword

	mov  ah, 9h
	lea  dx, av_mem_str2
	int  21h

	pop  di
	pop  dx
	pop  cx
	pop  bx
	pop  ax
	ret
output_of_avl_memory endp

output_of_ext_memory proc near
	push ax
	push cx
	push dx

	mov  al, 30h
	out  70h, al
	in   al, 71h
	mov  cl, al
	mov  al, 31h
	out  70h, al
	in   al, 71h
	mov  ch, al

	mov  ah, 9h
	lea  dx, ext_mem_str
	int  21h
	call output_of_dec_word
	lea  dx, ext_mem_str2
	int  21h

	pop  dx
	pop  cx
	pop  ax
	ret
output_of_ext_memory endp

output_of_mcbs proc near
	push ax
	push bx
	push cx
	push dx
	push di
	push es

	mov  ah, 52h
	int  21h
	mov  di, es:[bx-2]
	mov  es, di

	.mcb_loop:
		mov  ah, 9h

		lea  dx, mcb_psp_str
		int  21h
		mov  cx, es:[1h]
		call output_of_hex_word
		lea  dx, str_end
		int  21h

		lea  dx, mcb_size_str
		int  21
		mov  ax, es:[3h]
		mov  di, 16
		mul  di
		mov  cx, dx
		mov  dx, ax
		call output_of_dec_dword
		mov  ah, 9h
		lea  dx, mcb_size_str2
		int  21h

		lea  dx, mcb_name_str
		int  21h
		mov  cx, ds
		mov  bx, es
		mov  ds, bx
		mov  di, 8h
		mov  bx, 8h
		call output_of_str_nullterm
		mov  ds, cx
		lea  dx, str_end
		int  21h

		mov  cl, 4Dh
		cmp  es:[0h], cl
		jne .mcb_loop_end
		mov  di, es:[3h]
		mov  ax, es
		add  di, ax
		inc  di
		mov  es, di
	jmp  .mcb_loop
	.mcb_loop_end:

	pop  es
	pop  di
	pop  dx
	pop  cx
	pop  bx
	pop  ax
	ret
output_of_mcbs endp

begin:
	call output_of_avl_memory
	call output_of_ext_memory
	lea  dx, str_end
	mov  ah, 9h
	int  21h
	lea  dx, mcb_str
	int  21h
	call output_of_mcbs

	int  20h

	output_of_dec_word_outstr db '000000', '$'

	str_end   	    db 0Dh, 0Ah, '$'
	av_mem_str	    db 'Amount of available memory: ', '$'
	av_mem_str2	    db ' B', 0Dh, 0Ah, '$'
	ext_mem_str	    db 'Amount of extended memory: ', '$'
	ext_mem_str2	db ' kB', 0Dh, 0Ah, '$'

	mcb_str		    db 'MCB list:', 0Dh, 0Ah, '$'
	mcb_type_str	db 'MCB type: 0x', '$'
	mcb_psp_str	    db 'owner PSP segment address: 0x', '$'
	mcb_size_str	db 'memory chunk size: ', '$'
	mcb_size_str2	db ' B', 0Dh, 0Ah, '$'
	mcb_name_str	db 'Program name: ', '$'

testpc ends
end start