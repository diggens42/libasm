section .text
    global ft_strcmp

ft_strcmp:

.loop:
    mov    al, byte [rdi]  ; load byte from str1 (rdi) into al
    mov    cl, byte [rsi]  ; load byte from str2 (rsi) into cl
    cmp    al, cl          ; compare bytes
    jnz    .diff           ; jump if diff is found
    test   al, al          ; test for null chararacter
    jz     .equal          ; if null char is found, jump to equal
    inc    rdi             ; increment str1
    inc    rsi             ; increment str2
    jmp    .loop           ; jump back into loop to continue Comparison

.diff:
    movzx  eax, al         ; zero extend the str1 char (move 8bit into 32bit and put the 24bit leftover to 0)
    movzx  ecx, cl         ; zero extend the str2 char
    sub    eax, ecx        ; str1 - str2 like strcmp does, ret value <0 if str2 is longer, >0 if str1 is longer
    ret

.equal:
    xor    eax, eax        ; set eax to 0 since strcmp is supposed to return 0 if both str are equal
    ret
