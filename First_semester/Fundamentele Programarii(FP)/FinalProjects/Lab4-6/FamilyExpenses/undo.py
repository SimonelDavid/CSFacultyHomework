
'''
    Modulul undo.py are rolul de a reface modificarile unei actiuni realizate asupra listei cum ar fi adugarea, stergerea sau modificarea.
'''

from stergere import sterge_cheltuiala_dupa_zi_si_tip


def creeaza_istoric(actiune, zi, suma, tip):

    '''
        Functia creeaza_istoric are rolul de a returna sub forma de tuple istoricul actiunii care contine:

        actiune - numar de tip int care reprezinta id pentru actiune
        zi - numar de tip int cu numarul zilei cuprins intre 1 si 31
        suma - numar de tip float cu suma cheltuita
        tip - numele cheltuielii de tip string
    '''

    return(actiune, zi, suma, tip)

def adauga_istoric(istoric, inregistrare):

    '''
        Functia adauga_istoric(istoric, inregistrare) are rolul de a aduga la lista imutiabila istoric o noua inregistrare.

        istoric - lista de tupleuri
        inregistrare - tuple
    '''

    istoric.append(inregistrare)
    pass

def srv_adauga_istoric(istoric, actiune, zi, suma, tip):

    '''
        Functia srv_adauga_istoric(istoric, actiune, zi, suma, tip) are rolul de a creea o variabila inregistrare unde este stocat tupleul care mai apoi este adaugat in lista de tupleuri istoric cu ajutorul functiei adauga_istoric(istoric, inregistrare).
    '''

    inregistrare = creeaza_istoric(actiune, zi, suma, tip)
    adauga_istoric(istoric, inregistrare)

def get_actiune(inregistrare):

    '''
        Functia get_actiune(inregistrare) are rolul de a returna variabila de pe pozitia 0 din tupleul inregistrare intrucat aceasta reprezinta actiunea pentru istoric.
    '''

    return inregistrare[0]

def get_zi(inregistrare):

    '''
        Functia get_zi(inregistrare) are rolul de a returna variabila de pe pozitia 1 din tupleul inregistrare intrucat aceasta reprezinta ziua cheltuielii.
    '''

    return inregistrare[1]

def get_sum(inregistrare):

    '''
        Functia get_sum(inregistrare) are rolul de a returna variabila de pe pozitia 2 din tupleul inregistrare intrucat aceasta reprezinta suma cheltuielii.
    '''

    return inregistrare[2]

def get_tipul(inregistrare):

    '''
        Functia get_tipul(inregistrare) are rolul de a returna variabila de pe pozitia 3 din tupleul inregistrare intrucat aceasta reprezinta tipul cheltuielii.
    '''

    return inregistrare[3]

