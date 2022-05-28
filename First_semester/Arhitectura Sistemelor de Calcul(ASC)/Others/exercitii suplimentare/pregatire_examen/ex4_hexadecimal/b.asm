bits 32
segment code use32 public code
global suma
    suma:
        ;suma(sir, rez, len-bytes)
        mov esi, [esp+4] ; adresa sir
        mov edi, [esp + 8]; adresa rez
        mov ecx, [esp + 12]; adresa len
        cld
        parcurgere:
            lodsd ; eax avem elem sir
            mov bx, 0 ; aici calculez suma cifrelor
            push ecx
            mov ecx, 4
            calcul:
                ; încarc octetul low din eax în dl
                mov edx, 0
                mov dl, al
                ;salvez o copie a numarului încarcat
                push edx
                ;izolez ultimii 4 biți (cifra hexa din dreapta)
                shl dl, 4 ; ștergere din stânga
                shr dl, 4 ; revenire în dreapta
                add bx, dx ; adun cifra la rezultat
                
                pop edx   ; recuperez copia
                shr dl, 4 ; pun cifra din stânga în dreapta pentru a o aduna
                add bx, dx ; adun la rezultat
             
                shr eax, 8  ; șterg din dreapta ultimele 8 cifre binare (ultimele 2 cifre hexa)
            loop calcul
            ;salvez rezultatul
            mov al, bl
            stosb
            pop ecx
        loop parcurgere
        
        ret 