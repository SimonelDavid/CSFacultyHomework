bits 32

global start    
    
extern exit, printf 
import exit msvcrt.dll
import printf msvcrt.dll  

segment data use32 class=data
    sir dd 1234A678h, 12785634h, 1A4D3C2Bh
    len equ ($-sir)/4
    format dw "%x"
    
segment code use32 class=code
    start:
        mov ecx, len
        mov esi, 0
        mov ebx, 0
        parcurgere:
            mov ax, 0
            mov ah, [sir+(esi+1)*4-1]
            mov al, [sir+esi*4+1]
            push ecx
            mov ecx, 16
            mov edi, 0
            rotire:
                mov dl, 0
                rcl ax, 1
                adc dl, 0
                cmp dl, 0
                je nth
                inc edi
                nth:
            loop rotire
            add ebx, edi
            pop ecx
            inc esi
        loop parcurgere
        
        mov ecx, len
        
        afisare:
            push ecx
            push dword [sir+(ecx-1)*4]
            push dword format
            call [printf]
            add esp, 4*2
            pop ecx
        loop afisare
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
