'''
    Modulul meniu.py este folosit in scopul realizarii unei interfete pentru utilizator, functia run fiind apelata in modulul principal.py.
'''

from citire import introducere_suma, introducere_tip, introducere_ziua, modificare_suma, modificare_tip, modificare_zi, ui_adauga_cheltuiala
from afisare import afisare_cheltuieli, afisare_suma_totala
from cautari import cauta_suma, cauta_tip, cauta_ziua_si_suma
from rapoarte import cauta_cheltuieli_cu_o_anumita_suma, cauta_cheltuieli_de_un_anumit_tip, cauta_suma_max, suma_totala
from stergere import sterge_cheltuiala_de_un_anumit_tip, sterge_cheltuiala_din_interval, sterge_cheltuiala_dupa_zi, sterge_ultima_inregistrare_din_istoric
from undo import undo
from validare import validare_ziua, validare_suma, validare_tip
from filtrare import filtrare_dupa_suma, filtrare_dupa_tip

import colorama
colorama.init()

def meniu():

    '''
        Meniul este creat in scopul de a-l ajuta pe utilizator sa ofere comenzi programului. Functia meniu() este doar o functie pentru interfata programului.
    '''

    print(colorama.Fore.LIGHTRED_EX)
    print("      Aplicatie care gestioneaza cheltuielile unei familii")
    print(colorama.Fore.LIGHTGREEN_EX)
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

    print(colorama.Fore.LIGHTYELLOW_EX)
    print("a. Adauga o noua cheltuiala")
    print("b. Actualizeaza cheltuiala")
    print("Scrie comanda back pentru a te intoarce in meniul principal.")
    print("Scrie comanda exit pentru a iesi din program.")
    print("")

def meniu_stergere():

    '''
        Functia meniu_stergere() este un submeniu, realizat doar sub forma unei interfate. 
    '''

    print(colorama.Fore.LIGHTYELLOW_EX)
    print("a. Sterge toate cheltuielile dintr-o zi data.")
    print("b. Sterge cheltuielile pentru un interval de timp.")
    print("c. Sterge toate cheltuielile de un anumit tip.")
    print("Scrie comanda back pentru a te intoarce in meniul principal.")
    print("Scrie comanda exit pentru a iesi din program.")
    print("")

def meniu_cautari():

    '''
        Functia meniu_cautari() este un submeniu, realizat doar sub forma unei interfate.
    '''

    print(colorama.Fore.LIGHTYELLOW_EX)
    print("a. Tipareste toate cheltuielile cu suma mai mari decat o suma data.")
    print("b. Tipareste toate cheltuielile efectuate inainte de o zi data si mai mici decat o sumă.")
    print("c. Tipăreste toate cheltuielile de un anumit tip.")
    print("Scrie comanda back pentru a te intoarce in meniul principal.")
    print("Scrie comanda exit pentru a iesi din program.")
    print("")

def meniu_rapoarte():

    '''
        Functia meniu_rapoarte() este un submeniu, realizat doar sub forma unei interfate.
    '''

    print(colorama.Fore.LIGHTYELLOW_EX)
    print("a. Tipareste suma totala pentru un anumit tip de cheltuiala.")
    print("b. Gaseste ziua in care suma cheltuita e maxima.")
    print("c. Tipareste toate cheltuielile de o anumita suma.")
    print("d. Tipareste cheltuielile sortate după tip.")
    print("Scrie comanda back pentru a te intoarce in meniul principal.")
    print("Scrie comanda exit pentru a iesi din program.")
    print("")

def meniu_filtrare():

    '''
        Functia meniu_filtrare() este un submeniu, realizat doar sub forma unei interfate.
    '''

    print(colorama.Fore.LIGHTYELLOW_EX)
    print("a. Elimina toate cheltuielile de un anumit tip.")
    print("b. Elimina toate cheltuielile mai mici decât o suma data.")
    print("Scrie comanda back pentru a te intoarce in meniul principal.")
    print("Scrie comanda exit pentru a iesi din program.")
    print("")

