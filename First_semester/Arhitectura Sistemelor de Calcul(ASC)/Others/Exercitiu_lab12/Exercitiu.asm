bits 32 
global start        

extern exit, scanf, printf, fopen, fclose, fread               
import exit msvcrt.dll  
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll  

segment data use32 class=data
    text1 db "Dati numele fisierului: ", 0
    text2 db "Numarul bitilor 1 este: ", 0
    mod_acces db 'r', 0
    formats db "%s", 0
    format db "%d", 0 
    
    nume resb 20
    len equ 100
    text resb len
    descriptor dd -1
    nr db 0
    frecventa db 0

segment code use32 class=code
    start:
    
        ; afisam pe ecran mesajul pentru utilizator
        push dword text1
        call [printf]
        add esp, 4*1
    
        ; citim numele fisierului
        push dword nume
        push dword formats
        call [scanf]
        add esp, 4*2
        
        ; deschidem fisierul
        push dword mod_acces
        push dword nume
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je iesire
        mov [descriptor], eax
        
        verificare:
        
            ; citim din fisier elementul
            push dword [descriptor]
            push dword len
            push dword 1
            push dword text
            call [fread]
            add esp, 4*4
            
            mov [nr], eax
            cmp eax, 0
            je afisare
            
            mov ecx, [nr]
            cld
            mov esi, text
            bucla:
                lodsb
                rotire:
                    rcr al, 1
                    adc byte [frecventa], 0
                    cmp al, 0
                    jne rotire
            loop bucla
            
        afisare:
            
            
            ; afisam pe ecran mesajul pentru utilizator
            push dword text2
            call [printf]
            add esp, 4*1
            
            mov eax, 0
            mov eax, [frecventa]
            
            ; realizam afisarea
            push dword eax
            push dword format 
            call [printf]    
            add esp, 4*2

            push dword [descriptor]
            call [fclose]
            add esp, 4*2
            
        iesire:

        push    dword 0
        call    [exit]
