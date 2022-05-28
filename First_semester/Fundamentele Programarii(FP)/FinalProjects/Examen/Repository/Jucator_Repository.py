from Domain.Jucator import Jucator

class RepoJucator:

    def __init__(self):
        self.__jucatori = []

    def __len__(self):
        return len(self.__jucatori)

    def creeaza_jucator(self, nume, prenume, inaltime, post):
        Jucator(nume, prenume, inaltime, post)

    def adauga_jucator(self, jucator):
        self.__jucatori.append(jucator)

    def get_repo(self):
        if self.__len__() == 0:
            raise Exception("Nu exista jucatori introdusi!")
        return self.__jucatori

    def get_jucator(self, nume, prenume):
        for i in range(0, len(self.__jucatori)):
            if self.__jucatori[i].get_nume() == nume and self.__jucatori[i].get_prenume() == prenume:
                return self.__jucatori[i]
        raise Exception("Nu exista jucatori cu numele "+str(nume)+" si prenumele "+str(prenume)+".")

    def modifica_inaltimea(self, nume, prenume, inaltime):

        jucator = self.get_jucator(nume, prenume)

        jucator.set_inaltime(inaltime)

    def delete_inregistrare(self, poz):
        del(self.__jucatori[poz])