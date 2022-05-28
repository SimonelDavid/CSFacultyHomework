'''
    Modulul principal.py are rolul de program principal unde aplicatia poate fi rulata ca un intreg.
'''

from batch_mode import run_batch
from meniu import run
from test import run_teste

def main():
    
    '''
        Functia main este folosita in scopul rularii testelor, iar daca acestea sunt trecute cu succes, folosirea aplicatiei in sine.
    '''

    run_teste()
    run()
    #run_batch()

main()

#adauga 14 56 gaz;adauga 16 47 mancare;adauga 20 48 telefonie;afiseaza_lista;sterge 14 gaz;afiseaza_lista;sterge 16 mancare;afiseaza_lista;sterge 20 telefonie;afiseaza_lista
#adauga 35 56 gaz;adauga 16 -1 mancare;adauga 20 48 telefonie;afiseaza_lista;sterge 20 telefonie;afiseaza_lista
#adauga 14 56 gaz;adauga 16 47 mancare;adauga 20 48 telefonie;afiseaza_lista;sterge 14 gaz;afiseaza_lista;sterge 16 mancare;afiseaza_lista;sterge 20 telefonie;afiseaza_lista;undo;undo;undo;undo