
'''
    Modulul filtrare.py are rolul de a realiza anumite filtrari ale listei de cheltuieli. 
    Functiile acestui modul sunt adesea apelate in modulul meniu.py, iar altele testate in modulul test.py.
'''

from validare import get_suma, get_tip
#from cautari import max

import colorama
colorama.init()

def comparare(a, b):

    '''
        Functia comparare(a,b) are rolul de a verifica daca doua date ale unor cheltuieli diferite sunt sau nu egale. 
        Daca ambele tipuri sunt identice, functia va returna True, iar daca sunt diferite prin cel putin un caracter, functia va returna false.
    '''

    if a == b:
        return True
    else:
        return False

def filtrare_dupa_tip(l, tipul):

    '''
        Functia filtrare_dupa_tip(l, tipul) are rolul de a afisa utilizatorului cheltuieli cu tipul diferit de variabila "tipul" transimsa ca parametru, 
        citita si validata in modulul meniu.py in submeniul de filtrare.

        input:  l     - lista
                tipul - str
        output: returneaza cheltuieli diferite de tipul "tipul"
    '''

    l1 = []

    if len(l) == 0:
        raise Exception("Lista de cheltuieli este goala!\n")
    else:
        i = 0
        for cheltuiala in l:
            if comparare(get_tip(cheltuiala),tipul) == False:
                l1.append(cheltuiala)
                i = 1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt tipuri diferite fata de tipul "+str(tipul)+".\n")
        else:
            return l1

def filtrare_dupa_suma(l, s):

    '''
        Functia filtrare_dupa_suma(l, s) are rolul de a afisa utilizatorului cheltuieli de suma mai mare decat variabila "s" transimsa ca parametru, 
        citita si validata in modulul meniu.py in submeniul de filtrare.

        input:  l - lista
                s - int
        output: returnare cheltuieli cu suma mai mare decat "s".
    '''
    
    if len(l) == 0:
        raise Exception("Lista de cheltuieli este goala!\n")
    else:
        l1 = []
        i = 0
        for cheltuiala in l:
            if max(get_suma(cheltuiala),s) == get_suma(cheltuiala):
                l1.append(cheltuiala)
                i=1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt cheltuieli cu suma mai mare decat "+str(s)+".\n")
        else:
            return l1