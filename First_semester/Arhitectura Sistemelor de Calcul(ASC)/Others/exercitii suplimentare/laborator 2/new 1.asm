bits 32
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a db 'abcd'
    b db 'bbcc'
    
segment code use32 class=code
start:
    
    cld
    mov esi, a
    mov edi, b
    cmpsb
    cmpsb
    
    
    
    push dword 0
    call [exit]