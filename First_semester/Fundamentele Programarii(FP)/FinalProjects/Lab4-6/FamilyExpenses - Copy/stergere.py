
'''
    Modulul stergere.py are rolul de a sterge anumite cheltuieli din lista l.
    Functiile acestui modul sunt adesea apelate in modulele meniu.py sau in citire.py.
'''

from validare import get_tip, get_ziua

def sterge_cheltuiala_dupa_zi(l, zi):

    '''
        Functia sterge_cheltuiala_dupa_zi(l,zi) are rolul de a sterge toate cheltuielile din ziua zi.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista nu sunt inregistrate cheltuieli in ziua zi, va fi afisata eroarea "In lista de cheltuieli nu sunt inregistrari in ziua "+str(zi)+".".
    '''

    if len(l) == 0:

        raise Exception("Lista de cheltuieli este goala!\n")

    else:

        l1 = []
        i = 0

        for cheltuiala in l:
            if get_ziua(cheltuiala) != zi:
                l1.append(cheltuiala)
            else:
                i = 1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt inregistrari in ziua "+str(zi)+".")
        else:
            return l1

def sterge_cheltuiala_dupa_zi_si_tip(l, zi, tip):

    '''
        Functia sterge_cheltuiala_dupa_zi_si_tip(l,zi,tip) are rolul de a sterge toate cheltuielile din ziua zi si de tipul tip.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista nu sunt inregistrate cheltuieli in ziua zi si de tipul tip, va fi afisata eroarea "In lista de cheltuieli nu sunt inregistrari in ziua "+str(zi)+"si de tipul "+str(tip)+".".
    '''

    if len(l) == 0:

        raise Exception("Lista de cheltuieli este goala!\n")

    else:

        l1 = []
        i = 0

        for cheltuiala in l:
            if get_ziua(cheltuiala) != zi or get_tip(cheltuiala) != tip:
                l1.append(cheltuiala)
            else:
                i = 1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt inregistrari in ziua "+str(zi)+"si de tipul "+str(tip)+".")
        else:
            return l1

def sterge_cheltuiala_din_interval(l, prima_zi, ultima_zi):

    '''
        Functia sterge_cheltuiala_din_interval(l, prima_zi, ultima_zi) are rolul de a sterge toate cheltuielile din ziua prima_zi pana in ziua ultima_zi.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista nu sunt inregistrate cheltuieli intre ziulele prima_zi si ultima_zi, va fi afisata eroarea "In lista de cheltuieli nu sunt inregistrari in intervalul de zile "+str(prima_zi)+" - "+str(ultima_zi)+".\n".
    '''

    if len(l) == 0:

        raise Exception("Lista de cheltuieli este goala!\n")

    else:

        l1 = []
        i = 0

        for cheltuiala in l:
            if get_ziua(cheltuiala) < prima_zi or get_ziua(cheltuiala) > ultima_zi:
                l1.append(cheltuiala)
            else:
                i = 1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt inregistrari in intervalul de zile "+str(prima_zi)+" - "+str(ultima_zi)+".\n")
        else:
            return l1

def sterge_cheltuiala_de_un_anumit_tip(l, tip):

    '''
        Functia sterge_cheltuiala_de_un_anumit_tip(l, tip) are rolul de a sterge toate cheltuielile de tipul tip.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".

        Daca in lista nu sunt inregistrate cheltuieli de tipul tip, va fi afisata eroarea "In lista de cheltuieli nu sunt inregistrari de tipul "+str(tip)+".\n" .
    '''

    if len(l) == 0:

        raise Exception("Lista de cheltuieli este goala!\n")

    else:

        l1 = []
        i = 0

        for cheltuiala in l:
            if get_tip(cheltuiala) != tip:
                l1.append(cheltuiala)
            else:
                i = 1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt inregistrari de tipul "+str(tip)+".\n")
        else:
            return l1

def sterge_ultima_inregistrare_din_istoric(istoric):

    if len(istoric) == 0:
        raise Exception("Nu exista nici o actiune precedenta efectuata asupra listei.")
    else:
        inregistrare = istoric[len(istoric)-1]
        l1 = []

        for inreg in istoric:
            if inreg != inregistrare:
                l1.append(inreg)
        
        return l1