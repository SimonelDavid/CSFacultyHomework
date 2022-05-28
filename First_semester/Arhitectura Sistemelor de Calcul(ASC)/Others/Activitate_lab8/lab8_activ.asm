;Sa se citeasca de la tastatura un numar in baza 10 si sa se afiseze valoarea acelui numar in baza 16.
;Exemplu: Se citeste: 28; se afiseaza: 1C

bits 32
global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
      
segment data use32 class=data
    format_10 db "%d", 0
    format_16 db "%x", 0
    x dd 0
    

segment code use32 class=code
start:
; efectuam citirea numarului in baza 10
    push dword x
    push format_10
    call [scanf]
    add esp, 4*2
    
;efectuam afisraea numarului in baza 16
    push dword[x]
    push format_16
    call [printf]
    add esp, 4*2

    push dword 0
    call [exit]
