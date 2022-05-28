from Repository.File_Repository_Jucator import JucatorFileRepo
from Service.Service_Jucatori import JucatoriService
from UI.console import UserInterface
from Validation.Validare import ValidareJucator
from Teste.Tests import TesteJucatori

teste = TesteJucatori()
teste.run()

repo = JucatorFileRepo("Jucatori.txt")
validare = ValidareJucator()
service = JucatoriService(repo, validare)
console = UserInterface(service)

console.run()