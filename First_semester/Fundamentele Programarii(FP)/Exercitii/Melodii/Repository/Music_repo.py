from Domain.melody import Melody


class MusicRepo:

    def __init__(self):
        self.__melodii = []

    def __len__(self):
        return len(self.__melodii)

    def creare_exemplar(self, titlu, artist, gen, data):
        return Melody(titlu, artist, gen, data)

    def get_repo(self):
        return self.__melodii

    def adauga_exemplar(self, melody):
        self.__melodii.append(melody)

    def delete_exemplar(self, poz):
        del(self.__melodii[poz])

    def get_melody(self, titlu, artist):
        for melody in self.__melodii:
            if melody.get_titlu() == titlu and melody.get_artist() == artist:
                return melody