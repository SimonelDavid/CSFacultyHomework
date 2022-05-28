bits 32 ; assembling for the 32 bits architecture
global start        


extern exit, scanf, printf               
import exit msvcrt.dll    
extern simetrie

import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    numar dd 0
    format db "%x", 0
    format_af db "%x  ", 0
    numar_de_numere_de_afisat db 0

; our code starts here
segment code use32 class=code
    start:
        citire:
        ;scanf(format, numar)
        push dword numar
        push dword format
        call [scanf]
        add esp, 4*2
        cmp dword [numar], 0
        je iesire
        ;dx <- byte1 și byte 4
        ;bx <- byte2 și byte 3
        mov edx, 0
        mov dh, [numar]
        mov dl, [numar+3]
        ;call simetrie(dx)
        push edx
        call simetrie
        cmp eax, 0 
        je continue
        
        mov ebx, 0
        mov bh, [numar+1]
        mov bl, [numar+2]
        ;call simetrie(bx)
        push ebx
        call simetrie
        cmp eax, 0
        je continue
        
        push dword [numar]
        add [numar_de_numere_de_afisat], byte 1
        
        continue:
        jmp citire
        iesire:
        
        mov ecx, 0
        mov cl, [numar_de_numere_de_afisat]
        jecxz iesire2
        afis:
            pop eax
            pusha
            
            push eax
            push format_af
            call [printf]
            add esp, 4*2
            
            popa
            dec ecx
            cmp ecx, 0
            je iesire2
        jmp afis
        
        iesire2:
        push dword numar
        push dword format
        call [scanf]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
