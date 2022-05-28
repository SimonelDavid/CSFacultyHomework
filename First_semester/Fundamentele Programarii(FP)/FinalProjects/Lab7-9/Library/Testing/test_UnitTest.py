import unittest

from Domain.client import Client, ClientAccount
from Domain.book import Book, Copies

from Repository.client_repo import ConturiClientiRepository
from Repository.book_repo import RepoBookCopies
from Repository.ClientsFileRepo import ClientsRepoFile
from Repository.BookFileRepo import BookRepoFile

from Validation.client_validator import ClientValidator
from Validation.book_validator import BookValidator

from Service.client_service import ServiceClient
from Service.book_service import BookService


class TestCaseClient(unittest.TestCase):

    # Client and ClientAccount tests
    def test_a_create_client(self):
        id_client = 1
        nume = "Pop Ion"
        cnp = "12345678"
        client1 = Client(id_client, nume, cnp)
        assert (client1.get_id_client() == id_client)
        assert (client1.get_nume() == nume)
        assert (client1.get_cnp() == cnp)

    def test_b_modify_client(self):
        client1 = Client(1, "Pop Ion", "1234567890123")
        client1.set_id_client(2)
        client1.set_nume("Matei")
        client1.set_cnp("1234567890123")
        assert (client1.get_id_client() == 2)
        assert (client1.get_nume() == "Matei")
        assert (client1.get_cnp() == "1234567890123")

    def test_c_client_eq(self):
        id_client = 1
        nume = "Pop Ion"
        cnp = "1234567890123"
        client1 = Client(id_client, nume, cnp)
        client2 = Client(1, "Pop Ion", "1234567890123")
        assert (client1 == client2)

    def test_d_account_client_eq(self):
        id_client = 1
        nume = "Pop Ion"
        cnp = "1234567890123"
        cont_client1 = ClientAccount(Client(id_client, nume, cnp), 0, [])
        cont_client2 = ClientAccount(Client(1, "Pop Ion", "1234567890123"), 0, [])
        cont_client1.add_book(Book(1, "Moara", "-", "Slavici"))
        cont_client2.add_book(Book(1, "Moara", "-", "Slavici"))
        assert (cont_client1 == cont_client2)

    def test_e_create_client_account(self):
        id_client = 1
        nume = "Pop Ion"
        cnp = "12345678"
        client1 = Client(id_client, nume, cnp)
        cont_client1 = ClientAccount(client1, 0, [])
        assert (cont_client1.get_client() == client1)
        assert (cont_client1.get_numar_inchirieri_total() == 0)
        assert (cont_client1.get_carti_inchiriate() == [])

    def test_f_delete_book_from_account(self):
        cont1 = ClientAccount(Client(1, "Andrei", "1234567890122"), 0, [])
        cont1.add_book(Book(1, "Moara", "pentru bac", "Slavici"))
        cont1.add_book(Book(2, "Baltagul", "roman", "Sadoveanu"))
        book1 = Book(1, "Moara", "pentru bac", "Slavici")
        book2 = Book(2, "Baltagul", "roman", "Sadoveanu")
        assert (cont1.get_carti_inchiriate() == [book1, book2])
        cont1.delete_book(0)
        assert (cont1.get_carti_inchiriate() == [book2])
        assert (cont1.get_numar_inchirieri_total() == 2)

    # Client validator test
    def test_g_client_validator(self):
        validator_client = ClientValidator()
        validator_client.validare_date_client(2, "Andrei", "1234567890123")
        validator_client.validare_date_client(100, "Marius", "1234567890123")
        try:
            validator_client.validare_date_client(-1, "Andrei", "1234567890123")
            assert False
        except Exception as ex:
            assert (str(ex) == "id client invalid!\n")

    def test_h_validate_unicity(self):
        validator_client = ClientValidator()
        repository_client = ConturiClientiRepository()
        repository_client.add_cont(ClientAccount(Client(1, "Andrei", "1234567890123"), 0, []))
        repository_client.add_cont(ClientAccount(Client(2, "Mihai", "1234567890123"), 0, []))
        validator_client.validare_unicitate(repository_client, "1111", "3")
        try:
            validator_client.validare_unicitate(repository_client, "1234567890123", 1)
            assert False
        except Exception as ex:
            assert (str(ex) == "id-ul exista deja!\ncnp-ul exista deja!\n")

        try:
            validator_client.validare_unicitate(repository_client, "1234567890123", 3)
            assert False
        except Exception as ex:
            assert (str(ex) == "cnp-ul exista deja!\n")

    def test_i_client_cnp_validator(self):
        client_repository = ConturiClientiRepository()
        client_validator = ClientValidator()

        client_repository.add_cont(ClientAccount(Client(1, "Andrei", "1234567890123"), 0, []))
        client_validator.validare_cnp_client(client_repository, "1234567890120")
        try:
            client_validator.validare_cnp_client(client_repository, "123AA45")
            assert False
        except Exception as ex:
            assert (str(ex) == "cnp invalid!\n")

        try:
            client_validator.validare_cnp_client(client_repository, "1234567890123")
            assert False
        except Exception as ex:
            assert (str(ex) == "cnp-ul exista deja!\n")

    # Test Clients Repository

    def test_j_clients_repo_accounts_files(self):
        book_repo = BookRepoFile("TestBooks.txt")
        repo_cont_client = ClientsRepoFile("TestClients.txt", book_repo)
        assert (repo_cont_client.get_repository() == [])
        cont_client1 = ClientAccount(Client(1, "Andrei", "1234567890123"), 0, [])
        cont_client2 = ClientAccount(Client(2, "Marius", "2341567890123"), 0, [])
        repo_cont_client.add_cont(cont_client1)
        assert repo_cont_client.__len__() == 1
        assert (repo_cont_client.get_repository() == [cont_client1])
        repo_cont_client.add_cont(cont_client2)
        assert repo_cont_client.__len__() == 2
        assert (repo_cont_client.get_repository() == [cont_client1, cont_client2])

    def test_k_clear_file(self):
        book_repo = BookRepoFile("TestBooks.txt")
        file_name = "TestClients.txt"
        repo_cont_client = ClientsRepoFile(file_name, book_repo)

        assert repo_cont_client.__len__() == 2

        repo_cont_client.clear_line(1)
        repo_cont_client.delete_cont(0)

        assert repo_cont_client.__len__() == 1

        repo_cont_client.clear_line(2)
        repo_cont_client.delete_cont(0)

        assert repo_cont_client.__len__() == 0

    def test_l_create_new_account(self):
        repo_cont = ConturiClientiRepository()
        assert(repo_cont.creare_cont_nou(1, "Andrei", "1234") == ClientAccount(Client(1, "Andrei", "1234"), 0, []))

    def test_m_get_account_by_id(self):
        repository_client = ConturiClientiRepository()
        cont_client1 = ClientAccount(Client(1, "Andrei", "1234"), 0, [])
        cont_client2 = ClientAccount(Client(2, "Mircea", "2345"), 0, [])
        cont_client3 = ClientAccount(Client(3, "Ana", "4352"), 0, [])
        repository_client.add_cont(cont_client1)
        repository_client.add_cont(cont_client2)
        repository_client.add_cont(cont_client3)
        assert (repository_client.get_cont_by_id(1) == cont_client1)
        assert (repository_client.get_cont_by_id(2) == cont_client2)
        try:
            repository_client.get_cont_by_id(5)
            assert False
        except Exception as ex:
            assert (str(ex) == "id inexistent!\n")

    # Client Service Tests
    def test_n_create_service_client(self):
        repository_client = ConturiClientiRepository()
        validator_client = ClientValidator()
        book_repo = RepoBookCopies()
        service_client = ServiceClient(validator_client, repository_client, book_repo, 1)
        assert (service_client.get_repository_client() == repository_client)
        assert (service_client.get_validator_client() == validator_client)

    def test_o_add_client(self):
        repository_client = ConturiClientiRepository()
        validator_client = ClientValidator()
        book_repo = RepoBookCopies()
        service_client = ServiceClient(validator_client, repository_client, book_repo, 1)
        assert (service_client.get_repository_client().get_repository() == [])
        service_client.adauga_client(1, "Andrei", "1234567890120")
        service_client.adauga_client(2, "Mihai", "1234567890123")
        try:
            service_client.adauga_client(-1, "Andrei", "cnp_invalid")
            assert False
        except Exception as ex:
            assert (str(ex) == "id client invalid!\ncnp invalid!\n")

        try:
            service_client.adauga_client(1, "Cosmin", "1234567890120")
            assert False
        except Exception as ex:
            assert (str(ex) == "id-ul exista deja!\ncnp-ul exista deja!\n")

    def test_p_get_client_by_id(self):
        repository_client = ConturiClientiRepository()
        validator_client = ClientValidator()
        book_repo = RepoBookCopies()
        service_client = ServiceClient(validator_client, repository_client, book_repo, 1)
        repository_client.add_cont(ClientAccount(Client(1, "Andrei", "1234"), 0, []))
        assert (service_client.get_client_by_id(1) == ClientAccount(Client(1, "Andrei", "1234"), 0, []))
        try:
            service_client.get_client_by_id(-1)
            assert False
        except Exception as ex:
            assert (str(ex) == "id client invalid!\n")
        try:
            service_client.get_client_by_id(3)
            assert False
        except Exception as ex:
            assert (str(ex) == "id inexistent!\n")

    def test_q_modify_client_cnp(self):
        client_repository = ConturiClientiRepository()
        client_validator = ClientValidator()
        book_repo = RepoBookCopies()
        client_service = ServiceClient(client_validator, client_repository, book_repo, 1)

        client_service.adauga_client(1, "Andrei", "1234567890129")
        client_service.adauga_client(2, "Mihai", "1234567890121")

        cont = client_service.get_client_by_id(1)
        client_service.modificare_cnp_client(cont, "1234567890105")
        assert (cont.get_client().get_cnp() == "1234567890105")

        try:
            client_service.modificare_cnp_client(cont, "1234567890105")
            assert False
        except Exception as ex:
            assert (str(ex) == "cnp-ul exista deja!\n")

        try:
            client_service.modificare_cnp_client(cont, "aaaa")
            assert False
        except Exception as ex:
            assert (str(ex) == "cnp invalid!\n")

    def test_r_modify_client_name(self):
        client_repository = ConturiClientiRepository()
        client_validator = ClientValidator()
        book_repo = RepoBookCopies()
        client_service = ServiceClient(client_validator, client_repository, book_repo, 1)

        client_service.adauga_client(1, "Andrei", "1234567890125")
        client_service.adauga_client(2, "Mihai", "1234567890120")

        cont = client_service.get_client_by_id(2)
        client_service.modificare_nume_client(cont, "Mihnea")

        assert (cont.get_client().get_nume() == "Mihnea")

    def test_s_rent_book(self):
        client_repository = ConturiClientiRepository()
        client_validator = ClientValidator()
        book_repo = RepoBookCopies()
        client_service = ServiceClient(client_validator, client_repository, book_repo, 1)

        book_validator = BookValidator()
        book_service = BookService(book_validator, book_repo, client_service, 1)

        book_service.add_book(1, "Ion", "-", "Rebreanu", 5)
        book_service.add_book(2, "Alice", "frumos", "Autor", 1)
        book_service.add_book(3, "book3", "--", "Autortrei", 0)

        book1 = book_service.get_book_by_id(1)
        book2 = book_service.get_book_by_id(2)
        book3 = book_service.get_book_by_id(3)

        client_service.adauga_client(1, "Andrei", "1234567890120")
        client1 = client_service.get_client_by_id(1)

        client_service.rent_book(client1, book1)
        assert (book1.get_Copies_number() == 4)
        assert (client1.get_carti_inchiriate() == [book1.get_book()])

        client_service.rent_book(client1, book2)
        assert (book2.get_Copies_number() == 0)

        try:
            client_service.rent_book(client1, book2)
            assert False
        except Exception as ex:
            assert (str(ex) == "clientul are deja cartea!\n")

        try:
            client_service.rent_book(client1, book3)
            assert False
        except Exception as ex:
            assert (str(ex) == "carte indisponibila!\n")

    def test_t_search_client(self):
        client_repo = ConturiClientiRepository()
        client_validator = ClientValidator()
        book_repo = RepoBookCopies()
        client_service = ServiceClient(client_validator, client_repo, book_repo, 1)

        client_service.adauga_client(1, "david andrei", "1234567890120")
        client_service.adauga_client(2, "stephen king", "1234567890125")
        client_service.adauga_client(3, "david andrei", "1234567890121")

        client = client_service.get_client_by_id(1)
        client1 = client_service.get_client_by_id(2)
        client2 = client_service.get_client_by_id(3)

        assert (client_service.search_client(3, 0) == client2)
        assert (client_service.search_client("1234567890125", 1) == client1)

        local_clients = [client.get_client().get_id_client(), client2.get_client().get_id_client()]

        assert (client_service.search_client("david andrei", 2) == local_clients)

    def test_u_report_clients(self):
        client_repo = ConturiClientiRepository()
        client_validator = ClientValidator()
        book_repo = RepoBookCopies()
        client_service = ServiceClient(client_validator, client_repo, book_repo, 1)

        book_validator = BookValidator()
        book_service = BookService(book_validator, book_repo, client_service, 1)

        book_service.add_book(1, "Ion", "-", "Rebreanu", 5)
        book_service.add_book(2, "Alice", "frumos", "Autor", 7)
        book_service.add_book(3, "book3", "--", "Autortrei", 8)

        book1 = book_service.get_book_by_id(1)
        book2 = book_service.get_book_by_id(2)
        book3 = book_service.get_book_by_id(3)

        client_service.adauga_client(1, "david andrei", "1234567890120")
        client_service.adauga_client(2, "stephen king", "1234567890125")
        client_service.adauga_client(3, "andrei ficard", "1234567890121")
        client_service.adauga_client(4, "cristian mihaiu", "5234867800121")

        client1 = client_service.get_client_by_id(1)
        client2 = client_service.get_client_by_id(2)
        client3 = client_service.get_client_by_id(3)

        client_service.rent_book(client1, book1)
        client_service.rent_book(client1, book2)
        client_service.rent_book(client1, book3)
        client_service.rent_book(client2, book1)
        client_service.rent_book(client3, book3)
        client_service.rent_book(client3, book2)

        local_clients = [client3, client1, client2]

        assert (client_service.reported_clients(1) == local_clients)

        local_clients = [client2, client3, client1]

        assert (client_service.reported_clients(2) == local_clients)

        local_clients = [client1]

        assert (client_service.reported_clients(3) == local_clients)


