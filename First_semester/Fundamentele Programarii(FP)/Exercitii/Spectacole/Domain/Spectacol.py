class Spectacol:

    def __init__(self, titlu, artist, gen, durata):
        self.__titlu = titlu
        self.__artist = artist
        self.__gen  = gen
        self.__durata = durata

    def get_titlu(self):
        return self.__titlu

    def get_artist(self):
        return self.__artist

    def get_gen(self):
        return self.__gen

    def get_durata(self):
        return self.__durata

    def set_titlu(self, titlu):
        self.__titlu = titlu

    def set_artist(self, artist):
        self.__artist = artist

    def set_gen(self, gen):
        self.__gen = gen

    def set_durata(self, durata):
        self.__durata = durata

    def __str__(self):
        s = ""
        s += "Titlul: " + str(self.__titlu) + " | "
        s += "Artistul: " + str(self.__artist) + " | "
        s += "Genul: " + str(self.__gen) + " | "
        s += "Durata: " + str(self.__durata)
        return s