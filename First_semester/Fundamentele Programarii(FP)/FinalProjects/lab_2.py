#problema 4

def NrPrim(x):
    j = 0
    for i in range(2, int(x/2)+1):
        if x%i == 0:
            j = j+1
    if j == 0:
        return 1
    return 0

n = int(input("Adauga numarul natural n: "))
ok = 0
if n<5 or n%2 == 0:                                                                                         
    if n>3 and NrPrim(int(n/2)) == 1:                                                                               
        print("Numarul n este format din suma numerelor prime ", int(n/2), "si", int(n/2), ".")             
        ok = 1
    else:
        print("Nu exista doua numare prime care prin operatia de adunare pot sa formeze numarul", n, ".")
        ok = 1


if ok == 0:                                                                                                 
    p1 = 2                                                                                                  
    p2 = n                                                                                                  
    while p1 <= int(n/2):                                                                                   
        while p2 >= int(n/2):
            if NrPrim(p1) == 1 and NrPrim(p2) == 1 and p1+p2 == n:
                print("Numarul n este format din suma numerelor prime ", p1, "si", p2, ".")                 
            p2 = p2-1
        p1 = p1+1
                
