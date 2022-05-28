
'''
    Modulul citire.py are rolul de a introduce date in program.
'''

from afisare import afisare_suma, afisare_tip, afisare_ziua
from filtrare import comparare
from stergere import sterge_cheltuiala_dupa_zi, sterge_cheltuiala_dupa_zi_si_tip
from undo import srv_adauga_istoric
from validare import get_suma, get_tip, get_ziua, validare_cheltuiala, validare_suma, validare_tip, validare_ziua

import colorama
colorama.init()

def creeaza_cheltuiala(zi, suma, tip):

    '''
        Functia creeaza_cheltuiala(zi, suma, tip) are rolul de a creea o inregistrare sub forma unei cheltuieli.

        input: zi   - intreg
               suma - float
               tip  - string
        output: rezultat - o cheltuiala cu ziua <zi>, suma <suma> si tipul <tip>
    '''
    
    return(zi,suma,tip)
    #return{
    #    "ziua" : zi,
    #    "suma" : suma,
    #    "tip" : tip
    #}

def srv_adauga_cheltuiala(l, zi, suma, tip):

    '''
        Functia srv_adauga_cheltuiala(l, zi, suma, tip) are rolul de a valida datele introduse(prin apelarea unei functii din modulul de validare), iar daca inregistrarea este valida, noua cheltuiala este adaugata in lista.

        input:  l    - lista de cheltuieli 
                zi   - intreg
                suma - float
                tip  - string
        output: rezultat - o cheltuiala cu ziua <zi>, suma <suma> si tipul <tip>
    '''

    cheltuiala = creeaza_cheltuiala(zi,suma,tip)
    validare_cheltuiala(cheltuiala)
    adauga_cheltuiala(l,cheltuiala)

def adauga_cheltuiala(l, cheltuiala):

    '''
        Functia adauga_cheltuiala(l, cheltuiala) adauga in lista l, o cheltuiala unica indentificata prin zi si tip.

        input:  l    - lista de cheltuieli
                zi   - intreg
                suma - float
                tip  - string
        output: adauga in lista cheltuiala, daca nu exista deja in lista una din aceeasi zi cu acelasi tip.
                raises: Exception cu textul "Cheltuiala are ziua si tupul identice. Trebuie actualizata, nu adaugata una noua!\n", in cazul in care avem in aceeasi zi introdusa o cheltuiala de un tip deja introdus.
    '''

    for cheltuiala_locala in l:
        if (comparare(get_ziua(cheltuiala_locala), get_ziua(cheltuiala)) == True) and (comparare(get_tip[cheltuiala_locala], get_tip[cheltuiala]) == True):
            raise Exception("Cheltuiala are ziua si tupul identice. Trebuie actualizata, nu adaugata una noua!\n")

    l.append(cheltuiala)
    pass

def introducere_ziua():

    '''
        Functia introducere_ziua() are rolul de a citi ziua si de a verifica daca este un numar.
    '''

    try:
        zi = int(input("zi: "))
        return zi
    except ValueError:
        print(colorama.Fore.RED+"Valoare numerica invalida pentru zi!")
        return

def introducere_suma():

    '''
        Functia introducere_suma() are rolul de a citi suma si de a verifica daca este un numar.
    '''

    try:
        suma = float(input("suma: "))
        return suma
    except ValueError:
        print(colorama.Fore.RED+"Valoare numerica invalida pentru suma!")
        return

def introducere_tip():

    '''
        Functia introducere_tip() are rolul de citi tipul si de a verifica daca este un string.
    '''

    tip = input("tip: ")
    return tip

def ui_adauga_cheltuiala(l, istoric, mod):

    '''
        Functia ui_adauga_cheltuiala(l) are rolul de a creea 3 variablie(zi, suma, tip) si transmiterea lor impreuna cu a listei catre functia de service unde se efectueaza in sine toate operatiile necesare.
    '''

    zi = introducere_ziua()
    suma = introducere_suma()
    tip = introducere_tip()

    srv_adauga_cheltuiala(l, zi, suma, tip)
    if mod == 1:
        srv_adauga_istoric(istoric, 0, zi, suma, tip)

