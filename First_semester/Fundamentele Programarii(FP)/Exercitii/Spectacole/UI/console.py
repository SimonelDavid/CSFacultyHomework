import colorama
colorama.init()

class UserInterface:

    def __init__(self, service):
        self.__service = service

    def __ui_main_menu(self):
        print(colorama.Fore.GREEN+"     Meniul Principal")
        print(colorama.Fore.BLUE)
        print("1. Adauga spectacole.")
        print("2. Afiseaza spectacolele.")
        print("3. Modifica genul si durata unui spectacol.")
        print("Scrie comanda exit pentru a parasi aplicatia.")

    def __citire_titlu(self):
        titlu = input("Introduceti titlul: ")
        return titlu

    def __citire_artist(self):
        artist = input("Introduceti artistul: ")
        return artist

    def __citire_gen(self):
        gen = input("Introduceti genul: ")
        return gen

    def __citire_durata(self):
        durata = 0
        try:
            durata = int(input("Introduceti durata: "))
        except ValueError:
            print(colorama.Fore.RED+"Introduceti un numar!")
        return durata

    def adaugare(self):
        titlu = self.__citire_titlu()
        artist = self.__citire_artist()
        gen = self.__citire_gen()
        durata = self.__citire_durata()

        try:
            self.__service.adauga_elemente(titlu, artist, gen, durata)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)

    def afisare(self):
        for spectacol in self.__service.get_repo():
            print(spectacol)

    def modificare(self):

        print(colorama.Fore.BLUE+"Introduceti titlul si artistul spectacolului dorit: ")
        titlu = self.__citire_titlu()
        artist = self.__citire_artist()

        try:
            spectacol = self.__service.get_spectacol(titlu, artist)
            print(colorama.Fore.BLUE + "Introduceti noul gen si noua durata: ")
            gen = self.__citire_gen()
            durata = self.__citire_durata()

            try:
                self.__service.modifica_gen_durata(spectacol, gen, durata)
            except Exception as ex:
                print(colorama.Fore.RED)
                print(ex)
        except Exception as ex:
            print(ex)


    def run(self):

        while True:
            self.__ui_main_menu()
            cmd = input(">>> ")

            if cmd == "1":
                self.adaugare()
            elif cmd == "2":
                self.afisare()
            elif cmd == "3":
                self.modificare()
            elif cmd == "exit":
                print(colorama.Fore.MAGENTA+"Multumesc pentru utilizare!")
                return
            else:
                print(colorama.Fore.RED+"Introduceti o comanda valida!")
