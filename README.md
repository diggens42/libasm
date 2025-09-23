Resources:

https://www.youtube.com/watch?v=6S5KRJv-7RU
https://www.tutorialspoint.com/assembly_programming/index.htm
https://stackoverflow.com/questions/5041481/strlen-in-assembly
https://www.reddit.com/r/asm/comments/l4rzbf/strcpy_implementation/

Bit value	                        1	1	1	1	1	1	1	1
Position value as a power of base 2	128	64	32	16	8	4	2	1
Bit number	                        7	6	5	4	3	2	1	0

Decimal number	Binary representation	Hexadecimal representation
0	                    0	                        0
1	                    1	                        1
2	                    10	                        2
3	                    11	                        3
4	                    100	                        4
5	                    101	                        5
6	                    110	                        6
7	                    111	                        7
8	                    1000                    	8
9	                    1001                    	9
10	                    1010                    	A
11	                    1011                    	B
12	                    1100                    	C
13	                    1101                    	D
14	                    1110                    	E
15	                    1111                    	F


Important operators and syntax elements in Intel x86/x64 assembly:
Arithmetic Operators

ADD - Addition (ADD dest, src)
SUB - Subtraction (SUB dest, src)
MUL - Unsigned multiplication
IMUL - Signed multiplication
DIV - Unsigned division
IDIV - Signed division
INC - Increment by 1
DEC - Decrement by 1
NEG - Two's complement negation

Logical Operators

AND - Bitwise AND
OR - Bitwise OR
XOR - Bitwise exclusive OR
NOT - Bitwise NOT (one's complement)
SHL/SAL - Shift left (logical/arithmetic)
SHR - Shift right logical
SAR - Shift right arithmetic
ROL/ROR - Rotate left/right

Data Movement

MOV - Move data (MOV dest, src)
LEA - Load effective address
XCHG - Exchange values
PUSH - Push onto stack
POP - Pop from stack

Control Flow

JMP - Unconditional jump
JE/JZ - Jump if equal/zero
JNE/JNZ - Jump if not equal/not zero
JG/JL - Jump if greater/less (signed)
JA/JB - Jump if above/below (unsigned)
CALL - Call procedure
RET - Return from procedure
LOOP - Loop with counter

Comparison

CMP - Compare (sets flags)
TEST - Logical compare (AND without storing result)

-------------------------

x86-64 Register Naming Convention
General Purpose Registers (64-bit):

RAX - Accumulator (often used for return values)
RBX - Base register
RCX - Counter register
RDX - Data register
RSI - Source index
RDI - Destination index
RBP - Base pointer (stack frame)
RSP - Stack pointer
R8-R15 - Additional general purpose registers

Register Size Variants:

64-bit: RAX, RBX, RCX, etc. (R prefix)
32-bit: EAX, EBX, ECX, etc. (E prefix)
16-bit: AX, BX, CX, etc. (no prefix)
8-bit: AL, BL, CL, etc. (L suffix for low byte)

-------------------------


Addressing Syntax

Immediate: MOV EAX, 42 (literal value)
Register: MOV EAX, EBX (register to register)
Direct: MOV EAX, [1234h] (memory address)
Indirect: MOV EAX, [EBX] (register contains address)
Indexed: MOV EAX, [EBX + 4] (base + displacement)
Scaled: MOV EAX, [EBX + ECX*2 + 8] (base + index*scale + displacement)

Size Specifiers

BYTE PTR - 8-bit operation
WORD PTR - 16-bit operation
DWORD PTR - 32-bit operation
QWORD PTR - 64-bit operation

This covers the fundamental syntax you'll encounter most frequently in Intel assembly programming.

Intel vs AT&T Syntax Differences
1. Operand Order
Intel: operation destination, source
AT&T: operation source, destination
nasm; Intel (what you're using - CORRECT)
mov rax, 5          ; Move 5 into RAX
add rax, rbx        ; Add RBX to RAX

; AT&T
movq $5, %rax       ; Move 5 into RAX
addq %rbx, %rax     ; Add RBX to RAX
2. Register Names
Intel: No prefix - rax, rbx, rdi
AT&T: % prefix - %rax, %rbx, %rdi
3. Immediate Values (Constants)
Intel: No prefix - mov rax, 42
AT&T: $ prefix - movq $42, %rax
4. Memory Addressing
Intel: [base + index*scale + displacement]
AT&T: displacement(base, index, scale)
nasm; Intel
mov al, byte [rdi + rax]        ; Load byte from memory
cmp byte [rdi + rax], 0         ; Compare memory with 0

; AT&T
movb (%rdi, %rax), %al          ; Load byte from memory
cmpb $0, (%rdi, %rax)           ; Compare memory with 0
5. Instruction Suffixes
Intel: Size specified by operand type or explicit (byte, word, dword, qword)
AT&T: Suffix on instruction (b, w, l, q)
nasm; Intel
mov rax, 5              ; 64-bit move (inferred from register)
mov byte [rdi], 0       ; 8-bit move (explicit)

; AT&T
movq $5, %rax           ; 64-bit move (q = quad word)
movb $0, (%rdi)         ; 8-bit move (b = byte)


Calling convention rules (System V AMD64)

Caller-saved (volatile) registers: rax, rcx, rdx, rsi, rdi, r8–r11.
→ You can freely use their 8-bit parts (al, bl, cl, dl, r8b…).

Callee-saved (non-volatile) registers: rbx, rbp, r12–r15.
→ If you touch these, you’re supposed to restore them before ret.
