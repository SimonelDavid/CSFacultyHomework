from Domain.Spectacol import Spectacol

class RepoSpectacol:

    def __init__(self):
        self.__spectacole = []

    def __len__(self):
        return len(self.__spectacole)

    def creeare_exemplar(self, titlu, artist, gen, durata):
        return Spectacol(titlu, artist, gen, durata)

    def adauga_exemplar(self, spectacol):
        self.__spectacole.append(spectacol)

    def get_repository(self):
        return self.__spectacole

    def delete_exemplar(self, poz):
        del(self.__spectacole[poz])

    def get_spectacol(self, titlu, artist):

        for spectacol in self.__spectacole:
            if spectacol.get_titlu() == titlu and spectacol.get_artist() == artist:
                return spectacol
        raise Exception("Spectacolul nu a fost gasit!")