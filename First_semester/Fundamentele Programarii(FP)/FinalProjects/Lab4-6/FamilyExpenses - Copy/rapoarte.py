'''
    Functia rapoarte.py are rolul de a realiza un set de rapoarte pentru lista de cheltuieli introdusa de utilizator.
'''

from afisare import afisare_suma_totala

import colorama

from validare import get_suma, get_tip, get_ziua
colorama.init()

def calculator_suma(suma, s):

    '''
        Functia calculator_suma(suma, s) are rolul de a returna suma dintre variabilele de timp float suma si s transmise ca parametru.
    '''

    suma_noua = suma + s

    return suma_noua
    

def suma_totala(l, tip):

    '''
        Functia suma_totala(l, tip) are rolul de a returna suma totala a cheltuilelilor din lista l de tipul tip.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista nu sunt inregistrate cheltuieli de tipul tip, va fi afisata eroarea "Nu s-au gasit cheltuieli de tipul ",tip,"\n".
    '''

    if len(l) == 0:
        raise Exception("Lista de cheltuieli este goala!\n")
    else:
        s = 0
        for cheltuiala in l:
            if cheltuiala[2] == tip:
                s = calculator_suma(s,cheltuiala[1])
        if s == 0:
            raise Exception("Nu s-au gasit cheltuieli de tipul ",tip,"\n")
        else:
            return s

def cauta_suma_max(l):

    '''
        Functia suma_max(l) are rolul de a returna ziua cu suma maxima a cheltuilelilor din lista l.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".
    '''

    if len(l) == 0:
        raise Exception(colorama.Fore.RED+"Lista de cheltuieli este goala!\n")
    else:
        l1 = []
        i = 1
        while i < 32:
            l1.append(0)
            i = i+1

        smax = -1
        zi = -1
        for cheltuiala in l:
            z = get_ziua(cheltuiala)
            s = get_suma(cheltuiala)
            l1[z] += s

        for i in range(len(l1)):
            if l1[i] > smax:
                smax = l1[i]
                zi = i
            i = i+1
        return zi

def cauta_cheltuieli_cu_o_anumita_suma(l, suma):
    
    '''
        Functia cauta_cheltuieli_cu_o_anumita_suma(l, suma) are rolul de a cauta in lista de cheltuieli inregistrari de suma egala cu suma.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista nu sunt inregistrate cheltuieli cu suma egala cu suma, va fi afisata eroarea "In lista de cheltuieli nu sunt inregistrari care sa aiba suma "+str(suma)+".\n".
    '''

    if len(l) == 0:
        raise Exception(colorama.Fore.RED+"Lista de cheltuieli este goala!\n")
    else:
        l1 = []
        i = 0

        for cheltuiala in l:
            if get_suma(cheltuiala) == suma:
                l1.append(cheltuiala)
                i = 1
        if i == 0:
            raise Exception(colorama.Fore.RED+"In lista de cheltuieli nu sunt inregistrari care sa aiba suma "+str(suma)+".\n")
        else:
            return l1

def cauta_cheltuieli_de_un_anumit_tip(l, tip):

    '''
        Functia cauta_cheltuieli_de_un_anumit_tip(l, tip) are rolul de a cauta in lista de cheltuieli inregistrari de tipul tip.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista nu sunt inregistrate cheltuieli de tipul tip, va fi afisata eroarea "In lista de cheltuieli nu sunt inregistrari de tipul "+str(tip)+".\n".
    '''

    if len(l) == 0:
        raise Exception(colorama.Fore.RED+"Lista de cheltuieli este goala!\n")
    else:

        l1 = []
        i = 0

        for cheltuiala in l:
            if get_tip(cheltuiala) == tip:
                l1.append(cheltuiala)
                i = 1
        if i == 0:
            raise Exception(colorama.Fore.RED+"In lista de cheltuieli nu sunt inregistrari de tipul "+str(tip)+".\n")
        else:
            return l1