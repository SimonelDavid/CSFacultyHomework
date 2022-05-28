
class MelodyService:

    def __init__(self, melody_validator, melody_repo):
        self.__melody_valid = melody_validator
        self.__melody_repo = melody_repo

    def delete_melody(self, titlu, artist):
        local_melodies = self.__melody_repo.get_repo()

        melody = self.__melody_repo.get_repo()

        for i in range(0, len(local_melodies)):
            if local_melodies[i] == melody:
                self.__melody_repo.clear_line(titlu, artist)
                self.__melody_repo.delete_exemplar(i)

    def get_melody(self, titlu, artist):
        return self.__melody_repo.get_melody(titlu, artist)

    def get_repo_melody(self):
        return self.__melody_repo.get_repo()

    def modifica_gen_data(self, melody, gen, data):
        local_melodies = self.get_repo_melody()
        self.__melody_valid.validare_gen(gen)

        for melodie in local_melodies:
            if melody == melodie:
                melody.set_gen(gen)
                melody.set_data(data)
                self.__melody_repo.modify_line(melody)
                return
