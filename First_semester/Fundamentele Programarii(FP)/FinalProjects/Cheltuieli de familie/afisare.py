'''
    Modulul afisare.py are rolul de a printa toate rezultatele de dupa introducerea datelor de catre utilizator si dupa apelara unor functionalitati.
'''

#import colorama
#colorama.init()

def afisare_ziua(cheltuiala):

    '''
        Functia afisare_ziua(cheltuiala) are rolul de a afisa ziua dintr-o cheltuiala.
    '''

    return "Ziua: " + str(cheltuiala["ziua"])

def afisare_suma(cheltuiala):

    '''
        Functia afisare_suma(cheltuiala) are rolul de a afisa suma dintr-o cheltuiala.
    '''

    return "Suma: " + str(cheltuiala["suma"])

def afisare_tip(cheltuiala):

    '''
        Functia afisare_tip(cheltuiala) are rolul de a afisa tipul dintr-o cheltuiala.
    '''

    return "Tipul: " + str(cheltuiala["tip"])

def afisare_cheltuieli(l):

    '''
        Functia afisare_cheltuieli(l) are rolul de a afisa toate cheltuielile introduse de utilizator in lista l.
    '''

#    print(colorama.Fore.CYAN)
    if len(l) == 0:
        print("Lista de cheltuieli este goala!")
    else:
        for cheltuiala in l:
            print(afisare_ziua(cheltuiala))
            print(afisare_suma(cheltuiala))
            print(afisare_tip(cheltuiala))
            print("")

def afisare_suma_totala(suma, tip):

    '''
        Functia afisare_suma_totala(suma, tip) are rolul de a afisa suma totala(din toate cheltuielile introduse in lista) in urma executarii functiilor necesare din modulul de rapoarte. 
        Aceasta functie urmeaza a fi apelata in cadrul modului rapoarte pentru a afisa utilizatorului un mesaj inteligibil.
    '''

#    print(colorama.Fore.MAGENTA)
    print("Suma totala pentru tipul ", tip, " este: ", suma)