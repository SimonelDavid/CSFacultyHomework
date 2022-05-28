from Domain.Spectacol import Spectacol
from Repository.Spectacol_repository_files import SpectacolRepoFile
from Validation.Validare_Spectacol import SpectacolValidation
from Service.Service_spectacol import SpecatacolService

class Teste:

    def _test_creeare_spectacol(self):
        titlu = "Primavara"
        artist = "Andre Rieu"
        gen = "Concert"
        durata = 3

        spectacol = Spectacol(titlu,artist,gen,durata)

        assert spectacol.get_titlu() == titlu
        assert spectacol.get_artist() == artist
        assert spectacol.get_gen() == gen
        assert spectacol.get_durata() == durata

    def _test_adaugare_exemplar(self):
        repo = SpectacolRepoFile("test_spectacole.txt")
        validation = SpectacolValidation()
        service = SpecatacolService(repo, validation)

        spectacol1 = Spectacol("O seara minunata de aprilie", "Andrei Marius", "Comedie", "2")
        spectacol2 = Spectacol("Dansul lebedelor", "Mariana Timisan", "Balet", "1")

        service.adauga_elemente(spectacol1.get_titlu(), spectacol1.get_artist(), spectacol1.get_gen(), spectacol1.get_durata())
        assert repo.get_spectacol("O seara minunata de aprilie", "Andrei Marius").get_titlu() == spectacol1.get_titlu()

        service.adauga_elemente(spectacol2.get_titlu(), spectacol2.get_artist(), spectacol2.get_gen(), spectacol2.get_durata())
        assert repo.get_spectacol("Dansul lebedelor", "Mariana Timisan").get_titlu() == spectacol2.get_titlu()

    def run(self):
        self._test_creeare_spectacol()
        #self._test_adaugare_exemplar()
