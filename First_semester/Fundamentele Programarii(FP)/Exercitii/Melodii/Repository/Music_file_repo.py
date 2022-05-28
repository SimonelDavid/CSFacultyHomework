from Repository.Music_repo import MusicRepo
from Domain.melody import Melody
from Validation.melodyValidation import MelodyValidation


class MusicRepoFile(MusicRepo):

    def __init__(self, file_name):
        MusicRepo.__init__(self)
        self.__file_name = file_name
        self.load_from_file()

    def get_repo(self):
        return MusicRepo.get_repo(self)

    def __creeaza_melodia(self, line):
        fields = line.split(" | ")
        melody = Melody(fields[0], fields[1], fields[2], fields[3])
        return melody

    def load_from_file(self):
        fh = open(self.__file_name)
        for line in fh:
            if line.strip() == "":
                continue
            melody = self.__creeaza_melodia(line)
            MusicRepo.adauga_exemplar(self, melody)
        fh.close()

    def clear_line(self, titlu, artist):
        with open(self.__file_name, "r") as fh:
            lines = fh.readlines()

        for i in range(0, len(lines)):
            line = lines[i]
            fields = line.split(" | ")
            if line != '\n' and fields[0] == titlu and fields[1] == artist:
                del lines[i]
                break

        new_fh = open(self.__file_name, "w+")
        for new_line in lines:
            new_fh.write(new_line)

        new_fh.close()

    def modify_line(self, melody):

        fh = open(self.__file_name, "r")
        list_of_lines = fh.readlines()

        for i in range(0, len(list_of_lines)):
            line = list_of_lines[i]
            fields = line.split(" | ")
            if line != '\n':
                if fields[0] == melody.get_titlu() and fields[1] == melody.get_artist():
                    list_of_lines[i] = melody.get_titlu()+" | "+melody.get_artist()+" | "+melody.get_gen()+" | "+melody.get_data()+" | "+'\n'

        fh = open(self.__file_name, "w")
        fh.writelines(list_of_lines)
        fh.close()

