bits 32
global start

extern exit, fopen, fclose, fscanf, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
      
segment data use32 class=data
    text resb 100
    fisier1 db "primulfisier.txt", 0
    fisier2 db "al_doilea_fisier.txt", 0
    
    mod_acces1 db "w", 0
    mod_acces2 db "r", 0
    
    format1 db "%s", 0
    format2 db "%c", 0
    
    descriptor_fis dd 0

segment code use32 class=code
start:

    push dword mod_acces2
    push dword fisier1
    call [fopen]
    add esp, 4*2
    
    test eax, eax
    jz final
    mov [descriptor_fis], eax
    
    push dword text
    push dword format1
    push dword [descriptor_fis]
    call [fscanf]
    add esp, 4*3
    
    push dword [descriptor_fis]
    call [fclose]
    add esp, 4
    
    push dword mod_acces1
    push dword fisier2
    call [fopen]
    add esp, 4*2
    mov [descriptor_fis], eax
    
    mov esi, text
    
    cautare:
        cmp byte[esi], 0
        je afisare
        inc esi
        jmp cautare
    
    mov ebx, [esi]
    
    afisare:
        dec esi
        mov eax, 0
        
        push dword[esi]
        push format2
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 4*3
        
        cmp esi, text
        jne afisare
    
    push dword [descriptor_fis]
    call [fclose]
    add esp, 4
    
    final:
    push dword 0
    call [exit]