import random
import string

class ServiceClient():

    #Conctructor
    def __init__(self, validator_client, repository_client, book_repo_file, testing):
        self.__validator_client = validator_client
        self.__repository_client = repository_client
        self.__book_repo = book_repo_file
        self.__testing = testing

    def adauga_client(self, id_client, nume, cnp):
        '''
        Functia adauga un client nou in repository
        :param id_client: numar natural nenul
        :param nume: string nevid
        :param cnp: string nevid, contine doar cifre
        :return: -
        :raises - "id client invalid!\n" daca id_client este invalid
                - "nume invalid!\n" daca nume este invalid
                - "cnp invalid!\n" daca cnp este invalid
                - "id deja existent!\n" daca id-ul apare deja in repository
                - "cnp deja existent!\n" daca cnp-ul apare deja in repository
        '''
        #validare ca datele sa fie corecte
        self.__validator_client.validare_date_client(id_client, nume, cnp)
        #validare unicitate
        self.__validator_client.validare_unicitate(self.__repository_client, cnp, id_client)
        self.__repository_client.add_cont(self.__repository_client.creare_cont_nou(id_client, nume, cnp))
    
    def delete_client(self, id_client):
        local_clients = []
        local_clients = self.get_repository_client().get_repository()

        if len(local_clients) == 0:
            raise Exception("Nu sunt carti introduse.")
        else:
            for i in range(0, len(local_clients)):
                if local_clients[i].get_client().get_id_client() == id_client:
                    self.__repository_client.delete_cont(i)
                    self.__repository_client.clear_line(id_client)
                    return
        raise Exception("ID-ul introdus nu este unul corespondent cu una din cartile din biblioteca.")

    def get_client_by_id(self, id_client):
        '''
        Functia returneaza contul clientului cu id-ul id_client din repository-ul clientilor
        :param id_client: numar natural nenul
        :return: ContClient() cu id-ul id_client
        :raises Exception: "id inexistent!\n", daca id_client nu exista in lista clientilor
        '''
        self.__validator_client.validare_id_client(id_client)
        return self.__repository_client.get_cont_by_id(id_client)
        
    
    def modify_client_id(self, cont, id_nou):
        '''
        Functia modifica id-ul contului cont cu id_nou
        :param cont:- obiect de tipul ContClient()
        :param id_nou: intreg nevid
        :return: -
        :raises Exception: "id client invalid!\n", daca numele introdus e vid
        '''
        self.__validator_client.validare_id_client(id_nou)
        cont.get_client().set_id_client(id_nou)
        if self.__testing == 0:
            self.__repository_client.modify_line(cont)

    def modificare_nume_client(self, cont, nume_nou):
        '''
        Functia modifica numele contului cont cu nume_nou
        :param cont:- obiect de tipul ContClient()
        :param nume_nou: string nevid
        :return: -
        :raises Exception: "nume invalid!\n", daca numele introdus e vid
        '''
        self.__validator_client.validare_nume_client(nume_nou)
        cont.get_client().set_nume(nume_nou)
        if self.__testing == 0:
            self.__repository_client.modify_line(cont)

    def modificare_cnp_client(self, cont, cnp_nou):
        '''
        Functia modifica cnp-ul contului cont cu cnp_nou
        :param cont: - obiect de tipul ContClient()
        :param cnp_nou: string nevid, contine doar cifre
        :return:  -
        :raises Exception: "cnp invalid!\n", daca cnp-ul este vid sau contine caractere diferite de cifre
                           "cnp-ul exista deja!\n", daca cnp_nou apare deja asupra altui cont
        '''
        self.__validator_client.validare_cnp_client(self.__repository_client, cnp_nou)
        cont.get_client().set_cnp(cnp_nou)
        if self.__testing == 0:
            self.__repository_client.modify_line(cont)

    def rent_book(self, cont_client, carte):
        '''
        Functia atribuie cartea carte catre cont_client
        :param cont_client: obiect de tipul ContClient()
        :param carte: obiect de tipul Exemplare()
        :return: -
        :raises Exception: - "carte indisponibila!\n" daca cartea carte are 0 exemplare disponibile
                           - "clientul are deja cartea!\n" daca cartea se regaseste in lista clientului de carti
        '''

        if carte.get_book() in cont_client.get_carti_inchiriate():
            raise Exception("clientul are deja cartea!\n")
        if carte.get_Copies_number() == 0:
            raise Exception("carte indisponibila!\n")
        cont_client.add_book(carte.get_book())
        carte.sub_copies(1)
        carte.add_rents()
        if self.__testing == 0:
            self.__repository_client.modify_line(cont_client)
            self.__book_repo.modify_line(carte)
    
    def return_a_book(self, account, book):

        '''
            Functia return_a_book(slef, account, book) are rolul de a efectua operatia de returnare a unei carti pe care un client o realizeaza.

            Se va cauta mai intati daca acea carte dorita de a fi returnata, clientul a inchiriat-o sau nu, apoi daca este inchiriata aceasta va fi stearsa din contul lui si va fi incrementat numarul de exemplare al acelei carti din biblioteca.

            Date de intrare: account - string
                             book - string
        '''

        if book.get_book() not in account.get_carti_inchiriate():
            raise Exception("Clientul nu are aceasta carte inchiriata!\n")
        rented_books = []
        rented_books = account.get_carti_inchiriate()
        i = 0
        while i<len(rented_books):
            if rented_books[i].get_book_id() == book.get_book().get_book_id():
                account.delete_book(i)
                i = len(rented_books)
                book.add_copies(1)
            i = i+1
        if self.__testing == 0:
            self.__repository_client.modify_line(account)
            self.__book_repo.modify_line(book)

    def search_client(self, criteria, mode):

        '''
            Functia search_client(self, criteria, mode) are rolul de a cauta clienti in lista de clienti dupa anumite crietrii. 
            Date de intrare: criteria - string
                             mode - intt
                            Daca mode = 0: va fi cautat un anume client dupa id => criteria = id.
                            Daca mode = 1: va fi cautat un anume client dupa cnp => criteria = cnp.
                            Daca mode = 2: vor fi cautati anumiti clienti dupa nume => criteria = nume.
            :return: lista de obiecte.
        '''

        local_clients = []
        local_clients = self.get_repository_client().get_repository()
        if mode == 0:
            if len(local_clients) == 0:
                raise Exception("Nu sunt clienti introdusi.")
            else:
                for i in range(0,len(local_clients)):
                    if local_clients[i].get_client().get_id_client() == criteria:
                        return local_clients[i]
                raise Exception("ID-ul introdus nu este unul corespondent unui client inregistrat.")
        elif mode == 1:
            if len(local_clients) == 0:
                raise Exception("Nu sunt clienti introdusi.")
            else:
                for i in range(0,len(local_clients)):
                    if local_clients[i].get_client().get_cnp() == criteria:
                        return local_clients[i]
                raise Exception("CNP-ul introdus nu este unul corespondent unui client inregistrat.")
        elif mode == 2:
            if len(local_clients) == 0:
                raise Exception("Nu sunt clienti introdusi.")
            else:
                searched_clients = []

                for i in range(0,len(local_clients)):
                    if local_clients[i].get_client().get_nume() == criteria:
                        searched_clients.append(local_clients[i].get_client().get_id_client())
                if len(local_clients) == 0:
                    raise Exception("Numele introdus nu este unul corespondent unui client inregistrat.")
                else:
                    return searched_clients

    def get_validator_client(self):
        return self.__validator_client

    def get_repository_client(self):
        return self.__repository_client
    
    def get_number_of_clients(self):
        i = 0
        for client in self.__repository_client.get_repository():
            i = i+1
        
        return i
    
    def specific_string(self,length):  
        sample_string = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqerstuvwxyz' 
        result = ''.join((random.choice(sample_string)) for x in range(length))  
        return result  

    def clients_random(self, n, i=0):

        '''
            Functia clients_random(self,i,n) are rolul de a aduga in repository clienti la intamplare.
        '''

        if i < n:
            j = 0
            id = 0
            name = ""
            x = 0
            cnp = 0
            try:
                id = random.randint(1, 100)
                self.__validator_client.validare_id_client(id)
                j = j + 1
            except Exception as ex:
                j = 0

            try:
                x = random.randint(10, 35)
                name = self.specific_string(x)
                self.__validator_client.validare_nume_client(name)
                j = j + 1
            except Exception as ex:
                j = 0

            try:
                cnp1 = random.randint(1000000000000, 9999999999999)
                cnp = str(cnp1)
                self.__validator_client.validare_cnp_client(self.__repository_client, cnp)
                j = j + 1
            except Exception as ex:
                j = 0

            if j == 3:
                try:
                    self.adauga_client(id, name, cnp)
                    self.clients_random(n, i + 1)
                except Exception as ex:
                    self.clients_random(n, i - 1)
        elif i >= n:
            return
    """
        i = 0
        
        while i<n:
            j = 0
            id = 0
            name = ""
            x = 0
            cnp = 0
            try:
                id = random.randint(1,100)
                self.__validator_client.validare_id_client(id)
                j = j+1
            except Exception as ex:
                j = 0

            try:
                x = random.randint(10,35)
                name = self.specific_string(x)
                self.__validator_client.validare_nume_client(name)
                j = j+1
            except Exception as ex:
                j = 0

            try:
                cnp1 = random.randint(1000000000000,9999999999999)
                cnp = str(cnp1)
                self.__validator_client.validare_cnp_client(self.__repository_client,cnp)
                j = j+1
            except Exception as ex:
                j = 0
            
            if j == 3:
                try:
                    i = i+1
                    self.adauga_client(id,name,cnp)
                except Exception as ex:
                    i = i-1
    """

    def insertion_sort(self, key, start, end, l):

        """
            Functia insertion_sort(self, lista) are rolul de a sorta lista l.
            l - lista de elemente
            La finalul executiei lista l va fi sortata crescator.
        """

        i = start
        while i < end:
            j = i - 1
            while j >= 0 and key < l[j]:
                l[j + 1] = l[j]
                j -= 1
            l[j + 1] = key
            i = i +1
            if i < end:
                key = l[i]

    def getNextGap(self, gap):

        # Se micsoreaza gapul cu un factor de micsorare.
        gap = (gap * 10) / 13
        if gap < 1:
            return 1
        return int(gap)

    def comb_sort(self, start, end, l):

        """
            Functia comb_sort(self, lista) are rolul de a sorta lista l.
            l - lista de elemente
            La finalul executiei lista l va fi sortata crescator.
        """

        # Initializeaza gap-ul.
        gap = end

        # Initializam swapped cu True ca sa ne asiguram ca bucla va functiona.
        swapped = True

        # Instructiunea while va functiona pana cand gap-ul este mai mare decat 1.
        # Instructiunea while va functiona pana cand pana la ultima iteratie care cauzeaza un swap.
        while gap != 1 or swapped == 1:

            # Cauta urmatorul gap
            gap = self.getNextGap(gap)

            # Initializam swapped cu False ca sa putem verifica daca swap-ul s-a efectuat sau nu.
            swapped = False

            # Comparam elementele cu gap-ul curent.
            i = start
            while i< end-gap:
                if l[i] > l[i + gap]:
                    l[i], l[i + gap] = l[i + gap], l[i]
                    swapped = True
                i = i+1

    def order_by_name(self):
        local_clients = self.get_repository_client().get_repository().copy()
        sorted_list = []

        for i in range(0, len(local_clients)):
            if len(local_clients[i].get_carti_inchiriate()) > 0:
                sorted_list.append(local_clients[i].get_client().get_nume())

        reported_clients = []
        self.insertion_sort(sorted_list[0], 0, len(sorted_list), sorted_list)
        i = 0
        j = 0
        while i < len(sorted_list) and j < len(sorted_list):
            if sorted_list[j] == local_clients[i].get_client().get_nume():
                reported_clients.append(local_clients[i])
                j = j+1
                i = -1
            i = i+1

        return reported_clients

    def order_by_number_of_rents(self):

        local_clients = self.get_repository_client().get_repository().copy()
        sorted_list = []
        second_sorted = []

        for i in range(0, len(local_clients)):
            if len(local_clients[i].get_carti_inchiriate()) > 0:
                sorted_list.append(local_clients[i].get_numar_inchirieri_total())

        reported_clients = []
        self.comb_sort(0, len(sorted_list), sorted_list)
        second_sorted = self.order_by_name()
        i = 0
        j = 0
        while i < len(sorted_list) and j < len(sorted_list):
            if j == 0 and sorted_list[j] == second_sorted[i].get_numar_inchirieri_total():
                reported_clients.append(second_sorted[i])
                j = j + 1
                i = -1
            elif j>0 and sorted_list[j] == second_sorted[i].get_numar_inchirieri_total() and reported_clients[j-1].get_client().get_nume() != second_sorted[i].get_client().get_nume():
                reported_clients.append(second_sorted[i])
                j = j + 1
                i = -1
            i = i + 1

        return reported_clients

    def report_by_percentage(self):
        local_clients = self.get_repository_client().get_repository().copy()
        reported_clients = []

        n = round(0.2 * len(local_clients))
        i = 0
        max = local_clients[0].get_numar_inchirieri_total()

        while i < n:
            m = len(local_clients)
            for j in range(0, m):
                if local_clients[j].get_numar_inchirieri_total() > max:
                    max = local_clients[j].get_numar_inchirieri_total()

            j = 0

            while j < m and i < n:
                if local_clients[j].get_numar_inchirieri_total() == max:
                    reported_clients.append(local_clients[j])
                    del (local_clients[j])
                    i = i + 1
                    m = m - 1

                j = j + 1

        return reported_clients

    def reported_clients(self, mode):

        '''
            Functia reported_clients(self, mode) are rolul de a efectua cautari in lista de clienti si de a returna o lista specifica cerintei care ulterior va fi afisata in pachetul de ui.
            
            Date de intrare: mode - int 
                             daca mode = 1: se adauga in reported_clients, clientii care au carti inchiriate ordonati dupa nume.
                             daca mode = 2: se adauga in reported_clients, clientii care au carti inchiriate ordonati dupa numarul de carti inchiriate.
                             daca mode = 3: se vor afisa primii 20% clienti cu cele mai multe actiuni efectuate.
            
            :return: lista de obiecte.
        '''

        reported_clients = []

        if mode == 1:
            reported_clients = self.order_by_name()

        elif mode == 2:
            reported_clients = self.order_by_number_of_rents()

        elif mode == 3:
            reported_clients = self.report_by_percentage()

        if len(reported_clients) > 0:
            return reported_clients
        elif len(reported_clients) == 0:
            raise Exception("Nu exista clienti care sa aiba carti inchiriate pentru a realiza rapoarte.\n")