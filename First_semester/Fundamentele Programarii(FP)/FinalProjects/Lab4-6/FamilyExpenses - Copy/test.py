from afisare import afisare_cheltuieli
from citire import creeaza_cheltuiala
from stergere import sterge_cheltuiala_de_un_anumit_tip, sterge_cheltuiala_din_interval, sterge_cheltuiala_dupa_zi, sterge_cheltuiala_dupa_zi_si_tip
from validare import validare_cheltuiala, get_ziua, get_suma, get_tip
from cautari import cauta_suma, cauta_tip, cauta_ziua_si_suma, max
from rapoarte import calculator_suma, cauta_cheltuieli_cu_o_anumita_suma, cauta_cheltuieli_de_un_anumit_tip, cauta_suma_max, suma_totala
from filtrare import comparare, filtrare_dupa_suma, filtrare_dupa_tip

import colorama
colorama.init()

def test_valideaza_cheltuiala():

    '''
        Functia test_valideaza_cheltuiala() are rolul de a testa modulul de validare.
    '''

    cheltuiala = creeaza_cheltuiala(3, 45.7, "mancare")
    validare_cheltuiala(cheltuiala)

    ziua_invalida = creeaza_cheltuiala(65, 34, "divertiment")
    try:
        validare_cheltuiala(ziua_invalida)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Indexul zilei invalid. Introduceti o zi valida dintr-o luna!\n")
    
    suma_invalida = creeaza_cheltuiala(23, -23, "mancare")
    try:
        validare_cheltuiala(suma_invalida)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Suma nu poate fi una negativa! Trebuie sa introduceti suma cu numar pozitiv!\n")

    tip_invalid = creeaza_cheltuiala(23, 23, "")
    try:
        validare_cheltuiala(tip_invalid)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Tip de cheltuiala invalid!\nAtentie! Nu lasati campul gol!\n")
    
    zi_suma_invalide = creeaza_cheltuiala(65, -23, "intretinere")
    try:
        validare_cheltuiala(zi_suma_invalide)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Indexul zilei invalid. Introduceti o zi valida dintr-o luna!\nSuma nu poate fi una negativa! Trebuie sa introduceti suma cu numar pozitiv!\n")
    
    zi_tip_invalide = creeaza_cheltuiala(65, 45.6, "")
    try:
        validare_cheltuiala(zi_tip_invalide)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Indexul zilei invalid. Introduceti o zi valida dintr-o luna!\nTip de cheltuiala invalid!\nAtentie! Nu lasati campul gol!\n")

    suma_tip_invalide = creeaza_cheltuiala(23, -23, "")
    try:
        validare_cheltuiala(suma_tip_invalide)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Suma nu poate fi una negativa! Trebuie sa introduceti suma cu numar pozitiv!\nTip de cheltuiala invalid!\nAtentie! Nu lasati campul gol!\n")
    
    cheltuiala_invalida = creeaza_cheltuiala(45, -12, "")
    try:
        validare_cheltuiala(cheltuiala_invalida)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Indexul zilei invalid. Introduceti o zi valida dintr-o luna!\nSuma nu poate fi una negativa! Trebuie sa introduceti suma cu numar pozitiv!\nTip de cheltuiala invalid!\nAtentie! Nu lasati campul gol!\n")

def test_creeaza_cheltuiala():

    '''
        Functia test_creeaza_cheltuiala() are rolul de a testa daca functiia de creeare a unei cheltuieli din modulul de citire functioneaza.
    '''

    zi = 12
    suma = 76.9
    tip = "intretinere"
    cheltuiala = creeaza_cheltuiala(zi,suma,tip)
    assert(get_ziua(cheltuiala) == zi)
    assert(get_suma(cheltuiala) == suma)
    assert(get_tip(cheltuiala) == tip)

def test_calculator_suma():

    '''
        Functia test_calculator_suma() are roulul de a testa daca o functia de calculare a sumei din modulul de rapoarte returneaza valoarea dorita.
    '''

    cheltuiala = creeaza_cheltuiala(3, 32, "telefonie")
    s = 0
    assert(calculator_suma(s,cheltuiala[1]) == cheltuiala[1])

