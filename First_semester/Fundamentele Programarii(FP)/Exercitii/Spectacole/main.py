from Domain.Spectacol import Spectacol
from Repository.Spectacol_repository_files import SpectacolRepoFile
from Service.Service_spectacol import SpecatacolService
from UI.console import UserInterface
from Validation.Validare_Spectacol import SpectacolValidation
from Tests.teste import Teste

teste = Teste()

teste.run()

Repo = SpectacolRepoFile("Spectacole.txt")
Validator = SpectacolValidation()
Service = SpecatacolService(Repo, Validator)
console = UserInterface(Service)

console.run()