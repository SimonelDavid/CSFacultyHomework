class BookService():

    #Constructor
    def __init__(self, book_validator, book_repo, client_service, testing):
        self.__book_validator = book_validator
        self.__book_repo = book_repo
        self.__client_service = client_service
        self.__testing = testing

    def add_book(self, id_carte, titlu, descriere, autor, numar_exemplare):
        '''
        Functia adauga o carte noua in repository-ul cartilor
        :param id_carte: numar natural nenul
        :param titlu: string nevid
        :param descriere: string nevid
        :param autor: string nevid, contine doar litere
        :param numar_exemplare: numar natural
        :return:
        :raises Exception: "id carte invalid!\n" - daca id_carte este invalid
                           "titlu carte invalid!\n" - daca titlul cartii este invalid
                           "descriere carte invalida!\n" - daca descrierea cartii este invalida
                           "nume autor invalid!\n" - daca numele autorului este invalid
        '''
        self.__book_validator.book_data_validator(id_carte, titlu, descriere, autor)
        self.__book_validator.validare_unicitate(self.__book_repo, id_carte, titlu, autor)
        self.__book_repo.add_exemplar(self.__book_repo.creare_exemplar(id_carte, titlu, descriere, autor, numar_exemplare))
    
    def delete_book(self, id):

        local_books = []
        local_books = self.get_book_repo().get_repository()

        if len(local_books) == 0:
            raise Exception("Nu sunt carti introduse.")
        else:
            local_clients = []
            local_clients = self.__client_service.get_repository_client().get_repository()
            i = 0
            while i < len(local_clients):
                rented_books = []
                rented_books = local_clients[i].get_carti_inchiriate()
                if len(rented_books) > 0:
                    j = 0
                    while j < len(rented_books):
                        if rented_books[j].get_book_id() == id:
                            self.__client_service.return_a_book(local_clients[i], self.get_book_by_id(id))
                        j = j+1
                i = i+1

            for i in range(0,len(local_books)):
                if local_books[i].get_book().get_book_id() == id:
                    self.__book_repo.clear_line(local_books[i].get_book().get_book_id())
                    self.__book_repo.delete_exemplar(i)
                    return
        raise Exception("ID-ul introdus nu este unul corespondent cu una din cartile din biblioteca.")

    def max_book_title(self, i, max_book):
        '''
        Functia sorteaza repository-ul crescator dupa numarul de exemplare disponibile
        :return:
        '''

        """
        local_books = []
        local_books = self.get_book_repo().get_repository()
        max_book = local_books[0]

        for i in range (1, len(local_books)):
            if len(local_books[i].get_book().get_titlu()) >= len(max_book.get_book().get_titlu()):
                max_book = local_books[i]

        return max_book
        """

        local_books = self.get_book_repo().get_repository()

        if i < len(local_books):
            if len(max_book.get_book().get_titlu()) <= len(local_books[i].get_book().get_titlu()):
                return self.max_book_title(i + 1, local_books[i])
            else:
                return self.max_book_title(i + 1, max_book)
        else:
            return max_book


    def search_book(self, criteria, mode):

        '''
            Functia search_book(self, criteria, mode) are rolul de a cauta in lista de carti aflate in biblioteca, diverse carti dupa preferintele de cautare ale utilizatorului. 
            Daca doreste sa gaseasca o carte dupa id, mode va fi egal cu 0, daca doreste sa gaseasca mai multe carti dupa titlul cartii, atunci mode va fi 1, iar daca va dori sa caute carti dupa numele autorului mode va fi 3.
            :reutrn: obiect de tip self.get_book_repo().get_repository()
        '''

        local_books = []
        local_books = self.get_book_repo().get_repository()
        if mode == 0:
            if len(local_books) == 0:
                raise Exception("Nu sunt carti introduse.")
            else:
                for i in range(0,len(local_books)):
                    if local_books[i].get_book().get_book_id() == criteria:
                        return local_books[i]
            raise Exception("ID-ul introdus nu este unul corespondent cu una din cartile din biblioteca.")    
        elif mode == 1:
            if len(local_books) == 0:
                raise Exception("Nu sunt carti introduse.")
            else:
                searched_books = []
                for i in range(0,len(local_books)):
                    if local_books[i].get_book().get_titlu() == criteria:
                        searched_books.append(local_books[i].get_book().get_book_id())
                if len(searched_books) == 0:
                    raise Exception("Titlul introdus nu este unul corespondent uneia dintre cartile aflate in biblioteca.")
                else:
                    return searched_books
        elif mode == 2:
            if len(local_books) == 0:
                raise Exception("Nu sunt carti introduse.")
            else:
                searched_books = []
                for i in range(0,len(local_books)):
                    if local_books[i].get_book().get_autor() == criteria:
                        searched_books.append(local_books[i].get_book().get_book_id())
                if len(searched_books) == 0:
                    raise Exception("Titlul introdus nu este unul corespondent uneia dintre cartile aflate in biblioteca.")
                else:
                    return searched_books

    def get_book_by_id(self, id_carte):
        '''
        Functia returneaza, daca gaseste, cartea cu id-ul id_carte din repository
        :param id_carte: numar natural nenul
        :return: obiect de tip Exemplare(), daca este gasit
        :raises Exception: "id carte invalid!\n" daca id-ul <= 0
                           "id inexistent!\n" daca id-ul nu este gasit
        '''
        self.__book_validator.validare_id_carte(id_carte)
        return self.__book_repo.get_book_by_id(id_carte,1)

    def modify_book_id(self, book, new_id):
        '''
        Functia modifica id-ul cartii book cu new_id
        :param cont:- obiect de tipul Book()
        :param id_nou: intreg nevid
        :return: -
        :raises Exception: "id carte invalid!\n", daca id-ul introdus e negativ
        '''
        self.__book_validator.validare_id_carte(new_id)
        book.get_book().set_book_id(new_id)
        if self.__testing == 0:
            self.__book_repo.modify_line(book)

    def modify_book_title(self, book, new_title):
        '''
        Functia modifica titlului cartii book cu new_title
        :param cont:- obiect de tipul Book()
        :param id_nou: intreg nevid
        :return: -
        :raises Exception: "titlu carte invalid!\n", daca titlul introdus e vid
        '''
        self.__book_validator.book_title_validation(new_title)
        book.get_book().set_title(new_title)
        if self.__testing == 0:
            self.__book_repo.modify_line(book)
    
    def modify_book_author(self, book, new_author):
        '''
        Functia modifica autorul cartii book cu new_author
        :param cont:- obiect de tipul Book()
        :param id_nou: intreg nevid
        :return: -
        :raises Exception: "autor carte invalid!\n", daca autorul introdus e vid
        '''
        self.__book_validator.book_author_validation(new_author)
        book.get_book().set_author(new_author)
        if self.__testing == 0:
            self.__book_repo.modify_line(book)
    
    def modify_book_description(self, book, new_description):
        '''
        Functia modifica descrierea cartii book cu new_description
        :param cont:- obiect de tipul Book()
        :param id_nou: intreg nevid
        :return: -
        :raises Exception: "descriere carte invalida!\n", daca descrierea introdusa e vida
        '''
        self.__book_validator.book_description_validator(new_description)
        book.get_book().set_description(new_description)
        if self.__testing == 0:
            self.__book_repo.modify_line(book)

    def get_book_validator(self):
        return self.__book_validator


    def get_book_repo(self):
        return self.__book_repo

    def report_by_rents(self):
        local_books = self.get_book_repo().get_repository()
        reported_books = []

        if len(local_books) == 0:
            raise Exception("Nu sunt carti introduse.")
        else:
            max = local_books[0].get_rents()
            for i in range(0, len(local_books)):
                if local_books[i].get_rents() > 0 and local_books[i].get_rents() > max:
                    max = local_books[i].get_rents()

            for i in range(0, len(local_books)):
                if local_books[i].get_rents() > 0 and local_books[i].get_rents() == max:
                    reported_books.append(local_books[i])

        return reported_books

    def report_top_3(self):

        local_books = self.get_book_repo().get_repository()
        reported_books = []

        if len(local_books) == 0:
            raise Exception("Nu sunt carti introduse.")
        else:
            j = 0
            while j < 3:
                k = 0
                max = local_books[0].get_rents()
                for i in range(0, len(local_books)):
                    if local_books[i].get_rents() > 0 and local_books[i].get_rents() > max:
                        max = local_books[i].get_rents()
                    elif local_books[i].get_rents() == 0:
                        k = k + 1

                i = 0
                while i < len(local_books) and j < 3:
                    if local_books[i].get_rents() > 0 and local_books[i].get_rents() == max:
                        reported_books.append(local_books[i])
                        del (local_books[i])
                        j = j + 1
                    i = i + 1

                if k == len(local_books):
                    j = 3
        return reported_books

    def books_reports(self, mode):

        '''
            Functia books_reports(self, mode) are rolul de a efectua cautari in lista de carti si de a returna o lista specifica cerintei care ulterior va fi afisata in pachetul de ui.
            
            Date de intrare: mode - int 
                             daca mode = 1: se adauga in reported_books, cele mai inchiriate carti.
                             daca mode = 2: se vor aduga in reported_books, top 3 cele mai inchiriate carti.
                             
            :return: lista de obiecte.
        '''

        reported_books = []

        if mode == 1:
            reported_books = self.report_by_rents()
        
        elif mode == 2:
            reported_books = self.report_top_3()

        if len(reported_books) > 0:
            return reported_books
        elif len(reported_books) == 0:
            raise Exception("In biblioteca nu exista carti care sa fii fost cel putin odata inchiriate.\n")