def test_comparare():

    '''
        Functia test_comparare() are rolul de a testa daca functia comparare din modulul de filtrare respecta specificatia aferenta.
    '''

    cheltuiala = creeaza_cheltuiala(10, 45.3, "intretinere")
    t_adev = "intretinere"
    t_fals = "mancare"

    assert(comparare(cheltuiala[2],t_adev) == True)
    assert(comparare(cheltuiala[2],t_fals) == False)

def test_cautare_suma():

    '''
        Functia test_cautare_suma() are rolul de verifica daca functia de cautare a cheltuielilor cu o suma mai mare decat cea introdusa de utilizator este gasita.
    '''

    cheltuiala = creeaza_cheltuiala(10, 45.6, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(11, 42, "mancare")
    cheltuiala2 = creeaza_cheltuiala(12, 35, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []

    l1.append(cheltuiala)
    assert(cauta_suma(l,44) == l1)

    l1.append(cheltuiala1)
    assert(cauta_suma(l,40) == l1)

    l1.append(cheltuiala2)
    assert(cauta_suma(l,30) == l1)

    try:
        suma_locala = 48
        cauta_suma(l, suma_locala)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt zile in care se regaseste o suma mai mare decat "+str(suma_locala)+".\n")
    
    l1 = []
    try:
        suma_locala = 48
        cauta_suma(l1, suma_locala)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_cautare_tip():

    '''
        Functia test_cautare_tip() are rolul de verifica daca functia de cautare a cheltuielilor va returna o lista de cheltuieli de tipul introdus de utilizator.
    '''

    cheltuiala = creeaza_cheltuiala(10, 45.6, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(11, 42, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)

    l1 = []

    l1.append(cheltuiala)
    assert(cauta_tip(l,"intretinere") == l1)

    l1 = []
    l1.append(cheltuiala1)
    assert(cauta_tip(l,"mancare") == l1)

    try:
        tip_local = "divertisment"
        cauta_tip(l, tip_local)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt cheltuieli de tipul ",tip_local,".\n")
    
    l1 = []
    try:
        suma_locala = 48
        cauta_tip(l1, suma_locala)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_filtrare_tip():

    '''
        Functia test_filtrare_tip() are rolul de verifica daca functia de filtrare a cheltuielilor dupa tip va returna o lista de cheltuieli cu tipul diferit de cel introdus de utilizator.
    '''

    cheltuiala = creeaza_cheltuiala(10, 45.6, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(11, 42, "mancare")
    cheltuiala2 = creeaza_cheltuiala(12, 37.3, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []

    l1.append(cheltuiala1)
    l1.append(cheltuiala2)
    assert(filtrare_dupa_tip(l,"intretinere") == l1)

    l1 = []
    l1.append(cheltuiala)
    assert(filtrare_dupa_tip(l,"mancare") == l1)

    try:
        tip = "intretinere"
        filtrare_dupa_tip(l1, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt tipuri diferite fata de tipul "+str(tip)+".\n")
    
    l1 = []
    try:
        tip = "mancare"
        filtrare_dupa_tip(l1, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_filtrare_dupa_suma():

    '''
        Functia test_filtrare_dupa_suma() are rolul de verifica daca functia de filtrare a cheltuielilor dupa suma va returna o lista de cheltuieli cu suma mai mare decat cea introdusa de utilizator.
    '''

    cheltuiala = creeaza_cheltuiala(10, 45.6, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(11, 40, "mancare")
    cheltuiala2 = creeaza_cheltuiala(12, 37, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []

    l1.append(cheltuiala)
    assert(filtrare_dupa_suma(l,45) == l1)

    l1.append(cheltuiala1)
    assert(filtrare_dupa_suma(l,39.6) == l1)

    l1.append(cheltuiala2)
    assert(filtrare_dupa_suma(l,34.2) == l1)

    try:
        s = 55
        filtrare_dupa_suma(l, s)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt cheltuieli cu suma mai mare decat "+str(s)+".\n")
    
    l1 = []
    try:
        tip = "mancare"
        filtrare_dupa_tip(l1, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_raport_suma():

    '''
        Functia test_raport_suma() are rolul de verifica daca functia de cautare a sumei maxime a cheltuielilor de un anumit tip returna suma corecta.
    '''

    cheltuiala = creeaza_cheltuiala(10, 45.6, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(11, 42, "mancare")
    cheltuiala2 = creeaza_cheltuiala(12, 37.3, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    assert(suma_totala(l,"intretinere") == 45.6)
    assert(suma_totala(l,"mancare") == 79.3)

    try:
        tip = "divertisment"
        suma_totala(l, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Nu s-au gasit cheltuieli de tipul ",tip,"\n")
    
    l = []
    try:
        tip = "mancare"
        suma_totala(l, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_cauta_cheltuieli_cu_o_anumita_suma():
    
    '''
        Functia test_cauta_cheltuieli_cu_o_anumita_suma() are rolul de a verifica daca functia de cautare a cheltuielilor cu o suma egala cu una introdusa de utilizator, returneaza o lista intermediara noua cu aceasta proprietate.
    '''

    cheltuiala = creeaza_cheltuiala(14, 35.7, "mancare")
    cheltuiala1 = creeaza_cheltuiala(9, 50, "divertisment")
    cheltuiala2 = creeaza_cheltuiala(24, 50, "gaz")

    l= []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []
    l1.append(cheltuiala)
    assert(cauta_cheltuieli_cu_o_anumita_suma(l, 35.7) == l1)

    l1 = []
    l1.append(cheltuiala1)
    l1.append(cheltuiala2)
    assert(cauta_cheltuieli_cu_o_anumita_suma(l, 50) == l1)

    try:
        suma = 30
        cauta_cheltuieli_cu_o_anumita_suma(l, suma)
        assert(False)
    except Exception as ex:
        assert(str(ex) == colorama.Fore.RED+"In lista de cheltuieli nu sunt inregistrari care sa aiba suma "+str(suma)+".\n")
    
    l = []
    try:
        suma = 20
        cauta_cheltuieli_cu_o_anumita_suma(l, suma)
        assert(False)
    except Exception as ex:
        assert(str(ex) == colorama.Fore.RED+"Lista de cheltuieli este goala!\n")

def test_cauta_cheltuieli_de_un_anumit_tip():
    
    '''
        Functia test_cauta_cheltuieli_de_un_anumit_tip() are rolul de a verifica daca functia de cautare a cheltuielilor de acelasi tip introdus de utilizator, returneaza o lista intermediara noua cu aceasta proprietate.
    '''

    cheltuiala = creeaza_cheltuiala(14, 35.7, "mancare")
    cheltuiala1 = creeaza_cheltuiala(9, 50, "divertisment")
    cheltuiala2 = creeaza_cheltuiala(24, 50, "gaz")

    l= []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []
    l1.append(cheltuiala)
    assert(cauta_cheltuieli_de_un_anumit_tip(l, "mancare") == l1)

    l1 = []
    l1.append(cheltuiala1)
    assert(cauta_cheltuieli_de_un_anumit_tip(l, "divertisment") == l1)

    l1 = []
    l1.append(cheltuiala2)
    assert(cauta_cheltuieli_de_un_anumit_tip(l, "gaz") == l1)

    try:
        tip = "telefonie"
        cauta_cheltuieli_de_un_anumit_tip(l, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == colorama.Fore.RED+"In lista de cheltuieli nu sunt inregistrari de tipul "+str(tip)+".\n")
    
    l = []
    try:
        tip = "gaz"
        cauta_cheltuieli_de_un_anumit_tip(l, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == colorama.Fore.RED+"Lista de cheltuieli este goala!\n")

def test_cauta_ziua_si_suma():
    '''
        Functia test_cauta_ziua_si_suma() are rolul de verifica daca functia de cautare a cheltuielilor din zile precedente decat una introdusa de utilizator sau cu sume mai mici decat una introdusa de utilizator returneaza o astfel de lista.
    '''

    cheltuiala = creeaza_cheltuiala(10, 42, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(12, 45.7, "mancare")
    cheltuiala2 = creeaza_cheltuiala(21, 57.3, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []
    l1.append(cheltuiala)

    assert(cauta_ziua_si_suma(l,11,50) == l1)
    assert(cauta_ziua_si_suma(l,14,44) == l1)

    l1.append(cheltuiala1)

    assert(cauta_ziua_si_suma(l,14,46) == l1)
    assert(cauta_ziua_si_suma(l,24,50) == l1)

    l1.append(cheltuiala2)

    assert(cauta_ziua_si_suma(l,22,60) == l1)

    try:
        zi = 9
        suma = 40
        cauta_ziua_si_suma(l,zi,suma)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt zile precedente zilei "+str(zi)+" si nici sume ale cheltuielilor mai mici decat "+str(suma)+".\n")
    
    try:
        zi = 14
        suma = 40
        cauta_ziua_si_suma(l,zi,suma)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli sunt zile precedente zilei "+str(zi)+" dar nu sunt sume ale cheltuielilor mai mici decat "+str(suma)+".\n")

    try:
        zi = 9
        suma = 50
        cauta_ziua_si_suma(l,zi,suma)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt zile precedente zilei "+str(zi)+" dar sunt sume ale cheltuielilor mai mici decat "+str(suma)+".\n")
    
    l = []
    try:
        zi = 9
        suma = 40
        cauta_ziua_si_suma(l,zi,suma)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_cauta_suma_max():

    '''
        Functia test_cauta_suma_max() are rolul de verifica daca functia de cautare printe zilele inregistrate in cheltuieli a zilei in care suma cheltuita este una maxima.
    '''

    cheltuiala = creeaza_cheltuiala(10, 42, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(12, 45.7, "mancare")
    cheltuiala2 = creeaza_cheltuiala(10, 57.3, "mancare")

    l = []
    l.append(cheltuiala)
    assert(cauta_suma_max(l) == 10)

    l.append(cheltuiala1)
    assert(cauta_suma_max(l) == 12)

    l.append(cheltuiala2)
    assert(cauta_suma_max(l) == 10)

    l = []
    try:
        zi = 9
        suma = 40
        cauta_ziua_si_suma(l,zi,suma)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_stergere_cheltuieli_dupa_zi():

    '''
        Functia test_stergere_cheltuieli_dupa_zi() are rolul de a testa daca toate cheltuielile din anumite zile date sunt sterse.
    '''

    cheltuiala = creeaza_cheltuiala(10, 42, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(12, 45.7, "mancare")
    cheltuiala2 = creeaza_cheltuiala(10, 57.3, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []
    l1.append(cheltuiala)
    l1.append(cheltuiala2)

    assert(sterge_cheltuiala_dupa_zi(l, 12) == l1)

    l1 = []
    l1.append(cheltuiala1)
    assert(sterge_cheltuiala_dupa_zi(l, 10) == l1)

    try:
        zi = 9
        sterge_cheltuiala_dupa_zi(l,zi)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt inregistrari in ziua "+str(zi)+".")
    
    l = []
    try:
        zi = 15
        sterge_cheltuiala_dupa_zi(l,zi)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_stergere_cheltuieli_dupa_zi_si_tip():

    '''
        Functia test_stergere_cheltuieli_dupa_zi_si_tip() are rolul de a testa daca toate cheltuielile din anumite zile date si de anumite tipuri date sunt sterse.
    '''

    cheltuiala = creeaza_cheltuiala(10, 42, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(12, 45.7, "mancare")
    cheltuiala2 = creeaza_cheltuiala(10, 57.3, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []
    l1.append(cheltuiala)
    l1.append(cheltuiala2)
    assert(sterge_cheltuiala_dupa_zi_si_tip(l, 12, "mancare") == l1)

    l1 = []
    l1.append(cheltuiala)
    l1.append(cheltuiala1)
    assert(sterge_cheltuiala_dupa_zi_si_tip(l, 10, "mancare") == l1)

    l1 = []
    l1.append(cheltuiala1)
    l1.append(cheltuiala2)
    assert(sterge_cheltuiala_dupa_zi_si_tip(l, 10, "intretinere") == l1)

    try:
        zi = 9
        tip = "gaz"
        sterge_cheltuiala_dupa_zi_si_tip(l,zi,tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt inregistrari in ziua "+str(zi)+"si de tipul "+str(tip)+".")
    
    l = []
    try:
        zi = 15
        sterge_cheltuiala_dupa_zi(l,zi)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_stergere_cheltuieli_din_interval():

    '''
        Functia test_stergere_cheltuieli_din_interval() are rolul de a testa daca toate cheltuielile dintr-un anumit interval de zile sunt sterse.
    '''

    cheltuiala = creeaza_cheltuiala(5, 42, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(12, 45.7, "mancare")
    cheltuiala2 = creeaza_cheltuiala(20, 57.3, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []
    l1.append(cheltuiala)
    assert(sterge_cheltuiala_din_interval(l, 10, 20) == l1)

    l1 = []
    l1.append(cheltuiala)
    l1.append(cheltuiala1)
    assert(sterge_cheltuiala_din_interval(l, 13, 23) == l1)

    l1 = []
    l1.append(cheltuiala1)
    l1.append(cheltuiala2)
    assert(sterge_cheltuiala_din_interval(l, 5, 10) == l1)

    l1 = []
    l1.append(cheltuiala)
    l1.append(cheltuiala2)
    assert(sterge_cheltuiala_din_interval(l, 10, 19) == l1)

    try:
        prima_zi = 25
        ultima_zi = 29
        sterge_cheltuiala_din_interval(l, prima_zi, ultima_zi)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt inregistrari in intervalul de zile "+str(prima_zi)+" - "+str(ultima_zi)+".\n")
    
    l = []
    try:
        prima_zi = 10
        ultima_zi = 20
        sterge_cheltuiala_din_interval(l, prima_zi, ultima_zi)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def test_stergere_cheltuieli_de_un_anumit_tip():

    '''
        Functia test_stergere_cheltuieli_de_un_anumit_tip() are rolul de a testa daca toate cheltuielile de un anumit tip sunt sterse.
    '''

    cheltuiala = creeaza_cheltuiala(5, 42, "intretinere")
    cheltuiala1 = creeaza_cheltuiala(12, 45.7, "mancare")
    cheltuiala2 = creeaza_cheltuiala(20, 57.3, "mancare")

    l = []
    l.append(cheltuiala)
    l.append(cheltuiala1)
    l.append(cheltuiala2)

    l1 = []
    l1.append(cheltuiala)
    assert(sterge_cheltuiala_de_un_anumit_tip(l, "mancare") == l1)

    l1 = []
    l1.append(cheltuiala1)
    l1.append(cheltuiala2)
    assert(sterge_cheltuiala_de_un_anumit_tip(l, "intretinere") == l1)

    try:
        tip = "gaz"
        sterge_cheltuiala_de_un_anumit_tip(l, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt inregistrari de tipul "+str(tip)+".\n")
    
    l = []
    try:
        tip = "telefonie"
        sterge_cheltuiala_de_un_anumit_tip(l, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Lista de cheltuieli este goala!\n")

def run_teste():

    '''
        Functia run_teste() este functia apelata in modulul principal cu scopul de a testa intregul program inainte de a fi folosit de utilizator. 
        In cadrul acestei functii sunt apelate toate functiile de testatre din acest modul.
    '''

    test_creeaza_cheltuiala()
    test_valideaza_cheltuiala()

    test_stergere_cheltuieli_dupa_zi()
    test_stergere_cheltuieli_dupa_zi_si_tip()
    test_stergere_cheltuieli_din_interval()
    test_stergere_cheltuieli_de_un_anumit_tip()

    test_calculator_suma()
    test_comparare()

    test_cautare_suma()
    test_cauta_ziua_si_suma()
    test_cautare_tip()

    test_cauta_suma_max()
    test_raport_suma()
    test_cauta_cheltuieli_cu_o_anumita_suma()
    test_cauta_cheltuieli_de_un_anumit_tip()
    
    test_filtrare_tip()
    test_filtrare_dupa_suma()