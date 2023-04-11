
code segment
	assume cs:code, ds:data, ss:astack

int_hndl proc far
	jmp  .int_start

	backup_psp	dw ?
	backup_ip	dw 0
	backup_cs	dw 0
	int9_vec	dd ?
	int_magic	dw 0BEEFh

	backup_ss	dw ?
	backup_sp	dw ?
	backup_ax	dw ?
	int_stack	dw 32 dup (?)
	int_stack_end	dw ?
	teststr		db 'key "Z" was pressed'
	required_key	db 2Ch

	.int_start:

	mov  backup_ss, ss
	mov  backup_sp, sp
	mov  backup_ax, ax
	mov  ax, cs
	mov  ss, ax
	mov  sp, offset int_stack_end
	push ax
	push bx
	push cx
	push dx

	in   al, 60h
	cmp  al, required_key
	je   .hint_hndl

	pop  dx
	pop  cx
	pop  bx
	pop  ax

	mov  ax, backup_ss
	mov  ss, ax
	mov  ax, backup_ax
	mov  sp, backup_sp
	jmp  dword ptr cs:[int9_vec]

	.hint_hndl:
	in   al, 61h
	mov  ah, al
	or   al, 80h
	out  61h, al
	xchg ah, al
	out  61h, al
	mov  al, 20h
	out  20h, al

	.write_kb_buf:
	mov  ah, 05h
	mov  cl, 'Z'
	mov  ch, 0h
	int  16h
	or   al, al
	jz   .no_overflow

	push ds
	mov  ax, 0040h
	mov  ds, ax
	mov  ax, [001Ah]
	mov  bx, 001Ch
	mov  [bx], ax
	pop  ds
	jmp .write_kb_buf

	.no_overflow:
        push es
        push bp
        mov  ax, seg teststr
        mov  es, ax
        mov  ax, offset teststr
        mov  bp, ax
        mov  al, 0h  
        mov  ah, 13h   
        mov  bh, 0h    
        mov  bl, 1h
        mov  cx, 19   
        mov  dh, 0h 
        mov  dl, 0h   
        int  10h
        pop  bp
        pop  es

	.int_exit:
	pop  dx
	pop  cx
	pop  bx
	pop  ax

	mov  ax, backup_ss
	mov  ss, ax
	mov  ax, backup_ax
	mov  sp, backup_sp
	iret
resident_end:
int_hndl endp

load_int proc near
	push ax
	push bx
	push dx

	mov  ah, 35h
	mov  al, 09h
	int  21h
	mov  backup_psp, ds
	mov  backup_cs, es
	mov  backup_ip, bx
	mov  word ptr int9_vec + 2, es
	mov  word ptr int9_vec, bx

	push ds
	mov  dx, offset int_hndl
	mov  ax, seg int_hndl
	mov  ds, ax
	mov  ah, 25h
	mov  al, 09h
	int  21h
	pop  ds

	lea  dx, resident_end
	mov  cl, 4h
	shr  dx, cl
	inc  dx
	mov  ax, cs
	sub  ax, backup_psp
	add  dx, ax
	xor  ax, ax
	mov  ah, 31h
	int  21h

	pop  dx
	pop  bx
	pop  ax
	ret
load_int endp

unload_int proc near
	push ax
	push bx
	push cx

	push es
	mov  ax, backup_psp
	mov  es, ax
	mov  dx, word ptr es:int9_vec
	mov  ax, word ptr es:int9_vec + 2
	mov  backup_ip, dx
	mov  backup_cs, ax
	pop  es

	cli
	push ds

	mov  ah, 35h
	mov  al, 09h
	int  21h

	mov  si, offset backup_ip
	sub  si, offset int_hndl
	mov  dx, es:[bx + si]
	mov  ax, es:[bx + si + 2]
	mov  ds, ax
	mov  ah, 25h
	mov  al, 09h
	int  21h

	pop  ds

	mov  ax, es:[bx + si - 2]
	mov  es, ax
	push es

	mov  ax, es:[2Ch]
	mov  es, ax
	mov  ah, 49h
	int  21h

	pop  es
	mov  ah, 49h
	int  21h
	sti

	pop  cx
	pop  bx
	pop  ax
	ret
unload_int endp

test_int proc near
	push bx
	push es
	push si

	mov  ah, 35h
	mov  al, 09h
	int  21h

	mov  si, offset int_magic
	sub  si, offset int_hndl
	mov  dx, es:[bx + si]
	cmp  dx, 0BEEFh
	jne  .end_false
	mov  ax, 1
	jmp  .end2
	.end_false:
	mov  ax, 0

	.end2:
	pop  si
	pop  es
	pop  bx
	ret
test_int endp

test_should_unload proc near
	push bx
	push cx
	push di

	mov  di, 82h
	mov  bl, [80h]
	cmp  bl, 3
	jb   .end_false2
	mov  cl, [di]
	cmp  cl, '/'
	jne  .end_false2
	mov  cl, [di + 1]
	cmp  cl, 'u'
	jne  .end_false2
	mov  cl, [di + 2]
	cmp  cl, 'n'
	jne  .end_false2

	mov  ax, data
	mov  ds, ax
	mov  ax, 1
	jmp  .end

	.end_false2:
	mov  ax, data
	mov  ds, ax
	mov  ax, 0

	.end:
	pop  di
	pop  cx
	pop  bx
	ret
test_should_unload endp


start proc far
	xor  ax, ax
	push ds
	mov  ax, data
	mov  ds, ax

	call test_int
	cmp  ax, 1
	je   .already_loaded

	.not_loaded:
	pop  ds
	push ds
	call test_should_unload
	cmp  ax, 1
	je   .exit

	lea  dx, instld_str
	mov  ah, 9h
	int  21h
	pop  ds
	call load_int
	jmp  .exit

	.already_loaded:
	pop  ds
	call test_should_unload
	cmp  ax, 1
	jne  .do_not_unload

	.unload:
	call unload_int
	lea  dx, unld_str
	mov  ah, 9h
	int  21h
	jmp  .exit

	.do_not_unload:
	lea  dx, already_str
	mov  ah, 9h
	int  21h

	.exit:
	mov  ah, 4Ch
	int  21h
start endp

code ends

data segment
	already_str	db 'Resident interrupt at 0x9 already installed', 0Dh, 0Ah, '$'
	instld_str	db 'Resident interrupt at 0x9 installed', 0Dh, 0Ah, '$'
	unld_str	db 'Unloaded interrupt at 0x9', 0Dh, 0Ah, '$'
data ends

astack segment stack
	dw 128 dup(?)
astack ends

end start