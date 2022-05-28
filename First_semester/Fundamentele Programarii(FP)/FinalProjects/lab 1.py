number=int(input("Adauga numar pentru suma:"))
sum = 0
for value in range(1, number+1):
    sum = sum + value
print(sum)

n = int(input("adauga numar pentru verificarea daca este prim:"))
j = 0
for i in range(2, int(n/2)):
    if n%i == 0:
       j = j+1 
if j == 0:
    print("este prim")
else:
    print("nu este prim")

x = int(input("adauga primul numar pentru cmmdc:"))
y = int(input("adauga al doilea numar pentru cmmdc:"))

while x != y and x != 0 and y != 0:
    if x>y:
        if x < 0:
            y = y-x
        else:
            x = x-y
    else:
        if y<0:
            x = x-y
        else:
            y = y-x

print(x)