def run():

    '''
        Functia run() face meniul functional si memoreaza in l, o lista de cheltuieli prin citirea lor de la tastatura.
        Pentru fiecare comanda se deschide un submeniu unde se pot efectua mai multe operatii.
    '''

    l = []
    istoric = []

    while True:
        meniu()
        cmd = input(">>> ")
        print(colorama.Fore.LIGHTYELLOW_EX)

        if cmd == "exit":
            print(colorama.Fore.LIGHTRED_EX)
            print("Multumesc pentru utilizare! Salut!")
            return

        #se efectueaza citirea
        elif cmd == "1":     

            while cmd == "1":

                meniu_citire()
                cmd1 = input(">>> ")

                if cmd1 == "a":

                    try:
                        ui_adauga_cheltuiala(l, istoric, 1)
                    except Exception as ex:
                        print(ex)

                elif cmd1 == "b":

                    l1 = []

                    print("Adauga ziua cheltuielii pe care doresti sa o actualizezi.")
                    z = introducere_ziua()
                    try:
                        validare_ziua(z)
                        print(colorama.Fore.LIGHTYELLOW_EX)
                        print("Adauga tipul al carei cheltuieli din ziua precedenta doresti sa o actualizezi.")
                        t = introducere_tip()
                        try:
                            validare_tip(t)

                            print(colorama.Fore.LIGHTYELLOW_EX)
                            text = input('Adauga una dintre comenzile zi, suma sau tip pentru a actualiza informatia despre cheltuiala aleasa: ')
                            if text == "zi":

                                try:
                                    l1 = modificare_zi(l,istoric,z,0,t,1)
                                    l = l1
                                except Exception as ex:
                                    print(ex)

                            elif text == "suma":

                                try:
                                    l1 = modificare_suma(l,istoric,z,0,t,1)
                                    l = l1
                                except Exception as ex:
                                    print(ex)

                            elif text == "tip":

                                try:
                                    l1 = modificare_tip(l,istoric,z,0,t,1)
                                    l = l1
                                except Exception as ex:
                                    print(ex)
                        except Exception as ex:
                            print(ex)
                    except Exception as ex:
                        print(ex)
                        
                elif cmd1 == "back":

                    cmd = "back"

                elif cmd1 == "exit":

                    print(colorama.Fore.LIGHTRED_EX)
                    print("Multumesc pentru utilizare! Salut!")
                    return

                else:

                    print(colorama.Fore.RED)
                    print("Comanda este invalida! Te rog adauga una dintre comenzile a, back sau exit.")

        #se efectueaza stergerea
        elif cmd == "2":
            while cmd == "2":

                meniu_stergere()
                cmd1 = input(">>> ")

                if cmd1 == "a":

                    l1 = []

                    print("Adauga o zi pentru a sterge toate cheltuielile din acea zi.")
                    z = introducere_ziua()
                    try:
                        validare_ziua(z)
                        l1 = sterge_cheltuiala_dupa_zi(l,istoric,z,1)
                        l = l1
                        print(colorama.Fore.LIGHTGREEN_EX)
                        print("Stergea a fost realizata!")
                    except Exception as ex:
                        print(ex)

                elif cmd1 == "b":

                    l1 = []

                    print("Adauga prima zi din interval.")
                    prima_zi = introducere_ziua()
                    try:
                        validare_ziua(prima_zi)

                        print(colorama.Fore.LIGHTYELLOW_EX+"Adauga ultima zi din interval.")
                        ulitma_zi = introducere_ziua()
                        try:
                            validare_ziua(ulitma_zi)
                            l1 = sterge_cheltuiala_din_interval(l, istoric, prima_zi, ulitma_zi, 1)
                            l = l1
                            print(colorama.Fore.LIGHTGREEN_EX)
                            print("Stergea a fost realizata!")
                        except Exception as ex:
                            print(ex)
                    except Exception as ex:
                        print(ex)
                
                elif cmd1 == "c":

                    l1 = []

                    print("Adauga tipul cheltuielii pe care doresti sa o stergi.")
                    tip = introducere_tip()
                    
                    try:
                        validare_tip(tip)
                        l1 = sterge_cheltuiala_de_un_anumit_tip(l,istoric,tip,1)
                        l = l1
                        print(colorama.Fore.LIGHTGREEN_EX)
                        print("Stergea a fost realizata!")
                    except Exception as ex:
                        print(ex)

                elif cmd1 == "back":

                    cmd = "back"

                elif cmd1 == "exit":

                    print(colorama.Fore.LIGHTRED_EX)
                    print("Multumesc pentru utilizare! Salut!")
                    return

                else:

                    print(colorama.Fore.RED)
                    print("Comanda este invalida! Te rog adauga una dintre comenzile a, back sau exit.")


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
                elif cmd1 == "b":

                    l1 = []

                    print("Adauga ziua pentru gasirea cheltuielilor din zile anterioare.")
                    z = introducere_ziua()
                    try:
                        validare_ziua(z)

                        print(colorama.Fore.LIGHTYELLOW_EX+"Adauga suma pentru gasirea cheltuielilor de suma mai mica.")
                        s = introducere_suma()

                        try:
                            validare_suma(s)
                            l1 = cauta_ziua_si_suma(l, z, s)
                            afisare_cheltuieli(l1)
                        except Exception as ex:
                            print(ex)

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

                    print(colorama.Fore.LIGHTRED_EX)
                    print("Multumesc pentru utilizare! Salut!")
                    return

                else:

                    print(colorama.Fore.RED)
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

                elif cmd1 == "b":

                    zi = -1

                    try:
                        zi = cauta_suma_max(l)
                        print("In ziua "+str(zi)+", se gaseste suma maxima din toate cheltuielile.\n")
                    except Exception as ex:
                        print(ex)
                
                elif cmd1 == "c":

                    l1 = []

                    print("Adauga suma pe care doresti sa o cauti printre cheltuieli.")
                    s = introducere_suma()

                    try:
                        validare_suma(s)
                        l1 = cauta_cheltuieli_cu_o_anumita_suma(l, s)
                        afisare_cheltuieli(l1)
                    except Exception as ex:
                        print(ex)
                
                elif cmd1 == "d":

                    l1 = []

                    print("Adauga tipul cheltuielilor pe care doresti sa le vezi.")
                    tip = introducere_tip()

                    try:
                        validare_tip(tip)
                        l1 = cauta_cheltuieli_de_un_anumit_tip(l, tip)
                        afisare_cheltuieli(l1)
                    except Exception as ex:
                        print(ex)
        
                elif cmd1 == "back":

                    cmd = "back"

                elif cmd1 == "exit":

                    print(colorama.Fore.LIGHTRED_EX)
                    print("Multumesc pentru utilizare! Salut!")
                    return

                else:

                    print(colorama.Fore.RED)
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

                elif cmd1 == "b":
                    
                    l1 = []

                    print("Adauga o suma pentru filtrarea cheltuielilor de suma mai mica decat aceasta.")
                    s = introducere_suma()

                    try:
                        validare_suma(s)
                        l1 = filtrare_dupa_suma(l, s)
                        afisare_cheltuieli(l1)
                    except Exception as ex:
                        print(ex)

                elif cmd1 == "back":

                    cmd = "back"

                elif cmd1 == "exit":

                    print(colorama.Fore.LIGHTRED_EX)
                    print("Multumesc pentru utilizare! Salut!")
                    return

                else:

                    print(colorama.Fore.RED)
                    print("Comanda este invalida! Te rog adauga una dintre comenzile a, back sau exit.")


        #se efecetueaza afisarea
        elif cmd == "6":       
                                                                         
            afisare_cheltuieli(l)

        #se efectueaza functia de undo
        elif cmd == "undo":

            l1 = []
            istoric1 = []

            try:
                l1 = undo(istoric, l)
                l = []
                l = l1
                istoric1 = sterge_ultima_inregistrare_din_istoric(istoric)
                istoric = []
                istoric = istoric1
                print(colorama.Fore.LIGHTGREEN_EX+"Functia undo a functionat.")
                print(colorama.Fore.LIGHTGREEN_EX+"Noua lista este:")
                afisare_cheltuieli(l)
            except Exception as ex:
                print(ex)

        else:

            print(colorama.Fore.RED)
            print("Comanda este invalida! Te rog adauga una dintre comenzile 1, 2, 3, 4 sau exit.")