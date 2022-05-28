from Repository.FileRepo import CursuriRepo
from Service.ServiceCurs import CursService
from Domain.Curs import Inscriere
from UI.console import Consola
from Tests.teste import Teste

teste = Teste()
teste.test_run_all()

repo_cursuri = CursuriRepo("cursuri.txt")
service_cursuri = CursService(repo_cursuri, Inscriere)
rulare = Consola(service_cursuri)

rulare.run()