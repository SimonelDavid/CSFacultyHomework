bits 32         

global _verifica_siruri                
segment code use32 public code

_verifica_siruri:  ;verifica_siruri(sir_1, sir_2)    

    mov ecx, 0
    mov ecx, [esp+4*1] ; sir 1
    
    mov edx, 0
    mov edx, [esp+4*2] ; sir 2

    mov eax, 0
    mov eax, ecx ; in eax vom avea primul sir
    mov ecx, 0
    mov ecx, edx ; in ecx vom avea al doilea sir
    
    mov ebx, 0  ; contor pentru sirul al doilea
    mov edx, 0  ; contor pentru primul sir
    
    verifica:
        cmp byte [ecx+ebx], 0   ; verificam daca sirul al doilea este parcurs, daca da, atunci nu a fost gasit un subsir in sir
        je negasit
        
        ; verificam daca un caracter din primul sir se afla in al doilea sir, daca da trecem la bucla ok, altfel trecem la urmatorul caracter din sirul al doilea
        mov dl, [eax+0]
        mov dh, [ecx+ebx]
        cmp dl, dh
        je ok
        inc ebx
        jne verifica
    
    ok:
        ; daca primul sir a ajuns la final si nu s-a intors in bucla verifica, inseamna ca a fost gasit primul sir ca subsir in cel de-al doilea sir
        cmp byte [eax+ebx], 0
        je gasit
    
        ; daca nu este gata primul sir, verificam daca urmatorul caracter din primul sir se afla in al doilea sir in continuarea celui precedent
        mov dl, [eax+ebx]
        add ebx, edx
        mov dh, [ecx+ebx]
        
        cmp dl, dh
        inc edx
        je ok   ; daca este gasit intram din nou in ok
        mov edx, 0
        jne verifica ; daca nu este gasit revenim in bucla verifica
    
    
    ; daca este gasit inregistram in al 1 si inchidem programul
    gasit:
        mov al, 1
        ret 
    
    ; daca nu este gasit inregistram in al 0 si inchidem programul
    negasit: 
        mov al, 0
        ret 
        