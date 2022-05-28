'''
    Functia rapoarte.py are rolul de a realiza un set de rapoarte pentru lista de cheltuieli introdusa de utilizator.
'''

def calculator_suma(suma, s):

    '''
        Functia calculator_suma(suma, s) are rolul de a returna suma dintre variabilele de timp float suma si s transmise ca parametru.
    '''

    suma_noua = suma + s

    return suma_noua
    

def suma_totala(l, tip):

    '''
        Functia suma_totala(l, tip) are rolul de a afisa utilizatorului suma totala a cheltuilelilor din lista l de tipul tip.
    '''

    if len(l) == 0:
        raise Exception("Lista de cheltuieli este goala!\n")
    else:
        s = 0
        for cheltuiala in l:
            if cheltuiala["tip"] == tip:
                s = calculator_suma(s,cheltuiala["suma"])
        if s == 0:
            raise Exception("Nu s-au gasit cheltuieli de tipul ",tip,"\n")
        else:
            return s