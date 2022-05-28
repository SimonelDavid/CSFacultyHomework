from Repository.book_repo import RepoBookCopies
from Domain.book import Copies, Book

class BookRepoFile(RepoBookCopies):

    """
      Responsible with the load/add_exemplar of books from/into a text file
      Include different version of:
           reading from the file
           accessing base class attributes (fields/methods)
    """

    def __init__(self, fileName):
        RepoBookCopies.__init__(self)
        self.__fileName = fileName
        # self.__loadFromFile()
        self.__loadFromFile()
    
    def __createBookFromLine(self, line):
        """
        Process the a line from the file and create a book
        return student
        """
        fields = line.split(" | ")
        book = Copies(Book(int(fields[0]), fields[1], fields[2], fields[3]), int(fields[4]))
        book.set_rents(int(fields[5]))
        return book

    def __loadFromFile(self):
        """
          Load book from file
          process file line by line
        """
        fh = open(self.__fileName)
        for line in fh:
            if line.strip()=="":
                continue
            book = self.__createBookFromLine(line)
            RepoBookCopies.add_exemplar(self, book)
        fh.close()

    def __loadFromFile2(self):
        """
         Load book from file
         Load file at once
        """
        fh = open(self.__fileName)
        for line in fh:
            if line.strip() == "":
                continue
            while line != "":
                local_id = int(line)
                line = fh.readline().strip("\n")
                title = line
                line = fh.readline().strip("\n")
                description = line
                line = fh.readline().strip("\n")
                author = line
                line = fh.readline().strip("\n")
                nr_copies = int(line)
                line = fh.readline().strip("\n")
                rents = int(line)
                book = Copies(Book(local_id, title, description, author), nr_copies)
                RepoBookCopies.add_exemplar(self, book)
                book.set_rents(rents)
                line = fh.readline().strip("\n")
        fh.close()
        
    def add_exemplar(self, book):
        RepoBookCopies.add_exemplar(self, book)
        self.__appendToFile(book)

    def __appendToFile(self,book):
        """
          Append a new line in the file representing the student st
        """
        fh = open(self.__fileName,"a")
        # line = str(book.get_book().get_book_id())+"\n"+book.get_book().get_titlu()+"\n"+book.get_book().get_descriere()+"\n"+book.get_book().get_autor()+"\n"+str(book.get_Copies_number())+"\n"+str(book.get_rents())+"\n"
        line = str(book.get_book().get_book_id()) + " | " + book.get_book().get_titlu() + " | " + book.get_book().get_descriere() + " | " + book.get_book().get_autor() + " | " + str(book.get_Copies_number()) + " | " + str(book.get_rents())
        fh.write("\n")
        fh.write(line)
        fh.close()

    def clear_line(self, id_client):

        with open(self.__fileName, 'r') as fh:
            lines = fh.readlines()

        for i in range(0, len(lines)):
            line = lines[i]
            fields = line.split(" | ")
            if line != '\n' and int(fields[0]) == id_client:
                del lines[i]
                break

        new_fh = open(self.__fileName, "w+")
        for new_line in lines:
            new_fh.write(new_line)

        new_fh.close()

    def modify_line(self, copies):

        fh = open(self.__fileName, "r")
        list_of_lines = fh.readlines()

        for i in range(0, len(list_of_lines)):
            line = list_of_lines[i]
            if line != '\n':
                if int(line[0]) == copies.get_book().get_book_id():
                    list_of_lines[i] = str(copies.get_book().get_book_id())+" | "+copies.get_book().get_titlu()+" | "+copies.get_book().get_descriere()+" | "+copies.get_book().get_autor()+" | "+str(copies.get_Copies_number())+" | "+str(copies.get_rents())+'\n'
                    # list_of_lines[i] = str(copies.get_book().get_book_id()) + "\n" + copies.get_book().get_titlu() + "\n" + copies.get_book().get_descriere() + "\n" + copies.get_book().get_autor() + "\n" + str(copies.get_Copies_number()) + "\n" + str(copies.get_rents()) + '\n'

        fh = open(self.__fileName, "w")
        fh.writelines(list_of_lines)
        fh.close()
