import colorama
colorama.init()


class Consola:

    def __init__(self, service_cursuri):
        self.__service_cursuri = service_cursuri
        self.__load_cursuri()

    def __meniu_principal(self):
        print("")
        print(colorama.Fore.BLUE+"         Meniu principal")
        print(colorama.Fore.GREEN+"1. Afiseaza toate inregistrarile.")
        print("2. Cauta cursuri dupa limba dorita.")
        print("3. Inscrie-te la un curs.")
        print("Scrie comanda exit pentru a parasi aplicatia.")

    def __afisare_inregistrari(self):
        for curs in self.__service_cursuri.get_repo().get_all():
            print(curs)

    def __load_cursuri(self):
        try:
            self.__service_cursuri.incarcare_din_fisier()
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)

    def __cauta_curs_dupa_limba(self):
        try:
            limba = input("Introdu limba cursului pe care doresti sa il gasesti: ")
            for curs in self.__service_cursuri.cauta_curs(limba):
                print(curs)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)

    def __inscriere_la_curs(self):
        try:
            id_curs = input("Introdu ID-ul cursului la car edoresti sa participi: ")
            nr_ore = input("Intordu numarul de ore pe care doresti sa le faci: ")
            print(self.__service_cursuri.inscriere_la_curs(id_curs, int(nr_ore)))
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)

    def run(self):

        while True:
            self.__meniu_principal()
            cmd = input(">>>")
            if cmd == "1":
                self.__afisare_inregistrari()
            elif cmd == "2":
                self.__cauta_curs_dupa_limba()
            elif cmd == "3":
                self.__inscriere_la_curs()
            elif cmd == "exit":
                print(colorama.Fore.LIGHTRED_EX+"Multumesc pentru utilizare!\n")
                return
            else:
                print(colorama.Fore.RED+"Introdu o comanda corecta!\n")