def modificare_zi(l,istoric,zi,zi_istoric,tip,mod):
    
    '''
        Functia modificare_zi(l,zi,tip) are rolul de a modifica ziua dintr-o cheltuiala deja inregistrata.
    '''

    if len(l) == 0:
        raise Exception(colorama.Fore.RED+"Mai intai trebuie sa introduceti in lista cheltuieli pentru ziua "+str(zi)+" si de tipul "+str(tip)+". Din lista de cheltuieli lipseste aceasta inregistrare.")
    else:
        for cheltuiala in l:
            if get_ziua(cheltuiala) == zi and get_tip(cheltuiala) == tip:
                l1 = []
                s = get_suma(cheltuiala)
                
                l1 = sterge_cheltuiala_dupa_zi_si_tip(l, zi, tip)
                
                z = 0

                if mod == 0:
                    z = zi_istoric
                elif mod == 1:
                    print("Introdu noua zi: \n")
                    z = introducere_ziua()

                srv_adauga_cheltuiala(l1,z,s,tip)
                
                if mod == 1:
                    srv_adauga_istoric(istoric, 1, z, s, tip)

                return l1
        raise Exception(colorama.Fore.RED+"Nu exista in lista cheltuiala de tipul "+str(tip)+" in ziua "+str(zi)+".")

def modificare_suma(l,istoric,zi,suma_istoric,tip, mod):

    '''
        Functia modificare_suma(l,zi,tip) are rolul de a modifica suma dintr-o cheltuiala deja inregistrata.
    '''
    
    if len(l) == 0:
        raise Exception(colorama.Fore.RED+"Mai intai trebuie sa introduceti in lista cheltuieli pentru ziua "+str(zi)+" si de tipul "+str(tip)+". Din lista de cheltuieli lipseste aceasta inregistrare.")
    else:
        for cheltuiala in l:
            if get_ziua(cheltuiala) == zi and get_tip(cheltuiala) == tip:
                l1 = []
                l1 = sterge_cheltuiala_dupa_zi_si_tip(l, zi, tip)
                s = 0                

                if mod == 0:
                    s = suma_istoric
                elif mod == 1:
                    print("Introdu noua suma: \n")
                    s = introducere_suma()

                srv_adauga_cheltuiala(l1,zi,s,tip)
                if mod == 1:
                    srv_adauga_istoric(istoric, 2, zi, s, tip)

                return l1
        raise Exception("Nu exista in lista cheltuiala de tipul "+str(tip)+" in ziua "+str(zi)+".")

def modificare_tip(l,istoric,zi,tip_vechi,tip,mod):
    
    '''
        Functia modificare_tip(l,zi,tip) are rolul de a modifica tipul dintr-o cheltuiala deja inregistrata.
    '''

    if len(l) == 0:
        raise Exception(colorama.Fore.RED+"Mai intai trebuie sa introduceti in lista cheltuieli pentru ziua "+str(zi)+" si de tipul "+str(tip)+". Din lista de cheltuieli lipseste aceasta inregistrare.")
    else:
        for cheltuiala in l:
            if get_ziua(cheltuiala) == zi and get_tip(cheltuiala) == tip:
                l1 = []
                s = get_suma(cheltuiala)
                
                l1 = sterge_cheltuiala_dupa_zi_si_tip(l, zi, tip)
                t = 0
                if mod == 0:
                    t = tip_vechi
                elif mod == 1:
                    print("Introdu noul tip.")
                    t = introducere_tip()

                srv_adauga_cheltuiala(l1,zi,s,t)

                if mod == 1:
                    srv_adauga_istoric(istoric, 3, zi, s, t)

                return l1
        raise Exception("Nu exista in lista cheltuiala de tipul "+str(tip)+" in ziua "+str(zi)+".")