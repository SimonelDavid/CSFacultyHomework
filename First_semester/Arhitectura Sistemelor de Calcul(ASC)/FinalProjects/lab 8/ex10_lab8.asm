;10. Sa se citeasca de la tastatura un nume de fisier si un text. Sa se creeze un fisier cu numele dat in directorul curent si sa se scrie textul in acel fisier. Observatii: Numele de fisier este de maxim 30 de caractere. Textul este de maxim 120 de caractere.

bits 32
global start

extern exit, printf, scanf, fopen, fclose, fprintf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
      
segment data use32 class=data
    text1 db "Dati un nume fisierului: ", 0
    text2 db "Introduceti textul pe care doriti sa il vedeti in fisier: ", 0
    Format db "%s", 0
    mod_acces db "w", 0
    
    descriptor dd -1
    
    len equ 30
    numeFisier times len dd 0
    
    len1 equ 120
    textFisier times len1 dd 0

segment code use32 class=code
start:
    
    ; afisam pe ecran mesajul pentru utilizator
    push dword text1
    call [printf]
    add esp, 4*1
 
    ; citim numele fisierului de la tastatura
    push dword numeFisier
    push Format
    call [scanf]
    add esp, 4*2
    
    
    ; se creeaza fisierul si se deschide in modul de citire
    push dword mod_acces
    push dword numeFisier
    call [fopen]
    add esp, 4*2
    
    
    ; salvam valoarea returnata de fopen in variabila descriptor
    mov [descriptor], eax
    
    ; verificam daca functia fopen a creat cu succes fisierul(daca EAX != 0)
    cmp eax, 0
    je final
    
    
    ; afisam pe ecran mesajul pentru utilizator
    push dword text2
    call [printf]
    add esp, 4*1
 
    ; citim textul pe care dorim sa il introducem in fisier
    push dword textFisier
    push Format
    call [scanf]
    add esp, 4*2
    
    
    ; scriem textul in fisierul deschis folosid functia fprintf
    push dword textFisier
    push dword [descriptor]
    call [fprintf]
    add esp, 4*2
    
    
    ; inchidem fisierul prin apelarea functiei fclose
    push dword [descriptor]
    call [fclose]
    add esp, 4*1
    
    final:
    
    push dword 0
    call [exit]
