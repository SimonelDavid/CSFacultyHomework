class UserInterface:

    def __init__(self, service):
        self.__service_jucator = service

    def __ui_meniu_principal(self):
        print("         Meniu principal")
        print("1. Adauga un jucator.")
        print("2. Afiseaza jucatorii.")
        print("3. Modifica inaltimea.")
        print("4. Creeaza o echipa cu jucatorii inregistrati.")
        print("Scrie comanda exit pentru a parasi aplicatia.")

    def citire_nume(self):
        nume = input("Numele: ")
        return nume

    def citire_prenume(self):
        prenume = input("Prenumele: ")
        return prenume

    def citire_inaltime(self):
        try:
            inaltime = int(input("Inaltimea: "))
            return inaltime
        except Exception as ex:
            print("EROARE! "+"\n"+"  Introduceti un numar intreg!")

    def citire_post(self):
        post = input("Postul: ")
        return post

    def adaugare_jucator_nou(self):
        try:
            self.__service_jucator.adauga_jucator_nou(self.citire_nume(), self.citire_prenume(), self.citire_inaltime(), self.citire_post())
        except Exception as ex:
            print(ex)

    def afisare_jucator(self):
        jucatori = self.__service_jucator.get_repository()

        for i in range(0, len(jucatori)):
            print(jucatori[i])

    def modificare(self):

        print("Scrie numele si prenumele pentru a putea gasi jucatorul. Apoi da noua inaltime pe care o vei modifica.")

        try:
            self.__service_jucator.modifica_inaltime(self.citire_nume(), self.citire_prenume(), self.citire_inaltime())
        except Exception as ex:
            print(ex)

    def creeare_echipa(self):
        print("Echipa este: ")
        print(" Prenume          Nume          Post          Inaltime")
        try:
            echipa = self.__service_jucator.creeaza_echipa()
            for i in range(0, len(echipa)):
                print(str(echipa[i].get_prenume())+"          "+str(echipa[i].get_nume())+"          "+str(echipa[i].get_post())+"          "+str(echipa[i].get_inaltime()))
        except Exception as ex:
            print(ex)

    def run(self):
        while True:
            self.__ui_meniu_principal()

            cmd = input(">>> ")

            if cmd == "1":
                self.adaugare_jucator_nou()
            elif cmd == "2":
                self.afisare_jucator()
            elif cmd == "3":
                self.modificare()
            elif cmd == "4":
                self.creeare_echipa()
            elif cmd == "exit":
                print("Multumesc pentru utilizare!")
                return
            else:
                print("Introdu o comanda valida!")