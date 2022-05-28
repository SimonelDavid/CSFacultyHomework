from Repository.Sepctacol_Repository import RepoSpectacol


class SpectacolRepoFile(RepoSpectacol):

    def __init__(self, file_name):
        RepoSpectacol.__init__(self)
        self.__file_name = file_name
        self.load_from_file()

    def creeaza_spectacol(self, line):
        fields = line.split(" | ")
        return RepoSpectacol.creeare_exemplar(self, fields[0], fields[1], fields[2], fields[3])

    def load_from_file(self):

        fh = open(self.__file_name)

        for line in fh:
            if line.strip() == "":
                continue
            RepoSpectacol.adauga_exemplar(self, self.creeaza_spectacol(line))
        fh.close()

    def append_to_file(self, spectacol):
        fh = open(self.__file_name, 'a')
        line = str(spectacol.get_titlu())+" | "+str(spectacol.get_artist())+" | "+str(spectacol.get_gen())+" | "+str(spectacol.get_durata())
        fh.write("\n")
        fh.write(line)
        fh.close()

    def modify_line(self, spectacol):

        fh = open(self.__file_name, "r")
        list_of_lines = fh.readlines()

        for i in range(0, len(list_of_lines)):
            line = list_of_lines[i]
            fields = line.split(" | ")
            if line != "\n":
                if fields[0] == spectacol.get_titlu() and fields[1] == spectacol.get_artist():
                    list_of_lines[i] = str(spectacol.get_titlu()) + " | " + str(spectacol.get_artist()) + " | " + str(spectacol.get_gen()) + " | " + str(spectacol.get_durata())+"\n"

        fh = open(self.__file_name, "w")
        fh.writelines(list_of_lines)
        fh.close()