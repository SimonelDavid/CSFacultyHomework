from Repository.Jucator_Repository import RepoJucator
from Domain.Jucator import Jucator

class JucatorFileRepo(RepoJucator):

    def __init__(self, file_name):
        RepoJucator.__init__(self)
        self.__file_name = file_name
        self.load_from_file()

    def __creeaza_jcuator_de_pe_linie(self, line):
        fields = line.split(" | ")
        fields[3] = fields[3].split("\n")
        jucator = Jucator(fields[0], fields[1], int(fields[2]), fields[3][0])
        return jucator

    def __creeaza_nume_prenume(self, line, poz):
        fields = line.split(" | ")
        fields[1] = fields[1].split("\n")
        nume_prenume = []
        nume_prenume[poz][0] = fields[0]
        nume_prenume[poz][1] = fields[1][0]
        return nume_prenume

    def load_from_file_nume_prenume(self, nume_fis):
        fh = open(nume_fis)
        i = 0
        for line in fh:
            if line.strip() == "":
                continue
            nume_prenume = self.__creeaza_nume_prenume(line, i)
            i += 1
        fh.close()
        return nume_prenume

    def load_from_file(self):
        fh = open(self.__file_name)
        for line in fh:
            if line.strip() == "":
                continue
            jucator = self.__creeaza_jcuator_de_pe_linie(line)
            RepoJucator.adauga_jucator(self, jucator)
        fh.close()

    def append_to_file(self, jucator):
        fh = open(self.__file_name, 'a')
        line = str(jucator.get_nume()) + " | " + str(jucator.get_prenume()) + " | " + str(
            jucator.get_inaltime()) + " | " + str(jucator.get_post())
        fh.write("\n")
        fh.write(line)
        fh.close()

    def clear_line(self, nume, prenume):
        with open(self.__file_name, "r") as fh:
            lines = fh.readlines()

        for i in range(0, len(lines)):
            line = lines[i]
            fields = line.split(" | ")
            if line != '\n' and fields[0] == nume and fields[1] == prenume:
                del lines[i]
                break

        new_fh = open(self.__file_name, "w+")
        for new_line in lines:
            new_fh.write(new_line)

        new_fh.close()

    def modifica_linie(self, jucator):

        fh = open(self.__file_name, "r")
        list_of_lines = fh.readlines()

        for i in range(0, len(list_of_lines)):
            line = list_of_lines[i]
            fields = line.split(" | ")
            if line != '\n':
                if fields[0] == jucator.get_nume() and fields[1] == jucator.get_prenume():
                    list_of_lines[i] = jucator.get_nume()+" | "+jucator.get_prenume()+" | "+str(jucator.get_inaltime())+" | "+jucator.get_post()+"\n"

        fh = open(self.__file_name, "w")
        fh.writelines(list_of_lines)
        fh.close()
