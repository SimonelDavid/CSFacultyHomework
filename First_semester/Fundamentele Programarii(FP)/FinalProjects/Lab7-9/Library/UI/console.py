import colorama
colorama.init()


class UserConsole:

    def __init__(self, client_service, book_service):
        self.__client_service = client_service
        self.__book_service = book_service

    def __ui_general_options(self):
        print("")
        print(colorama.Fore.LIGHTGREEN_EX+"    Meniul principal pentru aplicatia de gestiune a bibliotecii")
        print(colorama.Fore.MAGENTA)
        print("1. Administreaza clientii.")
        print("2. Amdinistreaza cartile.")
        print("3. Randomizeaza clientii in lista.")
        print("Scrie exit pentru a iesi din aplicatie.\n")

    def __ui_clients_options(self):
        print("")
        print(colorama.Fore.BLACK+"Submeniu pentru optiunile gestiunii clientului")
        print(colorama.Fore.GREEN)
        print("1. Adauga client.")
        print("2. Afisare clienti.")
        print("3. Accesare cont.")
        print("4. Efectueaza cautari printre clienti.")
        print("5. Efectueaza rapoarte.")
        print("Scrie exit pentru a iesi din aplicatie.\n")

    def __ui_book_options(self):
        print("")
        print(colorama.Fore.BLACK+"Optiunile cartii alese")
        print(colorama.Fore.GREEN)
        print("1. Sterge cartea.")
        print("2. Modifica date.")
        print("Scrie exit pentru a iesi din aplicatie.\n")

    def __ui_account_options(self):
        print("")
        print(colorama.Fore.BLACK+"Gestiunea contului unui client")
        print(colorama.Fore.GREEN)
        print("1 .Inchiriaza o carte.")
        print("2. Returneaza carte.")
        print("3. Modificare date client.")
        print("4. Sterge clientul.")
        print("Scrie exit pentru a iesi din aplicatie.\n")

    def __ui_books_options(self):
        print("")
        print(colorama.Fore.BLACK+"Submeniu pentru optiunile gestiunii unei carti")
        print(colorama.Fore.GREEN)
        print("1. Adauga o carte noua.")
        print("2. Afiseaza cartile din lista.")
        print("3. Acceseaza o carte.")
        print("4. Afiseaza cartea cu titlul de lungime maxima.")
        print("5. Efectueaza cautari printre carti.")
        print("6. Efecturaza rapoarte.")
        print("Scrie exit pentru a iesi din aplicatie.\n")
    
    def __ui_modify_client_options(self):
        print("")
        print(colorama.Fore.BLACK+"Submeniu pentru optiunile de modificare a datelor unui client")
        print(colorama.Fore.GREEN)
        print("1. Modifica ID-ul clientului.")
        print("2. Modifica numele clientului.")
        print("3. Modifica CNP-ul clientului.")
        print("Scrie exit pentru a iesi din aplicatie.\n")
    
    def __ui_modify_book_data(self):
        print("")
        print(colorama.Fore.BLACK+"Submeniu pentru optiunile de modificare a datelor unei carti")
        print(colorama.Fore.GREEN)
        print("1. Modifica id-ul cartii.")
        print("2. Modifica numele cartii.")
        print("3. Modifica autorul cartii.")
        print("4. Modifica descrierea cartii.")
        print("Scrie exit pentru a iesi din aplicatie.\n")

    def __ui_search_for_books(self):
        print("")
        print(colorama.Fore.BLACK+"Submeniu pentru optiunile cautare a anumitor carti")
        print(colorama.Fore.GREEN)
        print("1. Cauta carti dupa ID.")
        print("2. Cauta carti dupa titlu.")
        print("3. Cauta carti dupa autor.")
        print("Scrie exit pentru a iesi din aplicatie.\n")
    
    def __ui_search_for_clients(self):
        print("")
        print(colorama.Fore.BLACK+"Submeniu pentru optiunile cautare a anumitor clienti")
        print(colorama.Fore.GREEN)
        print("1. Cauta clienti dupa ID.")
        print("2. Cauta clienti dupa cnp.")
        print("3. Cauta clienti dupa nume.")
        print("Scrie exit pentru a iesi din aplicatie.\n")
    
    def __ui_clients_reports(self):
        print("")
        print(colorama.Fore.BLACK+"Submeniu pentru optiunile de raportare a anumitor clienti")
        print(colorama.Fore.GREEN)
        print("1. Vezi clientii care au carti inchiriate ordonati dupa nume.")
        print("2. Vezi clientii care au carti inchiriate ordonati dupa numarul de carti inchiriate.")
        print("3. Vezi primii 20 la suta cei mai activi clienti.")
        print("Scrie exit pentru a iesi din aplicatie.\n")
    
    def __ui_books_reports(self):
        print("")
        print(colorama.Fore.BLACK+"Submeniu pentru optiunile de raportare a anumitor clienti")
        print(colorama.Fore.GREEN)
        print("1. Vezi care sunt cele mai inchiriate carti.")
        print("2. Vezi care este top 3 cele mai inchiriate carti.")
        print("Scrie exit pentru a iesi din aplicatie.\n")

    #UI_CLIENTI
    def __ui_add_client(self):
        try:
            id_client = int(input("Introdu ID-ul clientului: "))
        except ValueError:
            print("ID client invalid!\n")
            return
        nume = input("Introdu numele clientului: ").strip()
        cnp = input("Introdu CNP-ul clientului: ").strip()
        try:
            self.__client_service.adauga_client(id_client, nume, cnp)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)
            return
        print("Client adaugat!\n")

    def __ui_show_clients(self):
        for cont_client in self.__client_service.get_repository_client().get_repository():
            print(cont_client)

    def __ui_rent_a_book(self, cont):
        self.__ui_show_books()
        try:
            id_carte = int(input("Introdu ID-ul cartii pe care doreste clientul sa o inchirieze: "))
        except ValueError:
            print("id_invalid")
            return
        try:
            carte = self.__book_service.get_book_by_id(id_carte)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)
            return
        try:
            self.__client_service.rent_book(cont, carte)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)
            return

    def __ui_return_book(self, cont):
        try:
            id_carte = int(input("Introdu ID-ul cartii pe care doreste clientul sa o returneze: "))
        except ValueError:
            print("id_invalid")
            return
        try:
            book = self.__book_service.get_book_by_id(id_carte)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)
            return
        try:
            self.__client_service.return_a_book(cont, book)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)
            return

    def __ui_modify_client_data(self, cont):
        
        self.__ui_modify_client_options()
        cmd = input(">>> ")
        if cmd == "1":
            id = int(input("Introduceti id-ul nou: "))
            try:
                self.__client_service.modify_client_id(cont, id)
            except Exception as ex:
                print(colorama.Fore.RED)
                print(ex)
                return
            print("ID actualizat cu succes!\n")
        elif cmd == "2":
            nume = input("Introduceti numele nou: ").strip()
            try:
                self.__client_service.modificare_nume_client(cont, nume)
            except Exception as ex:
                print(colorama.Fore.RED)
                print(ex)
                return
            print("Nume actualizat cu succes!\n")
        elif cmd == "3":
            cnp = input("Introduceti cnp-ul nou: ").strip()
            try:
                self.__client_service.modificare_cnp_client(cont, cnp)
            except Exception as ex:
                print(colorama.Fore.RED)
                print(ex)
                return
            print("CNP actualizat cu succes!\n")
        elif cmd == "exit":
            return
        else:
            print("comanda invalida!\n")
            return

    def __ui_account__access(self):
        try:
            id_cont = int(input("ID cont: "))
        except ValueError:
            print("ID cont invalid!\n")
            return
        try:
            cont = self.__client_service.get_client_by_id(id_cont)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)
            return
        print(cont)
        while True:
            self.__ui_account_options()
            cmd = input(">>> ")
            if cmd == "1":
                self.__ui_rent_a_book(cont)
            elif cmd == "2":
                self.__ui_return_book(cont)
            elif cmd == "3":
                self.__ui_modify_client_data(cont)
            elif cmd == "4":
                resp = input("Esti sigur ca doresti sa stergi clientul? Raspunde cu da sau nu.\n")
                if resp == "da":
                    self.__client_service.delete_client(id_cont)
                    return
                elif resp == "nu":
                    cmd = "nu"
                else:
                    print(colorama.Fore.RED+"Introdu o comanda valida!")
                return
            elif cmd == "exit":
                return
            else:
                print(colorama.Fore.RED+"Introdu o comanda valida!")

    def __search_for_clients(self):
       
        while True:
            self.__ui_search_for_clients()
            cmd = input(">>> ")
            if cmd == "1":
                id = int(input("Introdu id-ul pentru a gasi clientul dorit: "))
                try:
                    print(self.__client_service.search_client(id,0))
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)
                    
            elif cmd == "2":
                cnp = input("Introduceti CNP-ul clientului pe care doresti sa il gasesti: ").strip()
                try:
                    print(self.__client_service.search_client(cnp, 1))
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)

            elif cmd == "3":
                name = input("Introduceti numele clientirlor pe care doresti sa ii gasesti: ").strip()
                try:
                    local_clients = []
                    local_clients = self.__client_service.search_client(name, 2)
                    for clients in range(0, len(local_clients)):
                        print(self.__client_service.get_client_by_id(local_clients[clients]))
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)

            elif cmd == "exit":
                return

            else:
                print(colorama.Fore.RED+"Introdu o comanda valida!")
    
    def __clients_report(self):
        while True:
            self.__ui_clients_reports()
            cmd = input(">>> ")

            if cmd == "1":
                try:
                    reported_clients = self.__client_service.reported_clients(1)
                    for i in range(0,len(reported_clients)):
                        print(reported_clients[i])
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)

            elif cmd == "2":
                try:
                    reported_clients = self.__client_service.reported_clients(2)
                    for i in range(0, len(reported_clients)):
                        print(reported_clients[i])
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)

            elif cmd == "3":
                try:
                    reported_clients = self.__client_service.reported_clients(3)
                    for i in range(0, len(reported_clients)):
                        print(reported_clients[i])
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)
            
            elif cmd == "exit":
                return

            else:
                print(colorama.Fore.RED+"Introdu o comanda valida!")

    def __ui_clients(self):
        while True:
            self.__ui_clients_options()
            cmd = input(">>>")
            if cmd == "1":
                self.__ui_add_client()
            elif cmd == "2":
                self.__ui_show_clients()
            elif cmd == "3":
                self.__ui_account__access()
            elif cmd == "4":
                self.__search_for_clients()
            elif cmd == "5":
                self.__clients_report()
            elif cmd == "exit":
                return

    #UI_CARTI
    def __ui_add_book(self):
        try:
            id_carte = int(input("Introdu ID-ul cartii: "))
        except ValueError:
            print("ID carte invalid!\n")
            return
        titlu = input("Introdu titlul cartii: ").strip()
        autor = input("Introdu numele autorului: ").strip()
        descriere = input("Introdu o descriere: ").strip()
        try:
            numar_exemplare = int(input("Introdu numarul de exemplare: "))
        except ValueError:
            print("Numar exemplare invalid!\n")
            return
        try:
            self.__book_service.add_book(id_carte, titlu, descriere, autor, numar_exemplare)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)
            return
        print("Carte adaugata!\n")

    def __ui_show_books(self):
        for exemplar in self.__book_service.get_book_repo().get_repository():
            print(exemplar)

    def __modify_book_data(self, book):

        '''
        Functia __modify_book_data(self, book) are rolul de a modifica datele unei carti book din biblioteca.
        '''
        
        self.__ui_modify_book_data()
        cmd = input(">>> ")

        if cmd == "1":
            new_id = int(input("Introduceti noul id: "))
            try:
                self.__book_service.modify_book_id(book, new_id)
            except Exception as ex:
                print(colorama.Fore.RED)
                print(ex)
                return
            print("ID-ul cartii actualizat cu succes!\n")
        elif cmd == "2":
            new_title = input("Introduceti noul titlu: ").strip()
            try:
                self.__book_service.modify_book_title(book, new_title)
            except Exception as ex:
                print(colorama.Fore.RED)
                print(ex)
                return
            print("Titlul cartii a fost actualizat cu succes!\n")
        elif cmd == "3":
            new_author = input("Introduceti noul autor: ").strip()
            try:
                self.__book_service.modify_book_author(book, new_author)
            except Exception as ex:
                print(colorama.Fore.RED)
                print(ex)
                return
            print("Autorul cartii a fost actualizat cu succes!\n")
        elif cmd == "4":
            new_description = input("Introduceti noua descriere: ").strip()
            try:
                self.__book_service.modify_book_description(book, new_description)
            except Exception as ex:
                print(colorama.Fore.RED)
                print(ex)
                return
        elif cmd == "exit":
                return
        else:
            print(colorama.Fore.RED)
            print("Introdu o comanda valida!")

    def __ui_access_book(self):

        '''
        Functia __ui_access_book(self) are rolul de a accesa datele unei carti pentru a aduga exemplare, de a sterge cartea sau de a modifica date.
        '''

        try:
            book_id = int(input("ID carte: "))
        except ValueError:
            print("ID carte invalid!\n")
            return
        try:
            book = self.__book_service.get_book_by_id(book_id)
        except Exception as ex:
            print(colorama.Fore.RED)
            print(ex)
            return
        print(book)
        while True:
            self.__ui_book_options()
            cmd = input(">>>")
            if cmd == "1":
                resp = input("Esti sigur ca doresti sa stergi cartea? Raspunde cu da sau nu.\n")
                if resp == "da":
                    self.__book_service.delete_book(book_id)
                    return
                elif resp == "nu":
                    cmd = ""
                else:
                    print(colorama.Fore.RED)
                    print("Introdu o comanda valida!")
            elif cmd == "2":
                self.__modify_book_data(book)
            elif cmd == "exit":
                return
            else:
                print(colorama.Fore.RED)
                print("Introdu o comanda valida!")

    def __ui_max_book_title(self):
        
        print(colorama.Fore.BLUE+"Cartea cu titlul maxim este:\n")

        local_books = self.__book_service.get_book_repo().get_repository()
        first_book = local_books[0]
        max_book = self.__book_service.max_book_title(1, first_book)

        for copy in self.__book_service.get_book_repo().get_repository():
            if copy == max_book:
                print(copy)
    
    def __search_for_books(self):

        '''
        Functia __search_for_books(self) are rolul de a cauta si afisa carti din biblioteca dupa anumite criterii precum id, titlu sau autor.
        '''
        
        while True:
            self.__ui_search_for_books()
            cmd = input(">>> ")
            if cmd == "1":
                id = int(input("Introdu id-ul pentru a gasi cartea aferenta: "))
                try:
                    print(self.__book_service.search_book(id,0))
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)
                    
            elif cmd == "2":
                title = input("Introduceti titlul cartilor pe care vrei sa le gasesti: ").strip()
                try:
                    local_books = []
                    local_books = self.__book_service.search_book(title, 1)
                    for books in range(0, len(local_books)):
                        print(self.__book_service.get_book_by_id(local_books[books]))
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)

            elif cmd == "3":
                author = input("Introdu autorul cartilor pe care doresti sa le gasesti: ").strip()
                try:
                    local_books = []
                    local_books = self.__book_service.search_book(author, 2)
                    for books in range(0, len(local_books)):
                        print(self.__book_service.get_book_by_id(local_books[books]))
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)

            elif cmd == "exit":
                return

            else:
                print(colorama.Fore.RED+"Introdu o comanda valida!")
    
    def __books_reports(self):

        while True:
            self.__ui_books_reports()
            cmd = input(">>> ")
            if cmd == "1":
                try:
                    reported_books = self.__book_service.books_reports(1)
                    for i in range(0,len(reported_books)):
                        print("Cartea a fost inchiriata de " + str(reported_books[i].get_rents()) + " ori.")
                        print(reported_books[i])
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)
            
            elif cmd == "2":
                try:
                    reported_books = self.__book_service.books_reports(2)
                    if len(reported_books) < 3:
                        print("Sunt mai putin de 3 carti care au fost inchiriate, iar topul lor este: \n")
                    for i in range(0,len(reported_books)):
                        print("Cartea a fost inchiriata de "+str(reported_books[i].get_rents())+" ori.")
                        print(reported_books[i])
                except Exception as ex:
                    print(colorama.Fore.RED)
                    print(ex)

            elif cmd == "exit":
                return

            else:
                print(colorama.Fore.RED+"Introdu o comanda valida!")

    def __ui_books(self):

        '''
        Functia __ui_books(self) are rolul de a actiona cu biblioteca in scopul adaugarii noilor carti, afisarii cartilor actuale, accesarea uneia, afisarea cartii cu numele cel mai lung sau de a cauta carti in biblioteca dupa anumite criterii.
        '''

        while True:
            self.__ui_books_options()
            cmd = input(">>>")
            if cmd == "1":
                self.__ui_add_book()
            elif cmd == "2":
                self.__ui_show_books()
            elif cmd == "3":
                self.__ui_access_book()
            elif cmd == "4":
                self.__ui_max_book_title()
            elif cmd == "5":
                self.__search_for_books()
            elif cmd == "6":
                self.__books_reports()
            elif cmd == "exit":
                return

    #random
    def __random_clients(self):
        
        n = int(input("Introdu cati clienti doresti sa fie introdusi la intamplare in lista: "))
        self.__client_service.clients_random(n, 0)
        self.__ui_show_clients()


    #main run
    def run(self):
        while True:
            self.__ui_general_options()
            cmd = input(">>>")
            if cmd == "1":
                self.__ui_clients()
            elif cmd == "2":
                self.__ui_books()
            elif cmd == "3":
                self.__random_clients()
            elif cmd == "exit":
                print(colorama.Fore.GREEN+"Multumesc pentru utilizare.\n")
                return