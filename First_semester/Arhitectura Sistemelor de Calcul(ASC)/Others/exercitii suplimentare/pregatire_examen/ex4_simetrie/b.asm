bits 32
segment code use32 public code
global simetrie

simetrie:
    ;simetrie(word  - dword in stack) -> returns 1 if mirrored 0 otherwise
    mov eax, 1
    mov ebx, [esp+4] ; iau ce s-a pus pe stiva
    mov ecx, 8
    repeta:
        mov dx, 0
        shr bl, 1
        adc dl, 0
        shl bh, 1
        adc dh, 0 
        cmp dl, dh
        je continue
        mov eax, 0
        ret 4
        continue:
    loop repeta
    
    ret 4