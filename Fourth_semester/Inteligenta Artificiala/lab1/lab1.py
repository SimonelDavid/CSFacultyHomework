import math

#1 Să se determine ultimul (din punct de vedere alfabetic) cuvânt care poate apărea într-un text care conține mai multe cuvinte separate prin ” ” (spațiu). De ex. ultimul (dpdv alfabetic) cuvânt din ”Ana are mere rosii si galbene” este cuvântul "si".
def ult_cuv(text):
    cuvinte = text.split()
    cuvinte.sort(reverse=True)
    return cuvinte[0]
#2 Să se determine distanța Euclideană între două locații identificate prin perechi de numere. De ex. distanța între (1,5) și (4,1) este 5.0
def dist_euc(locatie1, locatie2):
    x1, y1 = locatie1
    x2, y2 = locatie2
    distanta = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    return distanta

#3 Să se determine produsul scalar a doi vectori rari care conțin numere reale. Un vector este rar atunci când conține multe elemente nule. Vectorii pot avea oricâte dimensiuni. De ex. produsul scalar a 2 vectori unisimensionali [1,0,2,0,3] și [1,2,0,3,1] este 4.
def sc_prod(vec1, vec2):
    # verificăm dacă vectorii au aceeași dimensiune
    if len(vec1) != len(vec2):
        return None

    # inițializăm suma
    result = 0

    # parcurgem ambii vectori simultan
    for i in range(len(vec1)):
        # înmulțim elementele corespunzătoare ne-nule
        if vec1[i] != 0 and vec2[i] != 0:
            result += vec1[i] * vec2[i]

    return result

#4 Să se determine cuvintele unui text care apar exact o singură dată în acel text. De ex. cuvintele care apar o singură dată în ”ana are ana are mere rosii ana" sunt: 'mere' și 'rosii'.
def det_cuv(text):
    # separăm textul în cuvinte
    cuvinte = text.split()

    # numărăm de câte ori apare fiecare cuvânt în text
    aparitii = {}
    for cuvant in cuvinte:
        if cuvant in aparitii:
            aparitii[cuvant] += 1
        else:
            aparitii[cuvant] = 1

    # găsim cuvintele care apar doar o dată
    rezultat = []
    for cuvant, frecventa in aparitii.items():
        if frecventa == 1:
            rezultat.append(cuvant)
    return rezultat

#5 Pentru un șir cu n elemente care conține valori din mulțimea {1, 2, ..., n - 1} astfel încât o singură valoare se repetă de două ori, să se identifice acea valoare care se repetă. De ex. în șirul [1,2,3,4,2] valoarea 2 apare de două ori.
def gas_val_rep(lista):
    n = len(lista)
    suma_1_n_minus_1 = sum(range(1, n))

    # calculăm suma elementelor din lista
    suma_lista = sum(lista)

    # diferența dintre cele două sume este valoarea care se repetă
    valoare_repetata = suma_lista - suma_1_n_minus_1

    return valoare_repetata

#6 Pentru un șir cu n numere întregi care conține și duplicate, să se determine elementul majoritar (care apare de mai mult de n / 2 ori). De ex. 2 este elementul majoritar în șirul [2,8,7,2,2,5,2,3,1,2,2].
def gaseste_element_majoritar(lista):
    majoritar_potential = None
    count = 0

    # prima trecere: găsim un element majoritar potențial
    for numar in lista:
        if count == 0:
            majoritar_potential = numar
        if numar == majoritar_potential:
            count += 1
        else:
            count -= 1

    # verificăm dacă elementul majoritar potențial se află în șir de mai mult de n/2 ori
    count = 0
    for numar in lista:
        if numar == majoritar_potential:
            count += 1

    if count > len(lista) / 2:
        return majoritar_potential
    else:
        return None
#7 Să se determine al k-lea cel mai mare element al unui șir de numere cu n elemente (k < n). De ex. al 2-lea cel mai mare element din șirul [7,4,6,3,9,1] este 7.
def gaseste_k_element(lista, k):
    sorted_lista = sorted(lista, reverse=True)
    return sorted_lista[k-1]

#8 Să se genereze toate numerele (în reprezentare binară) cuprinse între 1 și n. De ex. dacă n = 4, numerele sunt: 1, 10, 11, 100.
def generate_binary_numbers(n):
    result = []
    for i in range(1, n+1):
        result.append(bin(i)[2:])
    return result

def main():
    #1
    print("ex 1")
    text = "Ana are mere rosii si galbene"
    print(ult_cuv(text))

    #2
    print("ex 2")
    locatie1 = (1, 5)
    locatie2 = (4, 1)
    print(dist_euc(locatie1, locatie2)) 

    #3
    print("ex 3")
    vec1 = [1, 0, 2, 0, 3]
    vec2 = [1, 2, 0, 3, 1]
    print(sc_prod(vec1, vec2))

    #4
    print("ex 4")
    text = "ana are ana are mere rosii ana"
    print(det_cuv(text))

    #5
    print("ex 5")
    lista = [1, 2, 3, 4, 2]
    valoare_repetata = gas_val_rep(lista)
    print(valoare_repetata)

    #6
    print("ex 6")
    lista = [2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]
    element_majoritar = gaseste_element_majoritar(lista)
    print(element_majoritar)

    #7
    print("ex 7")
    lista = [7, 4, 6, 3, 9, 1]
    k = 2
    k_element = gaseste_k_element(lista, k)
    print(k_element)

    #8
    print("ex 8")
    print(generate_binary_numbers(4))

main()