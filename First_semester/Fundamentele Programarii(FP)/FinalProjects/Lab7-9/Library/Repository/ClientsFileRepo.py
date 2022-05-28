from os import close
from Repository.client_repo import ConturiClientiRepository
from Repository.book_repo import RepoBookCopies
from Domain.client import ClientAccount, Client
from Domain.book import Copies

class ClientsRepoFile(ConturiClientiRepository):

    
    """
      Responsible with the load/add_exemplar of vlients from/into a text file
      Include different version of:
           reading from the file
           accessing base class attributes (fields/methods)
    """

    def __init__(self,fileName,book_repo):
        #invoke base class __init__ method
        ConturiClientiRepository.__init__(self)
        self.__fileName = fileName
        self.__book_repo = book_repo
        #load __students from the file
        self.__loadFromFile2()
    
    def __createClientFromLine(self, line):
        """
        Process the a line from the file and create a student
        return student
        """
        fields = line.split(" | ")
        list_of_id = []
        list_of_id_1 = []
        books = []
        list_of_id = list(fields[4].strip(" "))
        for i in range(0, len(list_of_id)):
            if i%2 == 0 and list_of_id[i] != '\n':
                list_of_id_1.append(int(list_of_id[i]))
        for i in list_of_id_1:
            books.append(self.__book_repo.get_book_by_id(i,2))
        client = ClientAccount(Client(int(fields[0]), fields[1], int(fields[2])), int(fields[3]), books)
        return client

    def __loadFromFile2(self):
        """
          Load __students from file
          process file line by line
        """
        fh = open(self.__fileName)
        for line in fh:
            if line.strip()=="":
                continue
            client = self.__createClientFromLine(line)
            ConturiClientiRepository.add_cont(self, client)
        fh.close()
        
    def add_cont(self, client):
        ConturiClientiRepository.add_cont(self, client)
        self.__appendToFile(client)

    def __appendToFile(self,client):
        """
          Append a new line in the file representing the client client
        """
        fh = open(self.__fileName,"a")
        line = str(client.get_client().get_id_client())+" | "+client.get_client().get_nume()+" | "+str(client.get_client().get_cnp())+" | "+str(client.get_numar_inchirieri_total())+" | "+" "
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
    
    def modify_line(self, ClientAccount):

        fh = open(self.__fileName, "r")
        list_of_lines = fh.readlines()

        for i in range(0, len(list_of_lines)):
            line = list_of_lines[i]
            if line != '\n':
                if int(line[0]) == ClientAccount.get_client().get_id_client():
                    if len(ClientAccount.get_carti_inchiriate()) > 0:
                        list_of_lines[i] = str(ClientAccount.get_client().get_id_client())+" | "+ClientAccount.get_client().get_nume()+" | "+str(ClientAccount.get_client().get_cnp())+" | "+str(ClientAccount.get_numar_inchirieri_total())+" |"
                        for book in ClientAccount.get_carti_inchiriate():
                            list_of_lines[i] = list_of_lines[i]+" "+str(book.get_book_id())
                    elif len(ClientAccount.get_carti_inchiriate()) == 0:
                        list_of_lines[i] = str(ClientAccount.get_client().get_id_client())+" | "+ClientAccount.get_client().get_nume()+" | "+str(ClientAccount.get_client().get_cnp())+" | "+str(ClientAccount.get_numar_inchirieri_total())+" | "+" "
                    list_of_lines[i] = list_of_lines[i]+'\n'

        fh = open(self.__fileName, "w")
        fh.writelines(list_of_lines)
        fh.close()