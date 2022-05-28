;David SImonel Olimpiu 212/2
; Cerinta:
; 10.Se da un sir A de cuvinte. Construiti doua siruri de octeti  
; - B1: contine ca elemente partea superioara a cuvintelor din A
; - B2: contine ca elemente partea inferioara a cuvintelor din A

bits 32
global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data 
    A dw 1234h, 5678h, 1122h, 3344h
    len equ ($-A)/2
    B1 times len db 0;12, 56, 11, 33
    B2 times len db 0;34, 78, 22, 44

segment code use32 class=code
    start:
    
    mov esi, A
    mov edi, B1
    mov ecx, len
    mov eax, 0
    repeta:
        lodsw           ;in ax avem pe rand elementele din A
        mov al, ah      ;in al avem cel mai high byte din elementul curent
        stosb           ;punem in B1 ce avem in al
    loop repeta
    
    mov esi, A
    mov edi, B2
    mov ecx, len
    repeta1:
        lodsw           ;in ax avem pe rand elementele din A
        stosb           ;punem in B2 ce avem in al
    loop repeta1

        
        push    dword 0
        call    [exit]
