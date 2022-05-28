from Domain.client import ClientAccount, Client

class ConturiClientiRepository():
    '''
    Clasa ConturiClientiRepository retine obiecte de tip ClientAccount().
    Se ocupa de management-ul Conturilor: adaugare cont, modificare cont, stergere cont
    '''
    #Constructor
    def __init__(self):
        self.__conturi_clienti_repository = []
    
    def __len__(self):
        return len(self.__conturi_clienti_repository)

    def creare_cont_nou(self, id_client, nume, cnp):
        '''
        Functia primeste ca parametri numarul intreg pozitiv id_client, string-ul nenul nume
        si string-ul nenul format doar din cifre cnp si creeaza un cont nou cu aceste informatii
        :param id_client: numar intreg strict pozitiv
        :param nume: string nenul
        :param cnp: string nenul, contine doar cifre
        :return:
        '''
        return ClientAccount(Client(id_client, nume, cnp), 0, [])

    def get_repository(self):
        '''
        getter pentru parametrul __conturi_clienti_repository
        :return: self.__conturi_clienti_repository
        '''
        return self.__conturi_clienti_repository

    def add_cont(self, cont_client):
        '''
        Functia adauga in repository un cont nou
        :param cont_client: obiect de tipul ClientAccount()
        :return: -
        '''
        self.__conturi_clienti_repository.append(cont_client)

    def delete_cont(self, poz):
        '''
        Functia sterge obiectul de tip ClientAccount() de pe pozitia poz
        :param poz: numar intreg pozitiv
        :return: -
        '''
        del(self.__conturi_clienti_repository[poz])

    def get_cont_by_id(self, id_client):
        '''
        Functia cauta in repository clientul cu id-ul id_client si returneaza obiectul gasit
        Daca nu gaseste, functia returneaza eroare
        :param id_client: numar natural nenul
        :return: cont_client
        :raises Exception: "id inexistent!\n", daca id_client nu exista in lista clientilor
        '''
        for cont_client in self.__conturi_clienti_repository:
            if cont_client.get_client().get_id_client() == id_client: 
                return cont_client
        raise Exception("id inexistent!\n")