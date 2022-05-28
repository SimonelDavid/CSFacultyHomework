class SpecatacolService:

    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def adauga_elemente(self, titlu, artist, gen, durata):
        """
        Functia adauga_elemente(self, titlu, artist, gen, durata) are rolul de face apeluri catre functii din pachetul de validare si din pachetul de repository astfel incat daca totul decurge cu succes sa fie adugat la final un nou spectacol cu parametrii specificati.
        :param titlu:
        :param artist:
        :param gen:
        :param durata:
        :return:
        """

        spectacol = self.__repo.creeare_exemplar(titlu, artist, gen, durata)
        self.__validator.validare_spectacol(spectacol)
        self.__repo.adauga_exemplar(spectacol)
        self.__repo.append_to_file(spectacol)


    def modifica_gen_durata(self, spectacol, gen, durata):
        """
        Functia modifica_gen_durata(self, spectacol, gen, durata) are rolul de a modifica atat in fisier cat si in memorie campurile gen si durata ale unui obiect spectacol.
        :param spectacol:
        :param gen:
        :param durata:
        :return:
        """

        self.__validator.validare_gen(gen)
        self.__validator.validare_durata(durata)
        spectacol.set_gen(gen)
        spectacol.set_durata(durata)
        self.__repo.modify_line(spectacol)

    def get_repo(self):
        """
        Functia get_repo(self) are rolul de a returna lista de obiecte inregistrate si anume spectacolele.
        :return: lista
        """

        return self.__repo.get_repository()

    def get_spectacol(self, titlu, artist):
        """
        Functia get_spectacol(self, titlu, artist) are rolul de a returna un unic obiect din lista de obiecte si anume un spectacol cu titlul si artistul specificate.
        :param titlu:
        :param artist:
        :return:
        """

        return self.__repo.get_spectacol(titlu, artist)
