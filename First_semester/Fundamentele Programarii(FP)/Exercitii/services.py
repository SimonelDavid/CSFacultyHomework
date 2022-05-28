import random

def specific_string(self, length):
    sample_string = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqerstuvwxyz'
    result = ''.join((random.choice(sample_string)) for x in range(length))
    return result


def clients_random(self, i, n):
    '''
        Functia clients_random(self,n) are rolul de a aduga in repository clienti la intamplare.
    '''

    if i < n:
        j = 0
        id = 0
        name = ""
        x = 0
        cnp = 0
        try:
            id = random.randint(1, 100)
            self.__validator_client.validare_id_client(id)
            j = j + 1
        except Exception as ex:
            j = 0

        try:
            x = random.randint(10, 35)
            name = self.specific_string(x)
            self.__validator_client.validare_nume_client(name)
            j = j + 1
        except Exception as ex:
            j = 0

        try:
            cnp1 = random.randint(1000000000000, 9999999999999)
            cnp = str(cnp1)
            self.__validator_client.validare_cnp_client(self.__repository_client, cnp)
            j = j + 1
        except Exception as ex:
            j = 0

        if j == 3:
            try:
                self.adauga_client(id, name, cnp)
                self.clients_random(i + 1, n)
            except Exception as ex:
                self.clients_random(i - 1, n)
    elif i >= n:
        return


"""
    i = 0

    while i<n:
        j = 0
        id = 0
        name = ""
        x = 0
        cnp = 0
        try:
            id = random.randint(1,100)
            self.__validator_client.validare_id_client(id)
            j = j+1
        except Exception as ex:
            j = 0
        try:
            x = random.randint(10,35)
            name = self.specific_string(x)
            self.__validator_client.validare_nume_client(name)
            j = j+1
        except Exception as ex:
            j = 0
        try:
            cnp1 = random.randint(1000000000000,9999999999999)
            cnp = str(cnp1)
            self.__validator_client.validare_cnp_client(self.__repository_client,cnp)
            j = j+1
        except Exception as ex:
            j = 0

        if j == 3:
            try:
                i = i+1
                self.adauga_client(id,name,cnp)
            except Exception as ex:
                i = i-1
"""

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

