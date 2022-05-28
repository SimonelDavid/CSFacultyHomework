bits 32 
global start        

extern exit, printf, scanf, fopen, fprintf, fclose
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import exit msvcrt.dll    

segment data use32 class=data
    
    text1 db "Citeste pe n: ", 0
    text2 db "Citeste pe m: ", 0
    text3 db "Citeste cuvantul: ", 0
    cuvant resb 20
    nume_fisier db "ex.txt", 0
    mod_acces db "a", 0
    n dd 0
    m dd 0
    format db "%d", 0
    format_cuv db "%s", 0
    descriptor_fis dd -1

segment code use32 class=code
    start:
    
    push dword text1
    call [printf]
    add esp, 4*1
    
    push dword n
    push dword format
    call [scanf]
    add esp, 4*2
    
    push dword text2
    call [printf]
    add esp, 4*1
    
    push dword m
    push dword format
    call [scanf]
    add esp, 4*2
    
    mov esi, 0
    
    read:
        cmp esi, [m]
        je final
        
        push dword text3
        call [printf]
        add esp, 4*1
        
        push dword cuvant
        push dword format_cuv
        call [scanf]
        add esp, 4*2
        
        inc esi
        
        mov ebx, -1
        mov ecx, 0
        jmp verifica

    verifica:
        inc ebx
        cmp byte[cuvant+ebx], 0
        je afisare
        
        cmp byte[cuvant+ebx], "a"
        je verifica
        
        cmp byte[cuvant+ebx], "e"
        je verifica
        
        cmp byte[cuvant+ebx], "i"
        je verifica
        
        cmp byte[cuvant+ebx], "o"
        je verifica
        
        cmp byte[cuvant+ebx], "u"
        je verifica
        
        inc ecx
        jmp verifica
        
    afisare:
        cmp ecx, [n]
        jle scrie
        ja read
    
    scrie:
        mov eax, 0
        
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2 
        
        mov [descriptor_fis], eax
        
        push dword cuvant
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 4*2
        
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4
        
        jmp read
        
    
    final:
        push    dword 0      
        call    [exit]       
