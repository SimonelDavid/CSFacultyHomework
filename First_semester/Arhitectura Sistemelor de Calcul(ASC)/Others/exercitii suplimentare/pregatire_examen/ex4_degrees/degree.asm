bits 32 ; assembling for the 32 bits architecture


global start        


extern exit, printf              
import exit msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir dq 1110111b, 100000000h, 0abcd0002e7fch, 5
    len equ ($-sir)/8
    rez times len dd 0
    format db "||", 0
    numar times 33 db 0
    

; our code starts here
segment code use32 class=code
    start:
        mov esi, 0
        mov ecx, len
        parcurgere:
            mov eax, [sir+esi*8] ;dublucuvantul low in eax
            push eax
            push ecx
            mov ecx, 32
            mov bl, 0 ; numarul de grade
            mov bh, 0; numar de 1 
            rotire:
                mov dl, 0
                rcl eax, 1
                adc dl, 0 
                cmp dl, 0 
                je zero ;pornim de la inceput
                inc bh   ;daca nu creste nr de 1 
                cmp bh, 3 
                jb noth ;daca e sub 3, ramane asa
                inc bl ; creste nr de grade si se începe de la început
                zero:
                    mov bh, 0 ;se reface numar de 1 la 0
                noth:
            loop rotire
            pop ecx
            pop eax
            cmp bl, 2   
            jb noth2 ; daca nu are mai mult de 2 grade nu afisam
            push ecx
            mov ecx, 32
            mov ebx, 0
            mov edx, 0
            mov dl, 0; pozitia la care se gaseste primu 1
            rotire2:
                mov [numar+ebx], byte 0
                rcl eax, 1
                adc [numar+ebx], byte '0'
                cmp [numar+ebx], byte '1'
                jb noth3
                cmp dl, 0
                ja noth3
                mov dl, bl
                noth3:
                inc bl
            loop rotire2
            lea ebx, [numar+edx]
            push dword ebx
            call [printf]
            add esp, 4
            
            push dword format
            call [printf]
            add esp, 4
            pop ecx
            noth2:
            inc esi
            dec ecx
            cmp ecx, 0
        ja parcurgere
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
