from stergere import sterge_cheltuiala_dupa_zi_si_tip


def creeaza_istoric(actiune, zi, suma, tip):
    return(actiune, zi, suma, tip)

def adauga_istoric(istoric, inregistrare):

    istoric.append(inregistrare)
    pass

def srv_adauga_istoric(istoric, actiune, zi, suma, tip):

    inregistrare = creeaza_istoric(actiune, zi, suma, tip)
    adauga_istoric(istoric, inregistrare)

def get_actiune(inregistrare):

    return inregistrare[0]

def get_zi(inregistrare):

    return inregistrare[1]

def get_sum(inregistrare):

    return inregistrare[2]

def get_tipul(inregistrare):

    return inregistrare[3]

def undo(istoric, l):

    '''

        0 - citire
        1 - modificare zi
        2 - modificare suma
        3 - modificare tip
        4 - stergere dupa zi
        5 - stergere din interval
        6 - stergere dupa zi si tip
        7 - stergere dupa tip
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
    