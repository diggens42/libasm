section .text
    global ft_strcpy

ft_strcpy:
    mov    rax, rdi        ; save dest ptr (rdi) into rax since it is the return value

.loop:
    mov    bl, byte [rsi]  ; load byte from src ptr (rsi) into 8bit registry of rbx (can't use rax since it is already used)
    mov    byte [rdi], bl  ; store byte from rbx 8bit registry into dest ptr (rdi)
    inc    rsi             ; increment src ptr
    inc    rdi             ; increment dest ptr
    test   bl, bl          ; check for null term (if bl == 0)
    jnz    .loop           ; if condition is not met, jump back to start of loop
    ret                    ; if condition is met, return rax (ptr to dest)
