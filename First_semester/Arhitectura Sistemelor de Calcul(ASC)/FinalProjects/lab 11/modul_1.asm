; 10. Se citesc mai multe siruri de caractere. Sa se determine daca primul apare ca subsecventa in fiecare din celelalte si sa se dea un mesaj corespunzator.

bits 32
global start

extern exit, printf, scanf, verifica_siruri
import exit msvcrt.dll     
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    text_1 db "Dati primul sir de caractere: ", 0
    text_2 db "Dati urmatoarele siruri de caractere: ", 0
    text_ok  db "Primul sir se gaseste in toate celelalte siruri.", 0
    test_not_ok db "Primul sir nu se gaseste in toate celelalte siruri", 0
    verif db 1
    format db "%s", 0
    sir_1 resb 100
    sir  resb 100
    
segment code use32 class=code


    start:
        
        ; afisam pe ecran mesaj pentru utilizator
        push dword text_1
        call [printf]
        add esp, 4*1
    
        ; citim primul sir de caractere
        push dword sir_1
        push format
        call [scanf]
        add esp, 4*2

        calculare:
            ; afisam pe ecran mesaj pentru utilizator
            push dword text_2
            call [printf]
            add esp, 4*1
        
            ; citim primul sir de caractere
            push dword sir
            push format
            call [scanf]
            add esp, 4*2
            
            cmp byte [sir+0], '0'
            jz final
            
            cmp byte [verif], 0
            je calculare
            
                push sir_1
                push sir
                call verifica_siruri
                mov [verif], al ; in al avem rezultatul da(1) sau nu(0) este subsirul in sir
            
        jmp calculare
    
        final:
        
            ; Se efectueaza verificarea daca primul sir citit se afla in al doilea sir.
            cmp byte [verif], 1
            je afisare_ok
            jne afisare_not_ok
            
            afisare_ok:
            
                ; afisam pe ecran mesaj pentru utilizator
                push dword text_ok
                call [printf]
                add esp, 4*1
                jmp sfarsit
            
            afisare_not_ok:
            
                ; afisam pe ecran mesaj pentru utilizator
                push dword test_not_ok
                call [printf]
                add esp, 4*1
        
    sfarsit:
    
    push dword 0
    call [exit]