import colorama
colorama.init()

class Consola:

    def __init__(self, service_imobil):
        self.__service_imobil = service_imobil
        self.__incarca_inregistrari()

    def __ui_meniu_principal(self):
        print("")
        print(colorama.Fore.BLUE+"         Meniu principal")
        print(colorama.Fore.GREEN+"1. Afiseaza toate inregistrarile din lista.")
        print("2. Media pretului pentru un tip de oferta dorit.")
        print("3. Efectueaza o tranzactie.")
        print("Introdu comanda exit pentru a iesi din aplicatie.")

    def __incarca_inregistrari(self):
        try:
            self.__service_imobil.load_din_fisier()
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)

    def __afisare_inregistrari(self):

        print(colorama.Fore.YELLOW)
        for imobil in self.__service_imobil.get_repository().get_all():
            print(imobil)

    def __media_pret(self):
        try:
            tip_oferta = input("Introdu tipul ofertei pentru care doresti sa vezi media de pret: ")
            print(colorama.Fore.YELLOW+"Media pretului pentru "+str(tip_oferta)+" este: "+str(self.__service_imobil.medie_pret(tip_oferta))+".\n")
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)

    def __efectuare_tranzactie(self):
        try:
            self.__afisare_inregistrari()
            print(colorama.Fore.BLUE)
            id_imobil = int(input("Introdu ID-ul imobilului pe care doresti sa il tranzactionezi: "))
            pret_negociat = int(input("Introdu pretul negociat intre proprietar si cumparator: "))
            print("Adresa imobilului este "+str(self.__service_imobil.get_imobil(id_imobil).get_adresa())+", iar comisionul aferent tranzactiei este "+str(self.__service_imobil.comision_tranzactie(pret_negociat, id_imobil))+".\n")
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)

    def run(self):

        while True:
            self.__ui_meniu_principal()
            cmd = input(">>>")
            if cmd == "1":
                self.__afisare_inregistrari()
            elif cmd == "2":
                self.__media_pret()
            elif cmd == "3":
                self.__efectuare_tranzactie()
            elif cmd == "exit":
                print(colorama.Fore.LIGHTRED_EX+"Multumesc pentru utilizare!\n")
                return
            else:
                print(colorama.Fore.RED+"Atentie! Introdu o comanda valida!\n")
