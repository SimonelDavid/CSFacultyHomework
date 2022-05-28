; Tema -> David Simonel-Olimpiu
bits 32 
global  start 

extern  exit 
import  exit msvcrt.dll
        
segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
	a  db 15
	b  db 7
    c  db 28
    d  db 4
    
    A dw 20
    B dw 9
    C dw 37
    D dw 6
segment  code use32 class=code ; segmentul de cod
start: 
	;exercitiul 1(exercitii simple: 17 => 14+2)
    mov eax, 0
    mov al, 14
    add al, 7
    
    ;exercitiul 2(adunari, scaderi, a,b,c,d - byte: 7 => c-(d+d+d)+(a-b)
    mov al, 0
    mov al, [d];al = d
    add al, [d];al = d+d
    add al, [d];al = d+d+d
    
    mov edx, 0
    mov dl, [a];dl = a
    sub dl, [b];dl = a-b
    
    mov ebx, 0
    mov bl, [c];bl = c
    sub bl, al;bl = c-(d+d+d)
    add bl, dl;bl = c-(d+d+d)+(a-b)
    
    ;exercitiul 3(adunari, scaderi, a,b,c,d - word: 26 => (a+c)-(b+b+d))
    
    mov ax, 0
    mov ax, [A] ;ax = a
    add ax, [C] ;ax = a+c
    
    mov bx, 0
    mov bx, [B] ;bx = b
    add bx, [B] ;bx = b+b
    add bx, [D] ;bx = b+b+d
    
    sub ax, bx ;ax = (a+c)-(b+b+d)
    
    ;exercitiul 4(inumltiri, impartiri, a,b,c - byte, d - word: 23 => [(a+b)*3-c*2]+d
    mov eax, 0
    mov ax, 0
    mov al, [a] ;al = a
    add al, [b] ;al = a+b
    mov ah, 3 ;ah = 3
    mul ah ;ax = (a+b)*3
    
    mov ebx, 0
    mov bx, ax ;bx = ax
    mov al, [c] ;al = c
    mov ah, 2 ;ah = 2
    mul ah ;ax = c*2
    
    sub bx, ax ;bx = (a+b)*3-c*2
    add bx, [D] ;bx = [(a+b)*3-c*2]+d
    
    ;exercitiul 5(inumltiri, impartiri, a,b,c,d-byte, e,f,g,h-word : 5 => a*(b+c)+34
    
    mov eax, 0
    mov al, [b] ;al = b
    add al, [c] ;al = c
    mov ah, [a] ;ah = a
    mul ah ;ax = a*(b+c)
    add ax, 34 ;ax = a*(b+c)+34
	
	push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului