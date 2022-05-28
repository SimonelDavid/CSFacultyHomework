from Domain.Curs import Curs


class CursuriRepo:

    def __init__(self, file_path):
        self.__file_path = file_path
        self.__repo_cursuri = []

    def load_cursuri_from_file(self):
        """
            Aceasta functie are rolul de a incarca multiple cursuri din fisierul file_path in repository.
        """

        fh = open(self.__file_path)
        content = fh.read()
        fh.close()
        lines = content.split("\n")

        for line in lines:
            if line.strip() == "":
                continue
            fields = line.split(",")
            curs = Curs(fields[0], fields[1], fields[2], int(fields[3]))
            self.add(curs)

    def add(self, curs):
        for curs_local in self.__repo_cursuri:
            if curs_local.get_id_curs() == curs.get_id_curs():
                raise Exception("Cursul cu id-ul "+str(curs.get_id_curs())+" deja exista in lista! Atentie la cursurile introduse in fisier!\n")
        self.__repo_cursuri.append(curs)

    def get_all(self):
        return self.__repo_cursuri

    def get_one(self, id_curs):

        for curs in self.__repo_cursuri:
            if curs.get_id_curs() == id_curs:
                return curs
        raise Exception("ID-ul nu este corespondent unui curs inregistrat!\n")