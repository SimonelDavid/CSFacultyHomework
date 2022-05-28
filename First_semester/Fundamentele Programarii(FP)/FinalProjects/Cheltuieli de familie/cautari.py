
'''
    Modulul cautari.py are roulul de a efectua diverse cautari prin lista de cheltuieli.
'''

from filtrare import comparare
from validare import get_suma, get_tip

def max(a,b):

    '''
        Functia max(a,b) are rolul de a returna valoarea mai mare din a si b.
    '''

    if a > b:
        return a
    else:
        return b

def cauta_suma(l, suma_locala):

    '''
        Functia cauta_suma(l, suma_locala) are rolul de a cauta in lista cheltuieli cu o suma mai mare decat cea introdusa de utilizator.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista exista o cheltuiala adaugata, dar nu sunt zile in care exista o suma cu numar mai mare, se va afisa mesajul "In lista de cheltuieli nu sunt zile in care se regaseste o suma mai mare decat ", suma_locala, ".".
    '''

    l1 = []
    if len(l) == 0:
        raise Exception("Lista de cheltuieli este goala!\n")
    else:
        i = 0
        for cheltuiala in l:
            if max(get_suma(cheltuiala),suma_locala) == get_suma(cheltuiala):
                l1.append(cheltuiala)
                i = 1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt zile in care se regaseste o suma mai mare decat ", suma_locala, ".\n")
        else:
            return l1

def cauta_tip(l, tip_local):

    l1 = []

    if len(l) == 0:
        raise Exception("Lista de cheltuieli este goala!\n")
    else:
        i = 0
        for cheltuiala in l:
            if comparare(get_tip(cheltuiala),tip_local) == True:
                l1.append(cheltuiala)
                i = 1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt cheltuieli de tipul ",tip_local,".\n")
        else:
            return l1