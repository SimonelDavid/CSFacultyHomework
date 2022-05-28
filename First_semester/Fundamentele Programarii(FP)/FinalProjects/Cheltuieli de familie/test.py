from afisare import afisare_cheltuieli
from citire import creeaza_cheltuiala
from validare import validare_cheltuiala, get_ziua, get_suma, get_tip
from cautari import cauta_suma, cauta_tip, max
from rapoarte import calculator_suma, suma_totala
from filtrare import comparare, filtrare_dupa_tip

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
    assert(calculator_suma(s,cheltuiala["suma"]) == cheltuiala["suma"])

def test_comparare():

    '''
        Functia test_comparare() are rolul de a testa daca functia comparare din modulul de filtrare respecta specificatia aferenta.
    '''

    cheltuiala = creeaza_cheltuiala(10, 45.3, "intretinere")
    t_adev = "intretinere"
    t_fals = "mancare"

    assert(comparare(cheltuiala["tip"],t_adev) == True)
    assert(comparare(cheltuiala["tip"],t_fals) == False)

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
        assert(str(ex) == "In lista de cheltuieli nu sunt zile in care se regaseste o suma mai mare decat ", suma_locala, ".\n")
    
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
        tip = "divertisment"
        filtrare_dupa_tip(l, tip)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "In lista de cheltuieli nu sunt tipuri diferite fata de tipul", tip, ".\n")
    
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

def run_teste():

    '''
        Functia run_teste() este functia apelata in modulul principal cu scopul de a testa intregul program inainte de a fi folosit de utilizator. 
        In cadrul acestei functii sunt apelate toate functiile de testatre din acest modul.
    '''

    test_creeaza_cheltuiala()
    test_valideaza_cheltuiala()
    test_calculator_suma()
    test_comparare()
    test_cautare_suma()
    test_cautare_tip()
    test_filtrare_tip()
    test_raport_suma()