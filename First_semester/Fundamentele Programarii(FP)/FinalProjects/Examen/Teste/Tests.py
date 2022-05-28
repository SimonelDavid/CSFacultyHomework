from Domain.Jucator import Jucator
from Repository.File_Repository_Jucator import JucatorFileRepo
from Service.Service_Jucatori import JucatoriService
from Validation.Validare import ValidareJucator

class TesteJucatori:

    def _test_creeare_jucator(self):
        prenume = "Niksa"
        nume = "Nikolic"
        post = "Fundas"
        inaltime = 192

        jucator = Jucator(nume, prenume, inaltime, post)

        assert jucator.get_nume() == nume
        assert jucator.get_prenume() == prenume
        assert jucator.get_inaltime() == inaltime
        assert jucator.get_post() == post

    def _test_add_to_file(self):
        repo = JucatorFileRepo("TesteJucatori.txt")
        validare = ValidareJucator()
        service = JucatoriService(repo, validare)

        service.adauga_jucator_nou("Mutu", "Ciprian", 178, "Pivot")
        assert len(service.get_repository()) == 6

        service.adauga_jucator_nou("Ramos", "Sergio", 188, "Fundas")
        assert len(service.get_repository()) == 7

    def _test_echipa(self):
        repo = JucatorFileRepo("TesteJucatori.txt")
        validare = ValidareJucator()
        service = JucatoriService(repo, validare)

        assert len(service.creeaza_echipa()) == 5

    def _test_delete_from_file(self):
        repo = JucatorFileRepo("TesteJucatori.txt")
        validare = ValidareJucator()
        service = JucatoriService(repo, validare)

        assert len(service.get_repository()) == 7
        service.delete_jucator(6)

        assert len(service.get_repository()) == 6
        service.delete_jucator(5)

    def run(self):
        self._test_creeare_jucator()
        self._test_add_to_file()
        self._test_echipa()
        self._test_delete_from_file()