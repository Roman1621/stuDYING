overlay2 segment
	assume cs:overlay2, ds:nothing, ss:nothing, es:nothing

main proc far
	push ax
	push cx
	push dx
	push ds
	push es

	mov  ax, cs
	mov  ds, ax

	lea  dx, load_msg
	mov  ah, 9h
	int  21h

	lea  dx, seg_msg
	int  21h
	mov  cx, cs
	call output_of_hex_word
	lea  dx, nl_str
	int  21h

	.ret:
	pop  es
	pop  ds
	pop  dx
	pop  cx
	pop  ax
	retf
main endp

output_of_hex_byte proc near
        push ax
        push bx
	push cx
        push dx

        mov  bl, cl

        push cx
        mov  al, bl
        mov  cl, 4
        shr  al, cl
        mov  bl, al
        pop  cx

        cmp  bl, 10
        jae  .add_hex_1
        add  bl, '0'
        jmp .out_1
        .add_hex_1:
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
        jae  .add_hex_2
        add  bl, '0'
        jmp .out_2
        .add_hex_2:
        sub  bl, 10
        add  bl, 'A'
        .out_2:
        xor  ax, ax
        mov  ah, 2h
        mov  dl, bl
        int  21h

        pop  dx
	pop  cx
        pop  bx
        pop  ax
        ret
output_of_hex_byte endp

output_of_hex_word proc near
	push bx

	push cx
	mov  bx, cx
	mov  cl, 8h
	shr  bx, cl
	mov  cx, bx
	call output_of_hex_byte
	pop  cx
	call output_of_hex_byte

	pop  bx
	ret
output_of_hex_word endp

	nl_str	db 0Dh, 0Ah, '$'
	load_msg	db 'Overlay #2 is loaded', 0Dh, 0Ah, '$'
	seg_msg		db 'Overlay #2 segment: 0x$'

overlay2 ends
end main