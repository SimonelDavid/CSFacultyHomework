'''
    Modulul meniu.py este folosit in scopul realizarii unei interfete pentru utilizator, functia run fiind apelata in modulul principal.py.
'''

from citire import introducere_suma, introducere_tip, ui_adauga_cheltuiala, introducere_suma
from afisare import afisare_cheltuieli, afisare_suma_totala
from cautari import cauta_suma, cauta_tip
from rapoarte import suma_totala
from validare import validare_ziua, validare_suma, validare_tip
from filtrare import filtrare_dupa_tip

#import colorama
#colorama.init()

def meniu():

    '''
        Meniul este creat in scopul de a-l ajuta pe utilizator sa ofere comenzi programului. Functia meniu() este doar o functie pentru interfata programului.
    '''

#    print(colorama.Fore.LIGHTRED_EX)
    print("      Aplicatie care gestioneaza cheltuielile unei familii")
#    print(colorama.Fore.LIGHTGREEN_EX)
    print("1. Adauga cheltuiala.")
    print("2. Sterge cheltuiala.")
    print("3. Efectueaza o cautare printre cheltuieli.")
    print("4. Efectueaza un raport.")
    print("5. Efectueaza o filtrare.")
    print("6. Afiseaza cheltuielile.")
    print("Pentru a parasi aplicatia introduceti comanda exit.")
    print("Pentru a readuce lista de cheltuieli cu o modificare inapoi introduceti comanda undo.")
    print("")

def meniu_citire():

    '''
        Functia meniu_citire() este un submeniu, realizat doar sub forma unei interfate. 
    '''

#    print(colorama.Fore.YELLOW)
    print("a. Adauga o noua cheltuiala")
    #print("b. Actualizeaza cheltuiala")
    print("Scrie comanda back pentru a te intoarce in meniul principal.")
    print("Scrie comanda exit pentru a iesi din program.")
    print("")

def meniu_cautari():

    '''
        Functia meniu_cautari() este un submeniu, realizat doar sub forma unei interfate.
    '''

#    print(colorama.Fore.LIGHTYELLOW_EX)
    print("a. Tipareste toate cheltuielile cu suma mai mari decat o suma data.")
    print("b. Urmeaza a fi realizat")
    #print("b. Tipareste toate cheltuielile efectuate inainte de o zi data si mai mici decat o sumă.")
    print("c. Tipăreste toate cheltuielile de un anumit tip.")
    print("Scrie comanda back pentru a te intoarce in meniul principal.")
    print("Scrie comanda exit pentru a iesi din program.")
    print("")

def meniu_rapoarte():

    '''
        Functia meniu_rapoarte() este un submeniu, realizat doar sub forma unei interfate.
    '''

#    print(colorama.Fore.LIGHTYELLOW_EX)
    print("a. Tipareste suma totala pentru un anumit tip de cheltuiala.")
    #print("b. Gaseste ziua in care suma cheltuita e maxima.")
    #print("c. Tipareste toate cheltuielile de un anumit tip.")
    #print("d. Tipareste cheltuielile sortate după tip")
    print("Scrie comanda back pentru a te intoarce in meniul principal.")
    print("Scrie comanda exit pentru a iesi din program.")
    print("")

def meniu_filtrare():

    '''
        Functia meniu_filtrare() este un submeniu, realizat doar sub forma unei interfate.
    '''

#    print(colorama.Fore.LIGHTYELLOW_EX)
    print("a. Elimina toate cheltuielile de un anumit tip.")
    #print("b. Elimina toate cheltuielile mai mici decât o suma data.")
    print("Scrie comanda back pentru a te intoarce in meniul principal.")
    print("Scrie comanda exit pentru a iesi din program.")
    print("")

def run():

    '''
        Functia run() face meniul functional si memoreaza in l, o lista de cheltuieli prin citirea lor de la tastatura.
        Pentru fiecare comanda se deschide un submeniu unde se pot efectua mai multe operatii.
    '''

    l = []
    while True:
        meniu()
        cmd = input(">>> ")
#        print(colorama.Fore.YELLOW)

        if cmd == "exit":
