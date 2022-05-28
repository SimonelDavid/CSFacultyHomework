class Melody:

    def __init__(self, titlu, artist, gen, data):
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__data = data

    def get_titlu(self):
        return self.__titlu

    def get_artist(self):
        return self.__artist

    def get_gen(self):
        return self.__gen

    def get_data(self):
        return self.__data

    def set_titlu(self, titlu):
        self.__titlu = titlu

    def set_artist(self, artist):
        self.__artist = artist

    def set_gen(self, gen):
        self.__gen = gen

    def set_data(self, data):
        self.__data = data

    def __str__(self):
        s = ""
        s += "Titlul: " + str(self.__titlu) + " | "
        s += "Artistul: " + str(self.__artist) + " | "
        s += "Genul: " + str(self.__gen) + " | "
        s += "Data: " + str(self.__data)

        return s
