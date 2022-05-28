from Domain.Curs import Curs, Inscriere
from Repository.FileRepo import CursuriRepo
from Service.ServiceCurs import CursService

class Teste:

    def __test_creeare_obiect(self):
        id_curs = "ENG1"
        limba = "limba_engleza"
        nivel = "A1"
        pret = 70
        curs1 = Curs(id_curs, limba, nivel, pret)

        assert curs1.get_id_curs() == id_curs
        assert curs1.get_limba() == limba
        assert curs1.get_nivel() == nivel
        assert curs1.get_pret() == pret

    def __test_load_cursuri(self):
        repo_curs = CursuriRepo("Test.txt")
        curs_service = CursService(repo_curs, Inscriere)
        curs_service.incarcare_din_fisier()

        curs1 = Curs("ENG1", "limba_engleza", "A1", 70)
        curs2 = Curs("GER1", "limba_germana", "C2", 125)
        curs3 = Curs("SPN23", "limba_spaniola", "B2", 86)
        curs4 = Curs("SPN24", "limba_spaniola", "B1", 22)

        assert repo_curs.get_one("ENG1") == curs1
        assert repo_curs.get_one("GER1") == curs2
        assert repo_curs.get_one("SPN23") == curs3
        assert repo_curs.get_one("SPN24") == curs4

    def __test_cautare(self):
        repo_curs = CursuriRepo("Test.txt")
        curs_service = CursService(repo_curs, Inscriere)
        curs_service.incarcare_din_fisier()

        curs1 = Curs("ENG1", "limba_engleza", "A1", 70)
        curs2 = Curs("GER1", "limba_germana", "C2", 125)
        curs3 = Curs("SPN23", "limba_spaniola", "B2", 86)
        curs4 = Curs("SPN24", "limba_spaniola", "B1", 22)

        lista_locala = []
        lista_locala.append(curs1)
        assert curs_service.cauta_curs("engleza") == lista_locala

        lista_locala = []
        lista_locala.append(curs2)
        assert curs_service.cauta_curs("germana") == lista_locala

        lista_locala = []
        lista_locala.append(curs3)
        lista_locala.append(curs4)
        assert curs_service.cauta_curs("spaniola") == lista_locala

    def __test_inscriere(self):
        repo_curs = CursuriRepo("Test.txt")
        curs_service = CursService(repo_curs, Inscriere)
        curs_service.incarcare_din_fisier()

        curs1 = Curs("ENG1", "limba_engleza", "A1", 70)
        curs2 = Curs("GER1", "limba_germana", "C2", 125)
        curs3 = Curs("SPN23", "limba_spaniola", "B2", 86)
        curs4 = Curs("SPN24", "limba_spaniola", "B1", 22)

        inscriere1 = Inscriere(curs1, 4)
        inscriere2 = Inscriere(curs4, 3)
        inscriere3 = Inscriere(curs3, 2)
        inscriere4 = Inscriere(curs2, 8)

        assert curs_service.inscriere_la_curs("ENG1", 4).get_total() == inscriere1.get_total()
        assert curs_service.inscriere_la_curs("SPN24", 3).get_total() == inscriere2.get_total()
        assert curs_service.inscriere_la_curs("SPN23", 2).get_total() == inscriere3.get_total()
        assert curs_service.inscriere_la_curs("GER1", 8).get_total() == inscriere4.get_total()

    def test_run_all(self):
        self.__test_creeare_obiect()
        self.__test_load_cursuri()
        self.__test_cautare()
        self.__test_inscriere()
