_stack segment stack
	dw 64 dup(?)
_stack ends

data segment
	over_path		db 64 dup (0)
	over_fname1		db 'OVERLAY1.COM', 0h
	over_fname2		db 'OVERLAY2.COM', 0h

	launch_params		dw 0, 0
	launch_addr		dd 0

        nl_str                  db 0Dh, 0Ah, '$'
        load_str      	        db 'Loading over $'

	str_err_dosunknown	db ': unknown error', 0Dh, 0Ah, '$'
	str_err_dos2		db 'Error: file not found', 0Dh, 0Ah, '$'
	str_err_dos3		db 'Error: path not found', 0Dh, 0Ah, '$'
        ;str_err_dos7     	db 'Error: memory control blocks destroyed', 0Dh, 0Ah, '$'
        ;str_err_dos7     	db m'$'
        str_err_dos8     	db 'Error: insufficient memory', 0Dh, 0Ah, '$'
        str_err_dos9     	db 'Error: invalid memory block address', 0Dh, 0Ah, '$'
	str_err_dos12		db 'Error: no more files (file not found)', 0Dh, 0Ah, '$'

	str_err_mem		db 'Error: could not allocate memory$'

	set_over_name_last	dw 0

	over_file_data	    db 64 dup (0)
data ends

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

        pop dx
        pop bx
        pop ax
        ret
output_of_hex_byte endp

output_of_nltrm_str proc near
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
output_of_nltrm_str endp

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

        ;lea  dx, str_err_dos7
        ;cmp  ax, 7h
        ;je  .print_err
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

set_over_name proc near
        push ax
        push bx
        push cx
        push dx
        push es
	push di

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
                mov  over_path[bx], al
                inc  di
                inc  bx
                jmp  .mpath_write_loop
        .mpath_write_end:

        .mpath_slash_loop:
                mov  al, over_path[bx]
                cmp  al, '\'
                je   .mpath_slash_end
                dec  bx
                jmp  .mpath_slash_loop
        .mpath_slash_end:

        inc  bx
	mov  di, si
        .lpath_write_loop:
                mov  al, [di]
                cmp  al, 0h
                je  .lpath_write_end
                mov  over_path[bx], al
                inc  di
                inc  bx
                jmp  .lpath_write_loop
        .lpath_write_end:
	mov  al, 0h
	mov  over_path[bx], al

        lea  dx, load_str
        mov  ah, 09h
        int  21h

	cmp  set_over_name_last, si
	je   .ret2
	lea  di, over_path
	mov  cx, ds
	mov  es, cx
	call output_of_nltrm_str

        lea  dx, nl_str
        int  21h

	.ret2:
	mov  set_over_name_last, si
	pop  di
        pop  es
        pop  dx
        pop  cx
        pop  bx
        pop  ax
        ret
set_over_name endp

get_size_of_over proc near
	push ax
	push bx
	push cx
	push dx
	push si

	mov  ah, 1Ah
	lea  dx, over_file_data
	int  21h

	mov  ah, 4Eh
	lea  dx, over_path
	mov  cx, 0h
	int  21h
	jnc  .ofile_found

	lea  dx, str_err_dos2
	cmp  ax, 2h
	je   .print_err2
	lea  dx, str_err_dos3
	cmp  ax, 3h
	je  .print_err2
	lea  dx, str_err_dos12
	cmp  ax, 12h
	je  .print_err2
	lea  dx, str_err_dosunknown
	mov  cl, al
	call output_of_hex_byte

	.print_err2:
	mov  ah, 9h
	int  21h
	jmp  .ret

	.ofile_found:
	mov  si, offset over_file_data
	add  si, 1Ah
	mov  bx, [si]
	mov  cl, 4
	shr  bx, cl
	mov  ax, [si + 2]
	mov  cl, 12
	shl  ax, cl
	add  bx, ax
	add  bx, 2
	mov  ah, 48h
	int  21h
	jnc  .set_launch_params

	lea  dx, str_err_mem
	mov  ah, 9h
	int  21h
	jmp  .ret

	.set_launch_params:
	mov  launch_params, ax
	mov  launch_params + 2, ax

	.ret:
	pop  si
	pop  dx
	pop  cx
	pop  bx
	pop  ax
	ret
get_size_of_over endp

load_over proc near
	push ax
	push dx
	push es

	lea  dx, over_path
	mov  ax, ds
	mov  es, ax
	lea  bx, launch_params
	mov  ax, 4B03h
	int  21h
	jnc  .over_launch

	lea  dx, str_err_dos2
	cmp  ax, 2h
	je   .print_err3
	lea  dx, str_err_dos3
	cmp  ax, 3h
	je   .print_err3
	lea  dx, str_err_dos8
	cmp  ax, 8h
	je   .print_err3
	lea  dx, str_err_dosunknown
	mov  cl, al
	call output_of_hex_byte

	.print_err3:
	mov  ah, 9h
	int  21h
	jmp  .over_cleanup

	.over_launch:
	mov  ax, launch_params
	mov  word ptr launch_addr + 2, ax
	call launch_addr
	mov  es, ax
	mov  ah, 49h
	int  21h

	.over_cleanup:
	pop  es
	pop  dx
	pop  ax
	ret
load_over endp


main proc far
	xor  ax, ax
	push ax
	mov  ax, data
	mov  ds, ax

	call free_mem

	lea  si, over_fname1
	call set_over_name
	call get_size_of_over
	call set_over_name
	call load_over

	lea  si, over_fname2
	call set_over_name
	call get_size_of_over
	call load_over

	xor  al, al
	mov  ah, 4Ch
	int  21h
main endp

exec_end:
code ends
end main