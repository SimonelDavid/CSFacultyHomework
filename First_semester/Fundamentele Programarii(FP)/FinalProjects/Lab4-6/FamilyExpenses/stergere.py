
'''
    Modulul stergere.py are rolul de a sterge anumite cheltuieli din lista l.
    Functiile acestui modul sunt adesea apelate in modulele meniu.py sau in citire.py.
'''

from validare import get_suma, get_tip, get_ziua

def sterge_cheltuiala_dupa_zi(l, istoric, zi, mod):

    '''
        Functia sterge_cheltuiala_dupa_zi(l, istoric, zi, mod) are rolul de a sterge toate cheltuielile din ziua zi. Variabila mod are rolul de adetermina daca sa se faca sau nu adaugare in lista istoric, cheltuieli pentru a fi memorate in arhiva. Modul 0 este pentru apelarea functiei cand nu este necesara adaugarea in arhiva a cheltuielii, modul 1 este pentru cand se citeste o cheltuiala noua, iar modul 2 este pentru functiile de test ale modulului undo.py.

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
                if mod == 1 or mod == 2:
                    from undo import srv_adauga_istoric
                    srv_adauga_istoric(istoric, 4, zi, get_suma(cheltuiala), get_tip(cheltuiala))
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

def sterge_cheltuiala_din_interval(l, istoric, prima_zi, ultima_zi, mod):

    '''
        Functia sterge_cheltuiala_din_interval(l, istoric, prima_zi, ultima_zi, mod) are rolul de a sterge toate cheltuielile din ziua prima_zi pana in ziua ultima_zi. Variabila mod are rolul de adetermina daca sa se faca sau nu adaugare in lista istoric, cheltuieli pentru a fi memorate in arhiva. Modul 0 este pentru apelarea functiei cand nu este necesara adaugarea in arhiva a cheltuielii, modul 1 este pentru cand se citeste o cheltuiala noua, iar modul 2 este pentru functiile de test ale modulului undo.py.

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
                if mod == 1 or mod  == 2:
                    from undo import srv_adauga_istoric
                    srv_adauga_istoric(istoric, 5, get_ziua(cheltuiala), get_suma(cheltuiala), get_tip(cheltuiala))
                i = 1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt inregistrari in intervalul de zile "+str(prima_zi)+" - "+str(ultima_zi)+".\n")
        else:
            return l1

def sterge_cheltuiala_de_un_anumit_tip(l, istoric, tip, mod):

    '''
        Functia sterge_cheltuiala_de_un_anumit_tip(l,istoric, tip, mod) are rolul de a sterge toate cheltuielile de tipul tip. Variabila mod are rolul de adetermina daca sa se faca sau nu adaugare in lista istoric, cheltuieli pentru a fi memorate in arhiva. Modul 0 este pentru apelarea functiei cand nu este necesara adaugarea in arhiva a cheltuielii, modul 1 este pentru cand se citeste o cheltuiala noua, iar modul 2 este pentru functiile de test ale modulului undo.py.

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
                if mod == 1 or mod == 2:
                    from undo import srv_adauga_istoric
                    srv_adauga_istoric(istoric, 6, get_ziua(cheltuiala), get_suma(cheltuiala), get_tip(cheltuiala))
                i = 1
        if i == 0:
            raise Exception("In lista de cheltuieli nu sunt inregistrari de tipul "+str(tip)+".\n")
        else:
            return l1

def sterge_ultima_inregistrare_din_istoric(istoric):

    '''
       Functia sterge_ultima_inregistrare_din_istoric(istoric) are rolul de a sterge toate inregistrarile de tip istoric al cheltuielii.

        Daca in lista nu exista nici o inregistrare, compararile intre cheltuieli nu mai au loc ci se afiseaza mesajul "Lista de cheltuieli este goala!".
    '''

    if len(istoric) == 0:
        raise Exception("Nu exista nici o actiune precedenta efectuata asupra listei.")
    else:
        inregistrare = istoric[len(istoric)-1]
        l1 = []

        for inreg in istoric:
            if inreg != inregistrare:
                l1.append(inreg)
        
        return l1