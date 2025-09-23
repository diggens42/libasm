section .text
    global ft_strlen

ft_strlen:
    xor rax, rax                ; when u XOR any value with itself ,it becomes 0 --> set rax(counter) to 0

.loop:
    cmp byte [rdi + rax], 0     ; compare byte at address given to function + rax(counter) until we get to 0 (null terminator)
    je .done                    ; if condition is met, jump to .done (conditional jump)
    inc rax                     ; i++
    jmp .loop                   ; jump back to loop (unconditional jump)

.done
    ret                         ; rax is automatically the return register for int/ptr values (calling convention rules)
