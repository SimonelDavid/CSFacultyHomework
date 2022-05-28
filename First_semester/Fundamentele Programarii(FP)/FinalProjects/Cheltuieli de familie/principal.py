'''
    Modulul principal.py are rolul de program principal unde aplicatia poate fi rulata ca un intreg.
'''

from meniu import run
from test import run_teste

def main():
    
    '''
        Functia main este folosita in scopul rularii testelor, iar daca acestea sunt trecute cu succes, folosirea aplicatiei in sine.
    '''

    run_teste()
    run()

main()