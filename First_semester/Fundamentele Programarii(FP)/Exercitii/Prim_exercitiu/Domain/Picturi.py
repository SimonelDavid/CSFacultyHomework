class Picturi:

    def __init__(self, id_picturi, nume, autor, an):
        self.__id = id_picturi
        self.__nume = nume
        self.__autor = autor
        self.__an = an

    def get_id_pictura(self):
        return self.__id

    def get_nume_pictura(self):
        return self.__nume

    def get_autor(self):
        return self.__autor

    def get_an(self):
        return self.__an

    def set_id_pictura(self, id_picturi):
        self.__id = id_picturi

    def set_nume_pictura(self, nume):
        self.__nume = nume

    def set_autor(self, autor):
        self.__autor = autor

    def set_an(self, an):
        self.__an = an

    def __eq__(self, other):
        return self.__id == other.get_id_pictura() and self.__nume == other.get_nume_pictura() and self.__autor == other.get_autor() and self.__an == other.get_an()

    def __str__(self):
        s = ""
        s += "ID-ul picturii este: "+str(self.__id)+","
        s += "Numele picturii este: "+str(self.__nume)+","
        s += "Numele autorului este: "+str(self.__autor)+","
        s += "Anul realizarii picturii este: "+str(self.__an)

        return s