def undo(istoric, l):

    '''

        Functia undo(istoric, l) are rolul de a returna o noua lista intermediara in care daca din lista initiala a fost sters un element, in aceasta este adaugat elementul din lista istoric. Diversele refaceri ale listei au loc in functie de actiunea precedenta, astfel in cazul citirii se sterge, iar in cazul stergerii se adauga cheltuiala stearsa si memorata in istoric. Pentru fiecare actiune exista un id reprezentat de urmatoarele numere:

        0 - citire
        1 - modificare zi
        2 - modificare suma
        3 - modificare tip
        4 - stergere dupa zi
        5 - stergere din interval
        6 - stergere dupa tip
    '''

    if len(istoric) == 0:
        raise Exception("Nu exista nici o actiune precedenta efectuata asupra listei.")
    else:
        i = len(istoric) - 1
        inregistrare = istoric[i]
        l1 = []
        i = i-1

        if get_actiune(inregistrare) == 0:
            l1 = sterge_cheltuiala_dupa_zi_si_tip(l, get_zi(inregistrare), get_tipul(inregistrare))
            
            return l1
        
        elif get_actiune(inregistrare) == 1:
            while i >= 0:
                inreg = istoric[i]

                from citire import modificare_zi

                if get_actiune(inreg) == 0 and get_sum(inreg) == get_sum(inregistrare) and get_tipul(inreg) == get_tipul(inregistrare):

                    l1 = modificare_zi(l,0,get_zi(inregistrare),get_zi(inreg),get_tipul(inregistrare), 0)
                    
                    return l1

                elif get_actiune(inreg) == 1 and get_sum(inreg) == get_sum(inregistrare) and get_tipul(inreg) == get_tipul(inregistrare):

                    l1 = modificare_zi(l,0,get_zi(inregistrare),get_zi(inreg),get_tipul(inregistrare), 0)

                    return l1

                elif get_actiune(inreg) == 2 and get_sum(inreg) == get_sum(inregistrare) and get_tipul(inreg) == get_tipul(inregistrare):

                    l1 = modificare_zi(l,0,get_zi(inregistrare),get_zi(inreg),get_tipul(inregistrare), 0)

                    return l1
                elif get_actiune(inreg) == 3 and get_sum(inreg) == get_sum(inregistrare) and get_tipul(inreg) == get_tipul(inregistrare):

                    l1 = modificare_zi(l,0,get_zi(inregistrare),get_zi(inreg),get_tipul(inregistrare), 0)

                    return l1
                
                i = i-1
        
        elif get_actiune(inregistrare) == 2:
            while i >= 0:
                inreg = istoric[i]
                from citire import modificare_suma

                if get_actiune(inreg) == 0 and get_zi(inreg) == get_zi(inregistrare) and get_tipul(inreg) == get_tipul(inregistrare):

                    l1 = modificare_suma(l,0,get_zi(inregistrare),get_sum(inreg),get_tipul(inregistrare), 0)
            
                    return l1
                
                if get_actiune(inreg) == 1 and get_zi(inreg) == get_zi(inregistrare) and get_tipul(inreg) == get_tipul(inregistrare):

                    l1 = modificare_suma(l,0,get_zi(inregistrare),get_sum(inreg),get_tipul(inregistrare), 0)
            
                    return l1
                
                if get_actiune(inreg) == 2 and get_zi(inreg) == get_zi(inregistrare) and get_tipul(inreg) == get_tipul(inregistrare):

                    l1 = modificare_suma(l,0,get_zi(inregistrare),get_sum(inreg),get_tipul(inregistrare), 0)
            
                    return l1
                
                if get_actiune(inreg) == 3 and get_zi(inreg) == get_zi(inregistrare) and get_tipul(inreg) == get_tipul(inregistrare):

                    l1 = modificare_suma(l,0,get_zi(inregistrare),get_sum(inreg),get_tipul(inregistrare), 0)
            
                    return l1
                
                i = i-1
        
        elif get_actiune(inregistrare) == 3:
            while i >= 0:
                inreg = istoric[i]
                from citire import modificare_tip

                if get_actiune(inreg) == 0 and get_zi(inreg) == get_zi(inregistrare) and get_sum(inreg) == get_sum(inregistrare):

                    l1 = modificare_tip(l,0,get_zi(inregistrare),get_tipul(inreg),get_tipul(inregistrare), 0)
            
                    return l1

                if get_actiune(inreg) == 1 and get_zi(inreg) == get_zi(inregistrare) and get_sum(inreg) == get_sum(inregistrare):

                    l1 = modificare_tip(l,0,get_zi(inregistrare),get_tipul(inreg),get_tipul(inregistrare), 0)
            
                    return l1
                
                if get_actiune(inreg) == 2 and get_zi(inreg) == get_zi(inregistrare) and get_sum(inreg) == get_sum(inregistrare):

                    l1 = modificare_tip(l,0,get_zi(inregistrare),get_tipul(inreg),get_tipul(inregistrare), 0)
            
                    return l1
                
                if get_actiune(inreg) == 3 and get_zi(inreg) == get_zi(inregistrare) and get_sum(inreg) == get_sum(inregistrare):

                    l1 = modificare_tip(l,0,get_zi(inregistrare),get_tipul(inreg),get_tipul(inregistrare), 0)
            
                    return l1
                
                i = i-1
            
        elif get_actiune(inregistrare) == 4:
            from citire import srv_adauga_cheltuiala
            l1 = l
            srv_adauga_cheltuiala(l1,0,get_zi(inregistrare), get_sum(inregistrare), get_tipul(inregistrare),0)

            return l1

        elif get_actiune(inregistrare) == 5:
            from citire import srv_adauga_cheltuiala
            l1 = l
            srv_adauga_cheltuiala(l1,0,get_zi(inregistrare), get_sum(inregistrare), get_tipul(inregistrare),0)

            return l1

        elif get_actiune(inregistrare) == 6:
            from citire import srv_adauga_cheltuiala
            l1 = l
            srv_adauga_cheltuiala(l1,0,get_zi(inregistrare), get_sum(inregistrare), get_tipul(inregistrare),0)

            return l1