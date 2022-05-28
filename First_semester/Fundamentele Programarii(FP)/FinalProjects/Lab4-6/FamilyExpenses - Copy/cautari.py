
'''
    Modulul cautari.py are roulul de a efectua diverse cautari prin lista de cheltuieli.
'''

from afisare import afisare_ziua, afisare_suma, afisare_tip
from filtrare import comparare
from validare import get_ziua, get_suma, get_tip

import colorama
colorama.init()

def max(a,b):

    '''
        Functia max(a,b) are rolul de a returna valoarea mai mare din a si b.
    '''

    if a > b:
        return a
    else:
        return b

def min(a,b):

    '''
        Functia min(a,b) are rolul de a returna valoarea mai mica din a si b.
    '''

    if a < b:
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
            raise Exception("In lista de cheltuieli nu sunt zile in care se regaseste o suma mai mare decat "+str(suma_locala)+".\n")
        else:
            return l1

def cauta_tip(l, tip_local):

    '''
        Functia cauta_tip(l, tip_local) are rolul de a cauta in lista, cheltuieli de tipul introdus de utilizator prin variabila tip_local.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista exista cel putin o cheltuiala adaugata, dar nu sunt cheltuieli de tipul tip_local, se va afisa mesajul "In lista de cheltuieli nu sunt zile in care se regaseste o suma mai mare decat ", suma_locala, ".".
    '''

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
            raise Exception("In lista de cheltuieli nu sunt cheltuieli de tipul "+str(tip_local)+".\n")
        else:
            return l1

def cauta_ziua_si_suma(l, zi_locala, suma_locala):

    '''
        Functia cauta_ziua_si_suma(l, zi_locala, suma_locala) are rolul de a cauta in lista cheltuieli zile precedente zilei zi_locala si cu o suma mai mica decat suma_locala.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista exista o cheltuiala adaugata, dar nu sunt zile precedente zilei zi_locala si nici suma mai mica decat suma_locala, se va afisa mesajul "In lista de cheltuieli nu sunt zile precedente zilei "+str(zi_locala)+" si nici sume ale cheltuielilor mai mici decat "+str(suma_locala)+".\n".

        Daca in lista exista o cheltuiala adaugata, dar nu sunt zile precedente zilei zi_locala dar se gaseste suma mai mica decat suma_locala, se va afisa mesajul "In lista de cheltuieli nu sunt zile precedente zilei "+str(zi_locala)+" dar sunt sume ale cheltuielilor mai mici decat "+str(suma_locala)+".\n".

        Daca in lista exista o cheltuiala adaugata sunt zile precedente zilei zi_locala, dar nu este suma mai mica decat suma_locala, se va afisa mesajul "In lista de cheltuieli sunt zile precedente zilei "+str(zi_locala)+" dar nu sunt sume ale cheltuielilor mai mici decat "+str(suma_locala)+".\n".
    '''

    l1 = []
    if len(l) == 0:
        raise Exception("Lista de cheltuieli este goala!\n")
    else:
        i = 0
        j = 0
        for cheltuiala in l:
            if get_ziua(cheltuiala) < zi_locala:
                if get_suma(cheltuiala) < suma_locala:
                    l1.append(cheltuiala)
                    j = 1
                i = 1
            elif get_suma(cheltuiala) < suma_locala:
                j = 1
        if i == 0 and j == 0:
            raise Exception("In lista de cheltuieli nu sunt zile precedente zilei "+str(zi_locala)+" si nici sume ale cheltuielilor mai mici decat "+str(suma_locala)+".\n")
        elif i == 0 and j == 1:
            raise Exception("In lista de cheltuieli nu sunt zile precedente zilei "+str(zi_locala)+" dar sunt sume ale cheltuielilor mai mici decat "+str(suma_locala)+".\n")
        elif i == 1 and j == 0:
            raise Exception("In lista de cheltuieli sunt zile precedente zilei "+str(zi_locala)+" dar nu sunt sume ale cheltuielilor mai mici decat "+str(suma_locala)+".\n")
        else:
            return l1