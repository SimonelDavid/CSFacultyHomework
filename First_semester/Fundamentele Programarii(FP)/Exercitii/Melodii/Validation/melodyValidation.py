

class MelodyValidation:
    def validare_gen(self, gen):
        if gen != "Rock" or gen != "Pop" or gen != "Jazz" or gen != "Altele":
            raise Exception("Genul nu este unul valid!")

