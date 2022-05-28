from Domain.book import Copies

class Client():
    '''
        Clasa Client() construieste obiecte de tip Client.
    '''

    # Constructorul
    def __init__(self, id_client, nume, cnp):
        self.__id_client = id_client
        self.__nume = nume
        self.__cnp = cnp

    def __eq__(self, other):
        return self.__id_client == other.get_id_client() and self.__cnp == other.get_cnp() and self.__nume == other.get_nume()

    def get_id_client(self):
        return self.__id_client

    def get_nume(self):
        return self.__nume

    def get_cnp(self):
        return self.__cnp

    def set_cnp(self, cnp):
        self.__cnp = cnp

    def set_id_client(self, id_client):
        self.__id_client = id_client

    def set_nume(self, nume):
        self.__nume = nume

class ClientAccount():

    '''
        Clasa ClientAccount() creeaza conturile clientilor de tip Client()
        Aici se monitorizeaza activitatea fiecarui client
    '''
    def __init__(self, client, nr_rents, books):
        self.__client = Client(client.get_id_client(), client.get_nume(), client.get_cnp())
        self.__numar_inchirieri_total = nr_rents
        self.__carti_inchiriate = books

    def __liste_egale(self, other):
        if len(self.__carti_inchiriate) != len(other.get_carti_inchiriate()): 
            return False

        for (c1, c2) in zip(self.__carti_inchiriate, other.get_carti_inchiriate()):
            if c1 != c2: 
                return False
                
        return True

    def __eq__(self, other):
        return self.__client == other.get_client() and self.__liste_egale(other) and self.__numar_inchirieri_total == other.get_numar_inchirieri_total()

    def __str__(self):
        s = ""
        s += "ID-ul clientului este: " + str(self.__client.get_id_client()) + "\n"
        s += "Numele clientului este: " + str(self.__client.get_nume()) + "\n"
        s += "CNP-ul clientului este: " + str(self.__client.get_cnp()) + "\n"
        s += "Numarul total al cartilor inchiriate de client: " + str(self.__numar_inchirieri_total)
        s += "\n"
        s += "Carti inchiriate: \n"
        for carte in self.__carti_inchiriate:
            s += str(carte) + "\n"
        return s

    def get_client(self):
        return self.__client

    def get_carti_inchiriate(self):
        return self.__carti_inchiriate

    def get_numar_inchirieri_total(self):
        return self.__numar_inchirieri_total
    
    def id_rented_books(self):
        list_of_id = []
        for book in self.__carti_inchiriate:
            list_of_id.append(str(book.get_book_id())+" ")
        
        return list_of_id

    def add_book(self, carte_object):
        '''

            Se adauga obiectul de tip Carte la finalul listei __carti_inchiriate

         :param carte_object:
         :return:
         '''
        self.__carti_inchiriate.append(carte_object)
        self.__numar_inchirieri_total += 1
    
    def delete_book(self, pozitie):
        '''

            Se sterge obiectul de tip Carte din __carti_inchiriate de la pozitia pozitie

         :param pozitie:
         :return:
         '''
        self.__numar_inchirieri_total -= 1
        del(self.__carti_inchiriate[pozitie])
