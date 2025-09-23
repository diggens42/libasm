section .text
	global ft_write
	extern	__errno_location

ft_write:
	mov		rax, 1      ;syscall number for write (linux)
	syscall				;invoke the syscall
	cmp		rax, 0
	jge		.done		;jump greater/equal --> if rax >= 0 no error occured

.error:
	neg		rax			; make error code positive
	mov		rdi, rax    ; save error code in rdi
	call    __errno_location ;get address of errno
	mov		[rax], edi  ;store error code in errno
	mov		rax, -1		; set ret value to -1 to indicate error

.done:
	ret					; return res in rax