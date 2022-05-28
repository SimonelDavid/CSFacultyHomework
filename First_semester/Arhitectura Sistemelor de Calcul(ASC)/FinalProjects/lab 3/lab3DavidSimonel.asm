bits 32

global start
extern exit
import exit msvcrt.dll

segment data use32 class=data

    a db 01h
    b dw 1234h
    c dd 12345678h
    d dq 1122334455667788h
    x resq 1
    
    B db 02h
    C db 03h
    E dd 11223344h
    
   
segment code use32 class=data
    start:
    
    ;a - byte, b - word, c - double word, d - qword - Interpretare cu semn
    ;2. (c+b)-a-(d+d)
    
       mov ax, [b]
       cwde ; eax = b
       add eax, [c] ; eax = c+b
        
       mov ebx, 0
       mov bl, [a]
       sub eax, ebx ; eax = (c+b) - a
       mov ebx, 0
        
       cdq ; edx:eax = (c+b) - a
       mov ebx, dword[d+0]
       mov ecx, dword[d+4]
       add ebx, ebx
       adc ecx, ecx
        
       mov dword[x+0], ebx
       mov dword[x+4], ecx; x = d+d
        
       sub eax, dword[x]
       sub edx, dword[x+4]
    

    ; 15. x-(a*B*25+C*3)/(a+B)+E; a,B,C-byte; E-doubleword
    
        mov al, [a]
        imul byte [B]
        mov bx, ax 
        mov al, 25
        cbw
        imul bx 

        mov bx, ax 
        mov al, 3
        imul byte [C]  
        add ax, bx
        adc dx, 0 
        mov bx, ax 
            
        mov al, [a] 
        add al, [B]
        cbw
            
        mov cx, ax
        mov ax, bx
        mov bx, cx 
            
        idiv bx 
        mov dx, 0 
        mov bx, word [E]
        mov cx, word [E+2] 
            
        add ax, bx
        adc dx, cx 
            
        push dx
        push ax
        pop ebx 
            
        mov eax, dword[x]
        mov edx, dword[x+4] 
            
        sub eax, ebx
        sbb edx, 0
    
    push dword 0
    call [exit]
