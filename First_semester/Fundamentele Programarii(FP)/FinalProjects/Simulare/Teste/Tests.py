from Domain.imobil import Imobil
from Repository.RepoImobil import RepoImobiliare
from Service.ServiceImobil import ServiceulImobilelor

class Teste:

    def test_obiect_imobil(self):
        """
            Functia test_obiect_imobil() are rolul de a testa obiectul imobil.
        :return:
        """
        id_imobil = 19
        adresa = "str.Independentei nr.21 Deva"
        pret = 260
        tip = "inchiriere"
        imobil1 = Imobil(id_imobil, adresa, pret, tip)

        assert imobil1.get_id_imobil() == id_imobil
        assert imobil1.get_adresa() == adresa
        assert imobil1.get_pret() == pret
        assert imobil1.get_tip() == tip

    def test_load(self):

        """
            Functia test_load(self) are rolul de a testa incarcarea inregistrarilor din Test.txt.
        :return:
        """

        repo_imobil = RepoImobiliare("Test.txt")
        service_imobil = ServiceulImobilelor(repo_imobil)
        service_imobil.load_din_fisier()

        imobil1 = Imobil(23, "str.Decebal nr.10 Cluj-Napoca", 110000, "vanzare")
        imobil2 = Imobil(21, "str.Independentei nr.21 Deva", 260, "inchiriere")
        imobil3 = Imobil(6, "str.Rapsodiei nr.11 CLuj-Napoca", 141000, "vanzare")
        imobil4 = Imobil(14, "str.Horia nr.6 Cluj-Napoca", 450, "inchiriere")

        assert service_imobil.get_repository().get_one(23).get_id_imobil() == imobil1.get_id_imobil()
        assert service_imobil.get_repository().get_one(21).get_id_imobil() == imobil2.get_id_imobil()
        assert service_imobil.get_repository().get_one(6).get_id_imobil() == imobil3.get_id_imobil()
        assert service_imobil.get_repository().get_one(14).get_id_imobil() == imobil4.get_id_imobil()

    def test_medie_pret(self):

        """
            Functia test_medie_pret(self) are rolul de a testa media de pret pentru un anumit tip de oferta.
        :return:
        """

        repo_imobil = RepoImobiliare("Test.txt")
        service_imobil = ServiceulImobilelor(repo_imobil)
        service_imobil.load_din_fisier()

        assert service_imobil.medie_pret("vanzare") == 125500
        assert service_imobil.medie_pret("inchiriere") == 355

    def test_comision(self):

        """
            Functia test_comision(self) are rolul de a testa care este comsiionul pentur pretul negociat.
        :return:
        """

        repo_imobil = RepoImobiliare("Test.txt")
        service_imobil = ServiceulImobilelor(repo_imobil)
        service_imobil.load_din_fisier()

        assert service_imobil.comision_tranzactie(105000, 23) == 2100
        assert service_imobil.comision_tranzactie(240, 21) == 120


    def test_run_all(self):

        """
            Functia test_run_all(self) are rolul de a efectua toate testele.
        :return:
        """

        self.test_obiect_imobil()
        self.test_load()
        self.test_medie_pret()
        self.test_comision()
