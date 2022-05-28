from Teste.tests import Teste
from Repository.repo_picturi import PicturiRepository
from Service.service import ServicePicturi
from UI.console import UserInterface

teste = Teste()
teste.run_tests()

repo_picturi = PicturiRepository("Picturi.txt")

service_picturi = ServicePicturi(repo_picturi)

user_console = UserInterface(service_picturi)

user_console.run()