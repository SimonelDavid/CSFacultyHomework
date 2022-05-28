class Imobil:

    def __init__(self, id_imobil, adresa, pret, tip):
        self.__id_imobil = id_imobil
        self.__adresa = adresa
        self.__pret = pret
        self.__tip = tip

    def get_id_imobil(self):
        return self.__id_imobil

    def get_adresa(self):
        return self.__adresa

    def get_pret(self):
        return self.__pret

    def get_tip(self):
        return self.__tip

    def set_id_imobil(self, id_imobil):
        self.__id_imobil = id_imobil

    def set_adresa(self, adresa):
        self.__adresa = adresa

    def set_pret(self, pret):
        self.__pret = pret

    def set_tip(self, tip):
        self.__tip = tip

    def __str__(self):
        s = ""
        s += "ID-ul imobilului este: " + str(self.__id_imobil) + ", "
        s += "Adresa imobilului este: " + str(self.__adresa) + ", "
        s += "Pretul imobilului este: " + str(self.__pret) + " euro, "
        s += "Tipul imobilului este: " + str(self.__tip)
        return s
