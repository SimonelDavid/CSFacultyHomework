class ServiceulImobilelor:

    def __init__(self, repo_imobil):
        self.__repo_imobil = repo_imobil

    def load_din_fisier(self):
        """
            Functia are rolul de a da load tuturor inregistrarilor din fisier.
        :return:
        """
        self.__repo_imobil.load_from_file()

    def get_repository(self):
        return self.__repo_imobil

    def get_imobil(self, id_imobil):
        return self.__repo_imobil.get_one(id_imobil)

    def medie_pret(self, tip):
        """
            Functia medie_pret(self, tip) are rolul de a calcula pretul mediu pentru tipul tip
        :param tip:
        :return pret_final:
        """
        contor = 0
        pret_total = 0
        lista_locala = self.__repo_imobil.get_all()

        for imobil in lista_locala:
            if imobil.get_tip() == tip:
                contor += 1
                pret_total += imobil.get_pret()

        pret_final = pret_total/contor

        return pret_final

    def comision_tranzactie(self, pret_tranzactie, id_imobil):
        """
            Functia comision_tranzactie(self, pret_tranzactie, id_imobil) are rolul de a calcula comisionul pentru imobilul cu id-ul id_imobil pentru pretul nou pret_tranzactie
        :param pret_tranzactie:
        :param id_imobil:
        :return comision:
        """
        lista_locala = self.__repo_imobil.get_all()

        for imobil in lista_locala:
            if imobil.get_id_imobil() == id_imobil:
                if imobil.get_tip() == "vanzare":
                    comision = 0.02*pret_tranzactie
                    return comision
                elif imobil.get_tip() == "inchiriere":
                    comision = 0.5*pret_tranzactie
                    return comision
                else:
                    raise Exception("Atentie la introducerea in lista deoarece tipul ofertei a fost introdus incorect!\n")

        raise Exception("Nu exista in inregistrari imobil cu ID-ul "+str(id_imobil)+"!\n")
