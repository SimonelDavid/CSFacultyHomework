bits 32
global start

extern exit, printf, scanf, fopen, fprintf, fclose
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    text1 db "Citeste numele fisierului: ", 0
    text2 db "Citeste textul: ", 0
    cuvant resb 20
    nume_fisier resb 10
    mod_acces db "a", 0
    format db "%s", 0
    descriptor_fis dd -1

segment code use32 class=code
    start:
    
    push dword text1
    call [printf]
    add esp, 4*1
    
    push dword nume_fisier
    push format
    call [scanf]
    add esp, 4*2
    
    push dword text2
    call [printf]
    add esp, 4*1
    
    push dword cuvant
    push format
    call [scanf]
    add esp, 4*2
    
    mov esi, 0
    verifica:
        cmp byte[cuvant+esi], 0
        je afisare
        
        cmp byte[cuvant+esi], "9"
        jle creste
        inc esi
        jmp verifica
    
    creste:
        cmp byte[cuvant+esi], "0"
        jle verifica
        
        mov ebx, [cuvant+esi]
        add ebx, 1
        mov [cuvant+esi], ebx
        inc esi
        jmp verifica
    
    afisare:
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                ; eliberam parametrii de pe stiva

        mov [descriptor_fis], eax   ; salvam valoarea returnata de fopen in variabila descriptor_fis
        
        ; verificam daca functia fopen a creat cu succes fisierul (daca EAX != 0)
        cmp eax, 0
        je final
        
        push dword cuvant
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 4*2
        
        ; apelam functia fclose pentru a inchide fisierul
        ; fclose(descriptor_fis)
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4

    
    final:
        push    dword 0
        call    [exit]
