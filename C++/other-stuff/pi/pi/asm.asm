.code

add_carry proc
	add rcx,rdx
	setc al
	mov [r8], al
	mov rax,rcx
	ret
add_carry endp
sub_carry proc
	sub rcx,rdx
	setc al
	mov [r8], al
	mov rax,rcx
	ret
sub_carry endp
mlt_carry proc
	mov rax,rcx
	imul rdx
	mov [r8], rdx
	ret
mlt_carry endp
add_full proc
	;C-decleration: void add_full(unsigned long long *a, unsigned long long *b, unsigned long long *res, unsigned int len)
	;Counter in r9 (input)
	clc
	lp:
	dec r9
	cmp r9,0
	mov rax, [rcx+r9*8]
	mov rbx, [rdx+r9*8]
	adc rax, rbx
	mov [r8+r9*8], rax
	jne lp
	ret
add_full endp
sub_full proc
	;C-decleration: void add_full(unsigned long long *a, unsigned long long *b, unsigned long long *res, unsigned int len)
	;Counter in r9 (input)
	clc
lp:
	dec r9
	cmp r9,0
	mov rax, [rcx+r9*8]
	mov rbx, [rdx+r9*8]
	sbb rax, rbx
	mov [r8+r9*8], rax
	jne lp
	ret
sub_full endp


end