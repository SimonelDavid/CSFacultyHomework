from Domain.Picturi import Picturi

class PicturiRepository:

    def __init__(self, file_path):
        self.__file_path = file_path
        self.__repo_picturi = []
        self.load_from_file()

    def __len__(self):
        return len(self.__repo_picturi)

    def __creeaza_pictura(self, line):
        fields = line.split(",")
        pictura = Picturi(int(fields[0]), fields[1], fields[2], int(fields[3]))
        return pictura

    def load_from_file(self):

        fh = open(self.__file_path)
        content = fh.read()
        lines = content.split("\n")
        for line in lines:
            if line.strip() == "":
                continue
            pictura = self.__creeaza_pictura(line)
            self.add(pictura)

    def add(self, pictura_noua):
        for pictura in self.__repo_picturi:
            if pictura.get_id_pictura() == pictura_noua.get_id_pictura():
                raise Exception("ID-ul picturii deja exista!\n")
        self.__repo_picturi.append(pictura_noua)

    def get_all(self):
        return self.__repo_picturi

    def get_pictura(self, id_pictura):
        for pictura in self.__repo_picturi:
            if pictura.get_id_pictura() == id_pictura:
                return pictura
        raise Exception("Nu exista aceste picturi.\n")