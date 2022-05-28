class Curs:

    def __init__(self, id_curs, limba, nivel, pret):
        self.__id_curs = id_curs
        self.__limba = limba
        self.__nivel = nivel
        self.__pret = pret

    def get_id_curs(self):
        return self.__id_curs

    def get_limba(self):
        return self.__limba

    def get_nivel(self):
        return self.__nivel

    def get_pret(self):
        return self.__pret

    def set_id_curs(self, id_curs):
        self.__id_curs = id_curs

    def set_limba(self, limba):
        self.__limba = limba

    def set_nivel(self, nivel):
        self.__nivel = nivel

    def set_pret(self, pret):
        self.__pret = pret

    def __eq__(self, other):
        return self.__id_curs == other.get_id_curs() and self.__limba == other.get_limba() and self.__nivel == other.get_nivel() and self.__pret == other.get_pret()

    def __str__(self):
        s = ""
        s += "ID-ul cursului este: "+str(self.__id_curs)+", "
        s += "Limba cursului este: "+str(self.__limba)+", "
        s += "Nivelul cursului este: "+str(self.__nivel)+", "
        s += "Pretul cursului este: "+str(self.__pret)
        return s


class Inscriere:

    def __init__(self, curs, numar_ore):
        self.__curs = curs
        self.__nr_ore = numar_ore

    def get_total(self):
        return self.__nr_ore * self.__curs.get_pret()

    def __str__(self):
        s = ""
        s += "ID-ul cursului este: "+str(self.__curs.get_id_curs())+", "
        s += "Limba cursului este: "+str(self.__curs.get_limba())+", "
        s += "Nivelul cursului este: "+str(self.__curs.get_nivel())+", "
        s += "Pretul total este: "+str(self.get_total())
        return s
