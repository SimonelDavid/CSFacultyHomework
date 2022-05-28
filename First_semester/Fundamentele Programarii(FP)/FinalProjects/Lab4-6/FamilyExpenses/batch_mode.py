
'''
    Modulul batc_mode.py are rolul de a face modificari asupra listei prin comenzi de tipul batch
'''

from afisare import afisare_cheltuieli
from citire import srv_adauga_cheltuiala
from stergere import sterge_cheltuiala_dupa_zi, sterge_ultima_inregistrare_din_istoric
from undo import undo

import colorama
colorama.init()


def run_batch():

    l = []
    istoric = []

    while True:
        text = []
        l1 = []

        txt = input(">>> ")
        text = txt.split(";")

        for i in text:
            x = i.split()
            
            if x[0] == "adauga":

                try:
                    srv_adauga_cheltuiala(l, istoric, int(x[1]), int(x[2]), x[3], 2)
                    print(colorama.Fore.LIGHTGREEN_EX+"Adaugarea a fost realizata!")
                except Exception as ex:
                    print(ex)

            elif x[0] == "sterge":

                try:
                    l1 = sterge_cheltuiala_dupa_zi(l, istoric, int(x[1]), 1)
                    l = []
                    l = l1
                    print(colorama.Fore.LIGHTGREEN_EX+"Stergerea a fost realizata!")
                except Exception as ex:
                    print(ex)

            elif x[0] == "afiseaza_lista":

                try:
                    print(colorama.Fore.LIGHTGREEN_EX+"Lista de cheltuieli este: ")
                    afisare_cheltuieli(l)
                except Exception as ex:
                    print(ex)
                
            elif x[0] == "undo":

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
        
            elif x[0] == "exit":
                return