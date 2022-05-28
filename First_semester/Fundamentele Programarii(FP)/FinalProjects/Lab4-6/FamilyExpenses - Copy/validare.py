'''
    Modulul validare.py are rolul de a valida datele introduse de utilizator.
'''

import colorama
colorama.init()

def get_ziua(cheltuiala):
    
    '''
        Functia get_ziua(cheltuiala) are rolul de a returna ziua cheltuielii.
    '''
    #return cheltuiala["ziua"]
    return cheltuiala[0]

def get_suma(cheltuiala):

    '''
        Functia get_suma(cheltuiala) are rolul de a returna suma cheltuielii.
    '''
    #return cheltuiala["suma"]
    return cheltuiala[1]

def get_tip(cheltuiala):

    '''
        Functia get_tip(cheltuiala) are rolul de a returna tipul cheltuielii.
    '''
    #return cheltuiala["tip"]
    return cheltuiala[2]

def set_ziua(cheltuiala, zi):

    '''
        Functia set_ziua(cheltuiala) are rolul de a seta ziua unei cheltuieli
    '''
    #cheltuiala["ziua"] = zi
    cheltuiala[0] = zi

def set_suma(cheltuiala, suma):

    '''
        Functia set_suma(cheltuiala) are rolul de a seta suma unei cheltuieli
    '''
    #cheltuiala["suma"] = suma
    cheltuiala[1] = suma

def set_tip(cheltuiala, tip):

    '''
        Functia set_tip(cheltuiala) are rolul de a seta tipul unei cheltuieli
    '''
    #cheltuiala["tip"] = tip
    cheltuiala[2] = tip

def validare_ziua(zi):

    '''
        Functia validare_ziua(cheltuiala) are rolul de a valida valoarea introdusa de utilizator pentru ziua. 
        In cazul in care numarul zilei nu se afla in intervalul [1,31] citirea nu va avea loc, iar utilizatorului i se va afisa mesajul "Indexul zilei invalid. Introduceti o zi valida dintr-o luna!\n"
    '''

    print(colorama.Fore.RED)
    eroare = ""
    if zi < 1 or zi > 31 or zi == "":
        eroare += "Indexul zilei invalid. Introduceti o zi valida dintr-o luna!\n"
    if len(eroare) > 0:
        raise Exception(eroare)

def validare_suma(s):

    '''
        Functia validare_suma(s) are rolul de a valida valoarea introdusa de utilizator pentru suma.
        In cazul in care suma este o valoare negativa, citirea nu va avea loc, iar utilizatorului ii va fi afisat mesajul "Suma nu poate fi una negativa! Trebuie sa introduceti suma cu numar pozitiv!\n"
    '''

    print(colorama.Fore.RED)
    eroare = ""
    if s == "" or type(s)==str or s < 0:
        eroare += "Suma nu poate fi una negativa! Trebuie sa introduceti suma cu numar pozitiv!\n"
    if len(eroare) > 0:
        raise Exception(colorama.Fore.RED+eroare)

def validare_tip(t):

    '''
        Functia validare_tip(t) are rolul de a valida valoarea introdusa de utilizator pentru tip.
        In cazul in care suma este o valoare negativa, citirea nu va avea loc, iar utilizatorului ii va fi afisat mesajul "Suma nu poate fi una negativa! Trebuie sa introduceti suma cu numar pozitiv!\n"
    '''

    print(colorama.Fore.RED)
    eroare = ""
    if t == "":
        eroare += "Tip de cheltuiala invalid!\nAtentie! Nu lasati campul gol!\n"
    if len(eroare) > 0:
        raise Exception(eroare)

def validare_cheltuiala(cheltuiala):

    '''
        Functia validare_cheltuiala(cheltuiala) are rolul de a valida o cheltuiala transimsa ca parametru.
        Aceasta functie valideaza o cheltuiala ca intreg si nu este compusa prin apelarea ulterioarelor validari particulare a elementelor introduse de utilizator.
    '''

    print(colorama.Fore.RED)
    eroare = ""

    if get_ziua(cheltuiala) < 1 or get_ziua(cheltuiala) > 31 or get_ziua(cheltuiala) == "":
        eroare += "Indexul zilei invalid. Introduceti o zi valida dintr-o luna!\n"
    if get_suma(cheltuiala) < 0 or get_suma(cheltuiala) == "":
        eroare += "Suma nu poate fi una negativa! Trebuie sa introduceti suma cu numar pozitiv!\n"
    if get_tip(cheltuiala) == "":
        eroare += "Tip de cheltuiala invalid!\nAtentie! Nu lasati campul gol!\n"
    
    if len(eroare) > 0:
        raise Exception(eroare)