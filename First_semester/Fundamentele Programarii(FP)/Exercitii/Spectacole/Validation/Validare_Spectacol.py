class SpectacolValidation:

    def validare_titlu(self, titlu):
        if titlu == "":
            raise Exception("Nu lasati campul pentru titlu gol.\n")

    def validare_artist(self, artist):
        if artist == "":
            raise Exception("Nu lasati campul pentru artist gol.\n")

    def validare_durata(self, durata):
        if durata <= 0:
            raise Exception("Durata trebuie sa fie numar intreg pozitiv!\n")

    def validare_gen(self, gen):
        if gen != "Altele" and gen != "Comedie" and gen != "Balet" and gen != "Concert":
            raise Exception("Genul trebuie sa fie Comedie, Balet, Concert sau Altele!\n")

    def validare_spectacol(self, spectacol):
        self.validare_titlu(str(spectacol.get_titlu()))
        self.validare_artist(str(spectacol.get_artist()))
        self.validare_gen(str(spectacol.get_gen()))
        self.validare_durata(int(spectacol.get_durata()))