class TestCaseBook(unittest.TestCase):

    # Book and Copies tests
    def test_a_book_creator(self):
        id_book = 1
        titlu = "Ion"
        descriere = "roman interbelic"
        autor = "Liviu Rebreanu"
        book1 = Book(id_book, titlu, descriere, autor)
        assert (titlu == book1.get_titlu())
        assert (descriere == book1.get_descriere())
        assert (id_book == book1.get_book_id())
        assert (autor == book1.get_autor())

    def test_b_book_modifier(self):
        book = Book(1, "Despre libertate", "carte filosofica", "John Stuart Mill")
        book.set_book_id(2)
        book.set_title("Moara cu noroc")
        book.set_description("nuvela psihologica")
        book.set_author("Ioan Slavici")
        assert (book.get_book_id() == 2)
        assert (book.get_titlu() == "Moara cu noroc")
        assert (book.get_autor() == "Ioan Slavici")
        assert (book.get_descriere() == "nuvela psihologica")

    def test_c_equals_books(self):
        id_book = 1
        titlu = "Baltagul"
        descriere = "frumos"
        autor = "M. Sadoveanu"
        book1 = Book(id_book, titlu, descriere, autor)
        book2 = Book(1, "Baltagul", descriere, "M. Sadoveanu")
        book3 = Book(id_book, titlu, descriere, "False")
        assert (book1 == book2)
        assert (book1 != book3)

    def test_d_create_a_copy(self):
        book = Book(1, "Luceafarul", "poezie bac", "Mihai Eminescu")
        exemplar = Copies(book, 5)
        assert (exemplar.get_book() == book)
        assert (exemplar.get_Copies_number() == 5)
        exemplar.add_copies(4)
        assert (exemplar.get_Copies_number() == 9)

    # Book validator tests

    def test_e_book_validator(self):
        book_validator = BookValidator()
        book_validator.book_data_validator(1, "Moara", "descriere", "Slavici")
        try:
            book_validator.book_data_validator(-1, " ", "-", "123")
            assert False
        except Exception as ex:
            assert (str(ex) == "id carte invalid!\ntitlu carte invalid!\nnume autor invalid!\n")
        try:
            book_validator.book_data_validator(1, "", "", "Mihai")
            assert False
        except Exception as ex:
            assert (str(ex) == "titlu carte invalid!\ndescriere carte invalida!\n")

    def test_f_book_unicity_validator(self):
        book_repo = RepoBookCopies()
        book_repo.add_exemplar(Copies(Book(1, "Moara", "bac", "Slavici"), 5))
        book_repo.add_exemplar(Copies(Book(2, "Ion", "bac", "Rebreanu"), 7))
        book_validator = BookValidator()
        try:
            book_validator.validare_unicitate(book_repo, 3, "Ion", "Rebreanu")
            assert False
        except Exception as ex:
            assert (str(ex) == "carte deja existenta!\n")
        try:
            book_validator.validare_unicitate(book_repo, 1, "Iooon", "Rebreanu")
            assert False
        except Exception as ex:
            assert (str(ex) == "id deja existent!\n")

        try:
            book_validator.validare_unicitate(book_repo, 1, "Ion", "Rebreanu")
            assert False
        except Exception as ex:
            assert (str(ex) == "id deja existent!\ncarte deja existenta!\n")

    # Book Repo tests
    def test_g_create_copies_repo(self):
        repo_copies = BookRepoFile("TestBooks.txt")
        exemplar1 = Copies(Book(1, "Moara cu noroc", "pt bac", "Slavici"), 10)
        exemplar2 = Copies(Book(2, "Hanul Ancutei", "povesti", "M. Sadoveanu"), 2)
        repo_copies.add_exemplar(exemplar1)
        assert (repo_copies.get_repository() == [exemplar1])
        repo_copies.add_exemplar(exemplar2)
        assert (repo_copies.get_repository() == [exemplar1, exemplar2])

    def test_ga_clear_file(self):
        repo_copies = BookRepoFile("TestBooks.txt")

        assert repo_copies.__len__() == 2

        repo_copies.clear_line(1)
        repo_copies.delete_exemplar(0)

        assert repo_copies.__len__() == 1

        repo_copies.clear_line(2)
        repo_copies.delete_exemplar(0)

        assert repo_copies.__len__() == 0

    def test_h_create_copies(self):
        book_repo = RepoBookCopies()
        exemplar = Copies(Book(1, "Ion", "-", "Ion Rebreanu"), 5)
        assert (book_repo.creare_exemplar(1, "Ion", "-", "Ion Rebreanu", 5) == exemplar)

    # Book service tests

    def test_i_create_service_book(self):
        book_repo = RepoBookCopies()
        book_validator = BookValidator()
        client_repository = ConturiClientiRepository()
        client_validator = ClientValidator()
        client_service = ServiceClient(client_validator, client_repository, book_repo, 1)
        book_service = BookService(book_validator, book_repo, client_service, 1)
        assert (book_service.get_book_validator() == book_validator)
        assert (book_service.get_book_repo() == book_repo)

    def test_j_add_book(self):
        book_repo = RepoBookCopies()
        book_validator = BookValidator()
        client_repository = ConturiClientiRepository()
        client_validator = ClientValidator()
        client_service = ServiceClient(client_validator, client_repository, book_repo, 1)
        book_service = BookService(book_validator, book_repo, client_service, 1)
        assert (book_service.get_book_repo().get_repository() == [])
        book_service.add_book(1, "Ion", "-", "Rebreanu", 6)
        try:
            book_service.add_book(1, "Ion", "-", "Rebreanu", 6)
        except Exception as ex:
            assert (str(ex) == "id deja existent!\ncarte deja existenta!\n")

    def test_k_get_book_by_id(self):
        book_repo = RepoBookCopies()
        book_validator = BookValidator()
        client_repository = ConturiClientiRepository()
        client_validator = ClientValidator()
        client_service = ServiceClient(client_validator, client_repository, book_repo, 1)
        book_service = BookService(book_validator, book_repo, client_service, 1)
        book_service.add_book(1, "Ion", "-", "Liviu Rebreanu", 3)
        assert (book_service.get_book_by_id(1) == Copies(Book(1, "Ion", "-", "Liviu Rebreanu"), 3))
        try:
            book_service.get_book_by_id(-1)
            assert False
        except Exception as ex:
            assert (str(ex) == "id carte invalid!\n")
        try:
            book_service.get_book_by_id(2)
            assert False
        except Exception as ex:
            assert (str(ex) == "id inexistent!\n")

    def test_l_search_books(self):
        book_repo = RepoBookCopies()
        book_validator = BookValidator()
        client_repository = ConturiClientiRepository()
        client_validator = ClientValidator()
        client_service = ServiceClient(client_validator, client_repository, book_repo, 1)
        book_service = BookService(book_validator, book_repo, client_service, 1)

        book_service.add_book(1, "Joyland", "Carte misterioasa", "Stephen King", 5)
        book_service.add_book(2, "Joyland", "Aventrua", "Emily Schultz", 12)
        book_service.add_book(3, "It", "Horror", "Stephen King", 10)

        book = book_service.get_book_by_id(1)
        book1 = book_service.get_book_by_id(2)
        book2 = book_service.get_book_by_id(3)

        local_books = [book.get_book().get_book_id(), book1.get_book().get_book_id()]

        assert (book_service.search_book(3, 0) == book2)
        assert (book_service.search_book("Joyland", 1) == local_books)

        local_books = [book.get_book().get_book_id(), book2.get_book().get_book_id()]

        assert (book_service.search_book("Stephen King", 2) == local_books)

    def test_m_book_reports(self):
        client_repo = ConturiClientiRepository()
        client_validator = ClientValidator()
        book_repo = RepoBookCopies()
        client_service = ServiceClient(client_validator, client_repo, book_repo, 1)

        book_validator = BookValidator()
        book_service = BookService(book_validator, book_repo, client_service, 1)

        book_service.add_book(1, "Ion", "-", "Rebreanu", 5)
        book_service.add_book(2, "Alice", "frumos", "Autor", 7)
        book_service.add_book(3, "book3", "--", "Autortrei", 8)
        book_service.add_book(4, "Moara cu noroc", "nuvela psihologica", "Ioan Slavici", 8)
        book_service.add_book(5, "IT", "roman horror", "Stephen King", 3)

        book1 = book_service.get_book_by_id(1)
        book2 = book_service.get_book_by_id(2)
        book3 = book_service.get_book_by_id(3)
        book4 = book_service.get_book_by_id(4)

        client_service.adauga_client(1, "david andrei", "1234567890120")
        client_service.adauga_client(2, "stephen king", "1234567890125")
        client_service.adauga_client(3, "andrei ficard", "1234567890121")

        client1 = client_service.get_client_by_id(1)
        client2 = client_service.get_client_by_id(2)
        client3 = client_service.get_client_by_id(3)

        try:
            book_service.books_reports(2)
            assert False
        except Exception as ex:
            assert (str(ex) == "In biblioteca nu exista carti care sa fii fost cel putin odata inchiriate.\n")

        client_service.rent_book(client2, book1)
        client_service.rent_book(client1, book2)
        client_service.rent_book(client2, book2)
        client_service.rent_book(client3, book2)
        client_service.rent_book(client1, book3)
        client_service.rent_book(client2, book3)
        client_service.rent_book(client3, book3)
        client_service.rent_book(client1, book4)
        client_service.rent_book(client3, book4)

        local_books = [book2, book3]
        assert (book_service.books_reports(1) == local_books)

        local_books = [book2, book3, book4]
        assert (book_service.books_reports(2) == local_books)

    def test_n_book_max_title(self):
        client_repository = ConturiClientiRepository()
        client_validator = ClientValidator()
        book_repo = RepoBookCopies()
        client_service = ServiceClient(client_validator, client_repository, book_repo, 1)
        book_validator = BookValidator()
        book_service = BookService(book_validator, book_repo, client_service, 1)
        book1 = Copies(Book(1, "Ion", "--", "Liviu Rebreanu"), 6)
        book2 = Copies(Book(2, "Moara cu noroc", "--", "Ioan Slavici"), 10)
        book_repo.add_exemplar(book1)
        book_repo.add_exemplar(book2)

        assert(book_service.max_book_title(1, book1) == book2)

        book3 = Copies(Book(3, "Enigma Otiliei", "--", "G. Calinescu"), 2)
        book_repo.add_exemplar(book3)

        assert(book_service.max_book_title(1, book1) == book3)

        book4 = Copies(Book(4, "Floare Albastra", "--", "M. Eminescu"), 4)
        book_repo.add_exemplar(book4)

        assert(book_service.max_book_title(1, book1) == book4)


if __name__ == '__main__':
    unittest.main()
