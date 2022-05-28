bits 32         

global verifica_siruri                
segment code use32 public code

verifica_siruri:  ;verifica_siruri(sir_1, sir_2, factor)    
    mov ecx, 0
    mov ecx, [esp+4*2] ; sir 1
    
    mov edx, 0
    mov edx, [esp+4*1] ; sir 2

    mov esi, ecx ; in esi vom avea primul sir
    mov edi, edx ; in edi vom avea al doilea sir
    
    mov ebx, 0  ; pentru sirul al treilea
    mov edx, 0  ; pentru sirul al doilea
    
    verifica:
        cmp byte [edi+ebx], 0   ; verificam daca sirul al doilea este parcurs, daca da, atunci nu a fost gasit un subsir in sir
        je negasit
        
        ; verificam daca un caracter din primul sir se afla in al doilea sir, daca da trecem la bucla ok, altfel trecem la urmatorul caracter din sirul al doilea
        mov dl, [esi+0]
        mov dh, [edi+ebx]
        cmp dl, dh
        je ok
        inc ebx
        jne verifica
    
    ok:
        ; daca primul sir a ajuns la final si nu s-a intors in bucla verifica, inseamna ca a fost gasit primul sir ca subsir in cel de-al doilea sir
        cmp byte [esi+ebx], 0
        je gasit
    
        ; daca nu este gata primul sir, verificam daca urmatorul caracter din primul sir se afla in al doilea sir in continuarea celui precedent
        mov dl, [esi+ebx]
        add ebx, edx
        mov dh, [edi+ebx]
        
        cmp dl, dh
        inc edx
        je ok   ; daca este gasit intram din nou in ok
        mov edx, 0
        jne verifica ; daca nu este gasit revenim in bucla verifica
    
    
    ; daca este gasit inregistram in al 1 si inchidem programul
    gasit:
        mov al, 1
        ret 4*2
    
    ; daca nu este gasit inregistram in al 0 si inchidem programul
    negasit: 
        mov al, 0
        ret 4*2