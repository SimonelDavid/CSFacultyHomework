from Domain.book import Copies, Book


class RepoBookCopies():
    '''
    Clasa RepoBookCopies() se ocupa cu crearea repository-ului pentru obiecte de tip Copies()
    '''
    #Constructor
    def __init__(self):
        self.__Copies_carti_repository = []
    
    def __len__(self):
        return len(self.__Copies_carti_repository)

    def creare_exemplar(self, id_Book, titlu, descriere, autor, nr_Copies):
        return Copies(Book(id_Book, titlu, descriere, autor), nr_Copies)

    def get_repository(self):
        '''
        getter pentru __Copies_carti_repository
        :return: __Copies_carti_repository
        '''
        return self.__Copies_carti_repository

    def add_exemplar(self, Copies):
        '''
        Adauga un exemplar nou in repository
        :param Copies: obiect de tipul Copies()
        :return: -
        '''
        self.__Copies_carti_repository.append(Copies)

    def delete_exemplar(self, poz):
        '''
        Sterge exemplarul de pe pozitia poz
        :param poz: numar intreg nenul
        :return: -
        '''
        del(self.__Copies_carti_repository[poz])

    def get_book_by_id(self, id_Book, mode):
        '''
        Returneaza Booka din repository care are id-ul id_Book. Daca nu exista retunreaza eroare
        :return:
        :raises Exception: "id inexistent!\n" daca id_Book nu este gasit
        '''
        if mode == 1:
            for Book in self.__Copies_carti_repository:
                if Book.get_book().get_book_id() == id_Book: 
                    return Book
        elif mode == 2:
            for Book in self.__Copies_carti_repository:
                if Book.get_book().get_book_id() == id_Book: 
                    return Book.get_book()
        raise Exception("id inexistent!\n")