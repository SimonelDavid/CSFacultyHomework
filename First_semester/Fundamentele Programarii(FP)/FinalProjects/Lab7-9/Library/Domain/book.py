class Book():

    '''
    Clasa Book() creeaza obiecte de tip Book()
    '''

    numar_carti = 0

    #Constructor
    def __init__(self, id_Book, titlu, descriere, autor):
        Book.numar_carti += 1
        self.__id_Book = id_Book
        self.__titlu = titlu
        self.__descriere = descriere
        self.__autor = autor

    def get_book_id(self):
        return self.__id_Book

    def get_titlu(self):
        return self.__titlu

    def get_descriere(self):
        return self.__descriere

    def get_autor(self):
        return self.__autor

    def set_book_id(self, book_id):
        self.__id_Book = book_id
    
    def set_title(self, title):
        self.__titlu = title
    
    def set_description(self, description):
        self.__descriere = description
    
    def set_author(self, author):
        self.__autor = author

    def __eq__(self, other):
        return self.__autor == other.get_autor() and self.__titlu == other.get_titlu() and self.__descriere == other.get_descriere() and self.__id_Book == other.get_book_id()

    def __str__(self):
        s = ""
        s += "[ID]: " + str(self.__id_Book) + " | "
        s += "[TITLU]: " + str(self.__titlu) + " | "
        s += "[AUTOR]: " + str(self.__autor)
        return s


class Copies():
    '''
        Clasa Copies() asociaza obiectelor de tip Book() numarul Copiilor
        de acel tip pentru fiecare instanta in parte
    '''

    def __init__(self, Book, numar_Copies):
        self.__Book = Book
        self.__numar_Copies = numar_Copies
        self.__inchirieri = 0

    def get_book(self):
        return self.__Book

    def get_Copies_number(self):
        return self.__numar_Copies

    def add_copies(self, numar):
        self.__numar_Copies += numar

    def sub_copies(self, numar):
        self.__numar_Copies -= numar
    
    def set_copies(self, numar):
        self.__numar_Copies = numar

    def get_rents(self):
        return self.__inchirieri

    def set_rents(self, rents):
        self.__inchirieri = rents

    def add_rents(self):
        '''
        Atunci cand cartea este inchiriata, se creste contorul
        :return:
        '''
        self.__inchirieri += 1

    def __str__(self):
        s = ""
        s += "ID-ul cartii este: " + str(self.__Book.get_book_id()) + "\n"
        s += "Titlul cartii este: " + self.__Book.get_titlu() + "\n"
        s += "Descrierea cartii este: " + self.__Book.get_descriere() + "\n"
        s += "Autorul cartii este: " + self.__Book.get_autor() + "\n"
        s += "Numarul exemplarelor disponibile este: " + str(self.__numar_Copies) + "\n"
        return s

    def __eq__(self, other):
        return self.__Book == other.get_book() and self.__numar_Copies == other.get_Copies_number()