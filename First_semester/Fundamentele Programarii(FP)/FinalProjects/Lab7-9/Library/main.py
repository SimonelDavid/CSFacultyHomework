from UI.console import UserConsole

from Domain.client import ClientAccount
from Domain.book import Copies

# from Repository.client_repo import ConturiClientiRepository
from Repository.ClientsFileRepo import ClientsRepoFile
# from Repository.book_repo import RepoBookCopies
from Repository.BookFileRepo import BookRepoFile

from Service.client_service import ServiceClient
from Service.book_service import BookService

from Validation.client_validator import ClientValidator
from Validation.book_validator import BookValidator

from Testing.test import Test

test = Test()
# test = UnitTest()
test.run_all_tests()

# client_repository = ConturiClientiRepository()
book_repo_file = BookRepoFile("Books.txt")
client_validator = ClientValidator()

# book_repo = RepoBookCopies()
client_repo_file = ClientsRepoFile("Clients.txt", book_repo_file)
book_validator = BookValidator()

client_service = ServiceClient(client_validator, client_repo_file, book_repo_file, 0)
book_service = BookService(book_validator, book_repo_file, client_service, 0)

user_console = UserConsole(client_service, book_service)
user_console.run()
