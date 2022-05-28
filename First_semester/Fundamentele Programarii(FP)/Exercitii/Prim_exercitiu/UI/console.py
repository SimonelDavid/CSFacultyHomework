import colorama
colorama.init()

class UserInterface:

    def __init__(self, service_picturi):
        self.__service_picturi = service_picturi

    def __ui_general_options(self):
        print("")
        print(colorama.Fore.BLUE+"      Meniul principal pentru aplicatia de picturi")
        print(colorama.Fore.GREEN+"1. Vezi inregistrarile din lista")

    def __afisare_inregistrari(self):
        for pictura in self.__service_picturi.get_repo():
            print(pictura)

    def run(self):
        while True:
            self.__ui_general_options()
            cmd = input(">>>")
            if cmd == "1":
                self.__afisare_inregistrari()
            elif cmd == "exit":
                print(colorama.Fore.LIGHTRED_EX+"Multumesc pentru utilizare.\n")
                return
            else:
                print(colorama.Fore.RED+"Introduceti o comanda valida!\n")