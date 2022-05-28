#problema 11

#date de intrare: n1=2143 n2=44123
#date de iesire: 2143  si  44123  au proprietatea P.

#date de intrare: n1=21430 n2=44123
#date de iesire: 21430  si  44123  nu au proprietatea P.

#date de intrare: n1 = 213764 n2= 3295
#date de iesire: 213764  si  3295  nu au proprietatea P.

n1 = int(input("Adauga primul numar: "))
n2 = int(input("Adauga al doilea numar: "))

f1 = [0] * 10
f2 = [0] * 10

i = 0
while i<=9:
    x = n1
    ok = 0
    while x > 0:
        if i == x%10:
            f1[i] = 1
        x = int(x/10)
    i = i+1

i = 0
while i<=9:
    x = n2
    ok = 0
    while x > 0:
        if i == x%10:
            f2[i] = 1
        x = int(x/10)
    i = i+1

ok = 1
i = 0
while i<=9:
    if f1[i] != f2[i]:
        ok = 0
    i = i+1

if ok == 1:
    print(n1, " si ", n2, " au proprietatea P.")
elif ok == 0:
    print(n1, " si ", n2, " nu au proprietatea P.")
