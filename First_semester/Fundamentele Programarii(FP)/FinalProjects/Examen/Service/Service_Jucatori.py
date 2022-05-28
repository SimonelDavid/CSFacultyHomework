import random
from Domain.Jucator import Jucator

class JucatoriService:

    def __init__(self, repo, validation):
        self.__repo_jucatori = repo
        self.__validare_jucator = validation

    def adauga_jucator_nou(self, nume, prenume, inaltime, post):
        """
            Functia adauga_jucator_nou(self, nume, prenume, inaltime, post) are rolul de a adauga in repository un nou
            jucator introdus de la tastatura.
        :param nume: string
        :param prenume: string
        :param inaltime: nr intreg
        :param post: string
        :return:
        """

        jucator = Jucator(nume, prenume, inaltime, post)

        self.__validare_jucator.validarea_jucatorului(jucator)
        self.__repo_jucatori.adauga_jucator(jucator)
        self.__repo_jucatori.append_to_file(jucator)

    def get_repository(self):
        """
            Functia get_repository(self) are rolul de a returna lista de jucatori.
        :return: lista de obiecte
        """

        return self.__repo_jucatori.get_repo()

    def modifica_inaltime(self, nume, prenume, inaltime):
        """
            Functia modifica_inaltime(self, nume, prenume, inaltime) are rolul de a modifica inaltimea unui jucator.
        :param nume: string
        :param prenume: string
        :param inaltime: nr intreg
        :return:
        """

        self.__validare_jucator.validare_nume(nume)
        self.__validare_jucator.validare_prenume(prenume)
        self.__validare_jucator.validare_inaltime(inaltime)

        self.__repo_jucatori.modifica_inaltimea(nume, prenume, inaltime)
        jucator = self.__repo_jucatori.get_jucator(nume, prenume)
        self.__repo_jucatori.modifica_linie(jucator)

    def delete_jucator(self, poz):
        """
            Functia delete_jucator(self, poz) are rolul de a sterge din repository si din fisier elementul aflat pe
            pozitia poz.
        :param poz: nr intreg
        :return:
        """

        nume = ""
        prenume = ""
        jucatori = self.get_repository()
        for i in range(0, len(jucatori)):
            if i == poz:
                nume = jucatori[i].get_nume()
                prenume = jucatori[i].get_prenume()
        self.__repo_jucatori.delete_inregistrare(poz)
        self.__repo_jucatori.clear_line(nume, prenume)

    def creeaza_echipa(self):
        """
            Functia creeaza_echipa(self) are rolul de a returna o echipa formata din 2 fundasi, 3 extreme si 1 pivot.
            In cazul in care nu sunt suficienti jucatori pentru diecare post introdusi in aplicatie, se va afisa eroarea
            "EROARE!"+"\n"+"Nu a fost creeata echipa!"+"\n"+"Posibila problema: in aplicatie nu au fost inregistrati
            suficienti fundasi, pivoti sau extreme."
        :return: lista de obiecte
        """

        echipa = []
        i = j = k = 0
        jucatori = self.get_repository()

        for ind in range(0, len(jucatori)):
            if jucatori[ind].get_post() == "Fundas" and i < 2:
                echipa.append(jucatori[ind])
                i += 1
            elif jucatori[ind].get_post() == "Pivot" and j < 1:
                echipa.append(jucatori[ind])
                j += 1
            elif jucatori[ind].get_post() == "Extrema" and k < 2:
                echipa.append(jucatori[ind])
                k += 1
        if i == 2 and j == 1 and k == 2:
            return echipa
        else:
            raise Exception("EROARE!"+"\n"+"Nu a fost creeata echipa!"+"\n"+"Posibila problema: in aplicatie nu au fost inregistrati suficienti fundasi, pivoti sau extreme.")

    def creeaza_jucatori_random(self, nume_fisier):
        """
            Functia creeaza_jucatori_random(self, nume_fisier) are rolul de a genera random jucatori cu nume si prenume din fisierul nume_fisier.
        :param nume_fisier:
        :return:
        """
        #nume = self.__repo_jucatori.load_from_file_nume_prenume(nume_fisier)
        pass