import colorama
colorama.init()


class UserInterface:

    def __init__(self, melody_service):
        self.__melody_service = melody_service

    def __main_menu(self):
        print("")
        print(colorama.Fore.GREEN+"         Meniul principal al aplicatiei.")
        print(colorama.Fore.BLUE)
        print("1. Afiseaza melodiile.")
        print("2. Sterge melodie.")
        print("3. Modifica gen si data.")
        print("Scire exit pentru a iesi din aplicatie.")

    def __afisare(self):
        for melody in self.__melody_service.get_repo_melody():
            print(melody)

    def __modify(self):
        print("Introduceti titlul si artistul: ")
        titlu = input("Titlul: ")
        artist = input("Artistul: ")
        melody = self.__melody_service.get_melody(titlu, artist)
        gen = input("Introduceti noul gen: ")
        data = input("Introduceti noua data: ")
        try:
            self.__melody_service.modifica_gen_data(melody, gen, data)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)

    def __sterge(self):
        print("Introduceti titlul si artistul: ")
        titlu = input("Titlul: ")
        artist = input("Artistul: ")
        try:
            self.__melody_service.delete_melody(titlu,artist)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)

    def run(self):
        while True:
            self.__main_menu()
            cmd = input(">>> ")
            if cmd == "1":
                self.__afisare()
            elif cmd == "2":
                self.__sterge()
            elif cmd == "3":
                self.__modify()
            elif cmd == "exit":
                print(colorama.Fore.MAGENTA+"Multumesc pentru utilizare!")
                return
            else:
                print(colorama.Fore.RED+"Comanda invalida!")