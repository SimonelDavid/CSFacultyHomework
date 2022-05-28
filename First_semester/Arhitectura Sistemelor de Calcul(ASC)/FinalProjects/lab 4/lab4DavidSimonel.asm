; Cerinta:
; 12. Se dau doua cuvinte A si B. Sa se obtina dublucuvantul C:
;   -bitii 0-6 ai lui C au valoarea 0
;   -bitii 7-9 ai lui C coincid cu bitii 0-2 ai lui A
;   -bitii 10-15 ai lui C coincid cu bitii 8-13 ai lui B
;   -bitii 16-31 ai lui C au valoarea 1

bits 32
global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data 
    a dw 0101010101110101b ; 0101 0101 0111 0101
    b dw 1010100110011100b ; 1010 1001 1001 1100   
    c dd 0
    

segment code use32 class=code
    start:
    
        mov bx, 0
        mov dx, 0 ; in dx:bx vom calcula rezultatul
        
        and  bx, 1111111110000000b ; facem bitii 0-6 din rezultat sa aiba valoarea 0
                                   ; 1111 1111 1000 0000
        
        mov  ax, [a] ; izolam bitii 0-2 ai lui a
        and  ax, 0000000000000101b ; 0000 0000 0000 0101
        mov  cl, 7
        rol  ax, cl ; rotim 7 pozitii spre stanga
        or   bx, ax ; punem bitii in rezultat
        
        mov  ax, [b] ; izolam bitii 8-13 ai lui b
        and  ax, 0011111100000000b ; 0011 1111 0000 0000
        mov  cl, 2
        rol  ax, cl ; rotim 2 pozitii spre stanga
        or   bx, ax ; punem bitii in rezultat
        
        or dx, 1111111111111111b ; bitii 16-31 ai lui C au valoarea 1
                                 ; 1111 1111 1111 1111
        
        push dx
        push bx
        
        mov eax, 0
        pop eax
        
        mov dword[c], eax ;punem valoarea din registru in rezultat, astfel in c avem rezultatul dorit
        
        push    dword 0
        call    [exit]
