from Domain.imobil import Imobil


class RepoImobiliare:

    def __init__(self, file_name):
        self.__file_name = file_name
        self.__repo_imobiliare = []

    def load_from_file(self):

        """
            Functia load_from_file(self) are rolul de a incarca inregistrari din fisierul self.__file_name
        :return:
        """

        fh = open(self.__file_name)
        content = fh.read()
        fh.close()

        lines = content.split("\n")

        for line in lines:
            if line.strip() == "":
                continue
            fields = line.split(",")
            imobil = Imobil(int(fields[0]), fields[1], int(fields[2]), fields[3])
            self.add(imobil)

    def add(self, imobil):

        """
            Functia are rolul de a adauga in lista de imobile un nou imobil.
        :param imobil:
        :return:
        """

        for imobil_local in self.__repo_imobiliare:
            if imobil.get_id_imobil() == imobil_local.get_id_imobil():
                raise Exception("Imobilul cu ID-ul "+str(imobil.get_id_imobil())+" deja exista in lista! Atentie la inregistrarile din fisier!\n")

        self.__repo_imobiliare.append(imobil)

    def get_all(self):
        return self.__repo_imobiliare

    def get_one(self, id_imobil):
        for imobil in self.__repo_imobiliare:
            if imobil.get_id_imobil() == id_imobil:
                return imobil
        raise Exception("Nu exista in inregistrari imobil cu ID-ul "+str(id_imobil)+"!\n")