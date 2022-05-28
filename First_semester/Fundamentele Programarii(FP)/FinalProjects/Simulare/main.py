from Repository.RepoImobil import RepoImobiliare
from Service.ServiceImobil import ServiceulImobilelor
from UI.Console import Consola
from Teste.Tests import Teste

teste = Teste()
teste.test_run_all()

repo_imobiliare = RepoImobiliare("Imobile.txt")
service_imobiliare = ServiceulImobilelor(repo_imobiliare)
rulare = Consola(service_imobiliare)
rulare.run()
