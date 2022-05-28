bits 32 


global start        


extern exit
extern printf, scanf               
import exit msvcrt.dll
import printf msvcrt.dll 
import scanf msvcrt.dll   
extern suma

segment data use32 class=data
    sir dd -1, 123456, 0xabcdeff, 0xabcdeff, 0xcbcdeff, 0xdbcdeff,0111010101b
    len equ ($-sir)/4
    rez db 0, 1, 1, 2, 2, 5, 7
    format db "%x ", 0
    end_secv db "|||", 0
    

; our code starts here
segment code use32 class=code
    start:
        ;cdecl call suma(sir, rez, len)
        pusha 
        push dword len
        push dword rez
        push dword sir
        call suma
        add esp, 4*3
        popa
        
        mov ecx, len
        mov esi, 0
        mov ah, 0
        parcurge:
            mov al, [rez + esi]
            cmp al, ah     ; dacă noul element încărcat e mai mare decât anteriorul
                    ;atunci el face parte din această secvență:
            ja continua_secv
            pusha
            ;altfel se afișează un delimitator de secvență
            push dword end_secv
            call [printf]
            add es  p, 4
            popa
            ;se continuă cu afișarea numărului
            ; din acest punct, el face parte din altă secvență
            continua_secv:
                
                mov ebx, [sir + esi*4]   ;afisez dublucuvântul corespunzător acestei poziții
                pusha
                
                push ebx
                push dword format
                call [printf]
                add esp, 4*2
                
                popa
                
                mov ah, [rez + esi] ; se actualizează elementul cu care se va compara
                        ;la următorul pas
                inc esi
        loop parcurge
        
        push dword sir
        push dword format
        call [scanf]
        add esp, 4*2
        
        ; exit(0)
        push    dword 0      
        call    [exit]       
