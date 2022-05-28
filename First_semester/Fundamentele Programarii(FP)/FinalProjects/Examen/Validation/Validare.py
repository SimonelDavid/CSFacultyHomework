class ValidareJucator:
    def validare_nume(self, nume):
        if nume == "":
            raise Exception("EROARE!"+"\n"+"  Introduceti un nume valid! Adica nu lasati campul gol.")

    def validare_prenume(self, prenume):
        if prenume == "":
            raise Exception("EROARE! "+"\n"+"  Introduceti un prenume valid! Adica nu lasati campul gol.")

    def validare_inaltime(self, inaltime):
        if inaltime <= 140:
            raise Exception("EROARE! "+"\n"+"  Inaltimea este mai mica sua egala decat 140.")

    def validare_post(self, post):
        if post != "Fundas" and post != "Pivot" and post != "Extrema":
            raise Exception("EROARE! "+"\n"+"  Postul trebuie sa fie Fundas, Pivot sau Extrema!")

    def validarea_jucatorului(self, jucator):
        self.validare_nume(jucator.get_nume())
        self.validare_prenume(jucator.get_prenume())
        self.validare_inaltime(jucator.get_inaltime())
        self.validare_post(jucator.get_post())
