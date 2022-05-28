class CursService:

    def __init__(self, curs_repo, inscriere):
        self.__curs_repo = curs_repo
        self.__inscriere = inscriere

    def get_repo(self):
        return self.__curs_repo

    def incarcare_din_fisier(self):
        self.__curs_repo.load_cursuri_from_file()

    def cauta_curs(self, limba):
        lista_locala = self.__curs_repo.get_all()
        lista_noua = []

        for curs in lista_locala:
            if limba in curs.get_limba():
                lista_noua.append(curs)

        if len(lista_noua) == 0:
            raise Exception("Nu exista cursuri in limba "+str(limba)+"!\n")
        else:
            return lista_noua

    def inscriere_la_curs(self, id_curs, nr_ore):
        lista_locala = self.__curs_repo.get_all()

        for curs in lista_locala:
            if curs.get_id_curs() == id_curs:
                inscriere_noua = self.__inscriere(curs, nr_ore)
                return inscriere_noua

        raise Exception("Nu exista cursuri cu id "+str(id_curs)+"!\n")