#            print(colorama.Fore.LIGHTRED_EX)
            print("Multumesc pentru utilizare! Salut!")
            return

        #se efectueaza citirea
        elif cmd == "1":                                
            while cmd == "1":
                meniu_citire()
                cmd1 = input(">>> ")
                if cmd1 == "a":
                    try:
                        ui_adauga_cheltuiala(l)
                    except Exception as ex:
                        print(ex)
                elif cmd1 == "back":
                    cmd = "back"
                elif cmd1 == "exit":
#                    print(colorama.Fore.LIGHTRED_EX)
                    print("Multumesc pentru utilizare! Salut!")
                    return
                else:
#                    print(colorama.Fore.RED)
                    print("Comanda este invalida! Te rog adauga una dintre comenzile a, back sau exit.")


        elif cmd == "2":
            print("Functiile comenzii 2 vor aparea incurand.")

        #se efectueaza functia de cautare
        elif cmd == "3":                                                                        
            while cmd == "3":
                meniu_cautari()
                cmd1 = input(">>> ")
                if cmd1 == "a":
                    l1 = []
                    print("Adauga o suma pentru tiparirea cheltuielilor cu o suma mai mare.")
                    s = introducere_suma()
                    try:
                        validare_suma(s)
                        l1 = cauta_suma(l, s)
                        afisare_cheltuieli(l1)
                    except Exception as ex:
                        print(ex)
                elif cmd1 == "c":
                    l1 = []
                    print("Adauga un tip pentru tiparirea cheltuielilor cu un tipul dorit.")
                    t = introducere_tip()
                    try:
                        validare_tip(t)
                        l1 = cauta_tip(l,t)
                        afisare_cheltuieli(l1)
                    except Exception as ex:
                        print(ex)
                elif cmd1 == "back":
                    cmd = "back"
                elif cmd1 == "exit":
#                    print(colorama.Fore.LIGHTRED_EX)
                    print("Multumesc pentru utilizare! Salut!")
                    return
                else:
#                    print(colorama.Fore.RED)
                    print("Comanda este invalida! Te rog adauga una dintre comenzile a, back sau exit.")

        #se efectueaza functia de rapoarte
        elif cmd == "4":                                                                       
            while cmd == "4":
                meniu_rapoarte()
                cmd1 = input(">>> ")
                if cmd1 == "a":
                    print("Adauga un tip de cheltuiala pentru suma totala a acelui tip.")
                    t = introducere_tip()
                    try:
                        validare_tip(t)
                        s = suma_totala(l,t)
                        afisare_suma_totala(s,t)
                    except Exception as ex:
                        print(ex)
                elif cmd1 == "back":
                    cmd = "back"
                elif cmd1 == "exit":
#                    print(colorama.Fore.LIGHTRED_EX)
                    print("Multumesc pentru utilizare! Salut!")
                    return
                else:
#                    print(colorama.Fore.RED)
                    print("Comanda este invalida! Te rog adauga una dintre comenzile a, back sau exit.")

        #se efectueaza functia de filtrare
        elif cmd == "5":                                                                        
            while cmd == "5":
                meniu_filtrare()
                cmd1 = input(">>> ")
                if cmd1 == "a":
                    l1 = []
                    print("Adauga un tip de cheltuiala pentru filtra cheltuielile in functie de tipul introdus de tine.")
                    t = introducere_tip()
                    try:
                        validare_tip(t)
                        l1 = filtrare_dupa_tip(l,t)
                        afisare_cheltuieli(l1)
                    except Exception as ex:
                        print(ex)
                elif cmd1 == "back":
                    cmd = "back"
                elif cmd1 == "exit":
#                    print(colorama.Fore.LIGHTRED_EX)
                    print("Multumesc pentru utilizare! Salut!")
                    return
                else:
#                    print(colorama.Fore.RED)
                    print("Comanda este invalida! Te rog adauga una dintre comenzile a, back sau exit.")

        #se efecetueaza afisarea
        elif cmd == "6":                                                                    
            afisare_cheltuieli(l)

        else:
#            print(colorama.Fore.RED)
            print("Comanda este invalida! Te rog adauga una dintre comenzile 1, 2, 3, 4 sau exit.")
