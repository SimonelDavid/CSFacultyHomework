import colorama
colorama.init()

def citire(l):
    '''
        Functia citire(l) are rolul de a citi elementele unei liste l introduse de utilizator in scopul efectuarii unor operatii cu aceasta lista de elemente.
        Am folosit colorama in scopul de a colora textul afisat.
    '''
    print(colorama.Fore.BLUE)
    print("Introdu numere in lista!")
    print("Atentie! La introducerea unui caracter care nu este numar, citirea se va opri!")

    while True:
        try:
            nr = int(input(""))
            l.append(nr)
        except ValueError:
            return

def elem_egale(l):
    '''
        Functia elem_egale(l) are rolul de a cauta secventa cea mai lunga de elemente din lista l cu proprietatea ca acestea sunt egale intre ele.
    '''
    i = 1
    j = 0
    n = len(l)
    max = 0

    print(colorama.Fore.MAGENTA)

    #Cautam secventa cea mai lunga cu elemente egale intre ele.
    while i < n:
        if l[i] == l[i-1]:
            j = j+1
        else:
            j = 0
        if j>max:
            max = j
        i = i+1
    
    #Daca nu exista o astfel de secventa, toate elementele consecutive fiind diferite intre ele, vom afisa mesajul "Nu exista o astfel de secventa. Toate numerele sunt diferite sau nu exista doua elemente consecutive egale."
    if max == 0:
        print("Nu exista o astfel de secventa. Toate numerele sunt diferite sau nu exista doua elemente consecutive egale.")
    
    #Daca exista una sau mai multe secvente de lungime maxima(pot exista doua secvente diferite cu aceeasi lungime, aceasta fiind maxima), vor fi afisate elementele care o/le compun.
    elif max > 0:
        i = 0
        j = 0
        while i < n:
            if i+1 < n and l[i] == l[i+1]:
                j = j+1
            elif i+1>=n or l[i] != l[i+1]:
                if j == max:
                    print("O secventa de lungime maxima cu numere intregi este: ")
                    k = i
                    while j >= 0:
                        print(l[k])
                        k = k-1
                        j = j - 1
                j = 0
            i = i+1

def suma_max(l):

    '''
        Functia suma_max(l) are rolul de a cauta secventa de lungime maxima din lista l in care se regaseste suma maxima a lementelor.
        Nu poate exista mai mult de o secventa prin urmatorul exemplu : l = [1,2,3,-6,2,2,2], aici avem doua secvente de lungimi egale 1+2+3=6 si 2+2+2=6.
        Daca luam in considerare pe -6, acesta nu face altceva decat sa anuleze suma primilor 3 termen.
        Astfel secventa de lungime maxima este formata din primele 3 elemente, cu al doilea si cu ultimele 3.
    '''

    i = 0
    st = 0
    dr = 0
    s = -1
    smax = l[0]
    start = 0
    n = len(l)

    #Cautam elementul din stanga si cel din dreapta al seceventei celei mai lungi cu suma elementelor maxima.
    while i < n:
        if s < 0:
            s = 0
            start = i
        s = s+l[i]
        if s >= smax:
            smax = s
            st = start
            dr = i
        i = i+1
    print(colorama.Fore.CYAN)
    print("Suma maxima este: ", smax, "Iar elementele sunt: ")
    
    #Afisam secventa de lungime maxima din lista l cu suma elementelor maxima.
    while st <= dr:
        print(l[st])
        st = st+1

def afisare_repetabilitate(max,x,l):
    '''
        Functia afisare_repetabilitate(max,x,l) are rolul de a afisa elementele din lista l care respecta regula: "in oricare 3 elemente consecutive exista o valoare care se repeta."
    '''
    
    nx = len(x)

    print(colorama.Fore.CYAN)
    if nx == 0:
        print("Nu exista cel putin o valoare care se repeta intre 3 elemente consecutive.")
    elif nx > 0:
        n = len(l)
        j = 0
        while j<nx:
            print("Una dintre secventele cu 3 elemente consecutive in care se gaseste o valoare care se repeta este: ")
            i = x[j]-max+1
            while i<=x[j]+1:
                print(l[i])
                i = i+1
            j = j+1

def repetabilitate(l):

    '''
        Functia repetabilitate(l) are rolul de a afla indicii finali si de a-i memora in lista x secventelor de lungime maxima din lista l cu regula: "in oricare 3 elemente consecutive exista o valoare care se repeta."
    '''

    i = 2
    n = len(l)
    j = 0
    max = 0
    x = []

    while i<n:
        if l[i] == l[i-1] or l[i] == l[i-2] or l[i-1] == l[i-2]:
            j = j+1
        else:
            j = 0
        if j > max:
            max = j
        i = i+1
    
    j = 0
    i = 2
    while i<n:
        if l[i] == l[i-1] or l[i] == l[i-2] or l[i-1] == l[i-2]:
            j = j+1
        else:
            j = 0
        if j == max:
            x.append(i-1)
        i = i+1
    afisare_repetabilitate(max,x,l)

def afisare(l):

    '''
        Functia afisare(l) afiseaza elementele listei l.
    '''

    print(colorama.Fore.YELLOW)
    print("Lista de numere intregi este: ")
    for x in l:
        print(x)

def testatre():
    l=[3,10,-15,10,7,20,20,20,7]
    assert(elem_egale(l) == ("O secventa de lungime maxima cu numere intregi este: \n20\n20\n20"))
 
def meniu():

    '''
        Meniul este creat in scopul de a-l ajuta pe utilizator sa ofere comenzi programului. Functia meniu() este doar o functie pentru interfata programului.
    '''

    print(colorama.Fore.LIGHTGREEN_EX)
    print("1. Citeste o lista de numere intregi.")
    print("2. Afiseaza secventa cea mai lunga in care se regasesc elemente egale consecutive.")
    print("3. Afiseaza secventa de elemente consecutive cu suma maxima.")
    print("4. Afiseaza secventa maxima unde intre 3 elemente exista o valoare care se repeta.")
    print("5. Afiseaza lista de numere intregi.")
    print("Pentru a parasi aplicatia introduceti comanda exit.")
    print("")

def run():

    '''
        Functia run() face meniul functional si memoreaza in l, o lista de elemente prin citirea lor de la tastatura.
    '''

    l = []
    while True:
        meniu()
        cmd = input(">>> ")
        if cmd == "exit":
            print(colorama.Fore.LIGHTRED_EX)
            print("Multumesc pentru utilizare! Salut!")
            return
        elif cmd == "1":
            citire(l)
        elif cmd == "2":
            elem_egale(l)
        elif cmd == "3":
            suma_max(l)
        elif cmd == "4":
            repetabilitate(l)
        elif cmd == "5":
            afisare(l)
        else:
            print(colorama.Fore.RED)
            print("Comanda este invalida! Te rog adauga una dintre comenzile 1, 2, 3, 4 sau exit.")

def main():

    '''
        Functia main() ajuta la apelarea functiei run() in scopul functionarii programului. Functia este apelata mai jos pentru a da start proceselor.
    '''

    print(colorama.Fore.LIGHTRED_EX)
    print("")
    print("      Aplicatie pentru lucrul cu liste de numere intregi")
    run()

main()