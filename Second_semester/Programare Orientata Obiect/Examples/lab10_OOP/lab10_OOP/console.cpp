#include "console.h"

#include <iostream>
using namespace std;
using std::cout;
using std::cin;

void ConsoleUI::adaugaUI()
{
	/*string name, type;
	int ap, surf;
	cout << "dati apartament: ";
	cin >> ap;
	cout << "dati nume: ";
	cin >> name;
	cout << "dati suprafata: ";
	cin >> surf;
	cout << "dati tip: ";
	cin >> type;
	ctr.addLocatar(ap, name, surf, type);
	cout << "adaugat cu succes\n";*/
	string name, type;
	int ap, surf;
	cout << "dati apartament: ";
	cin >> ap;
	cout << "dati nume: ";
	getline(cin >> ws, name);
	cout << "dati suprafata: ";
	cin >> surf;
	cout << "dati tip: ";
	getline(cin >> ws, type);
	ctr.addLocatar(ap, name, surf, type);
	cout << "adaugat cu succes\n";
}

void ConsoleUI::tipareste(const vector<Locatar>& locatari)
{
	cout << "Locatari:\n";
	for (const auto& loc : locatari) {
		cout << loc.getApartment() << ' ' << loc.getName() << ' ' << loc.getSurface() << ' ' << loc.getType() << '\n';
	}
	cout << "Sfarsit lista locatari\n";
}

void ConsoleUI::sterge()
{
	cout << "apartament de sters: ";
	int ap = 0;
	cin >> ap;
	ctr.delLocatar(ap);
	cout << "sters cu succes\n";
}

void ConsoleUI::modifica()
{
	string name, type;
	int ap, surf;
	cout << "dati apartament: ";
	cin >> ap;
	cout << "dati nume: ";
	cin >> name;
	cout << "dati suprafata: ";
	cin >> surf;
	cout << "dati tip: ";
	cin >> type;
	ctr.modifLocatar(ap, name, surf, type);
	cout << "modificat cu succes\n";
}

void ConsoleUI::cauta()
{
	cout << "apartament de cautat: ";
	int ap = 0;
	cin >> ap;
	Locatar loc = ctr.findLocatar(ap);
	if (loc.getApartment() > 0)
		cout << loc.getApartment() << ' ' << loc.getName() << ' ' << loc.getSurface() << ' ' << loc.getType() << '\n';
	else
		cout << "apartament inexistent\n";
}

void ConsoleUI::printListaNotificareComenzi()
{
	cout << "MENIU LISTA DE NOTIFICARE LOCATARI:\n1 adauga locatar\n2 adauga random locatari\n3 sterge tot\n4 afiseaza tot\n5 meniu principal\n6 export to cvs file\n7 export to html file\n";
}

void ConsoleUI::addNotificari()
{
	cout << "apartament de adaugat: ";
	int ap = 0;
	cin >> ap;
	Locatar loc = ctr.findLocatar(ap);
	if (loc.getApartment() > 0)
		ctr.addToNotificari(ap);
	else
		cout << "apartament inexistent\n";
}

void ConsoleUI::addRandomNotificari()
{
	cout << "numar de adaugari: ";
	int nr = 0;
	cin >> nr;
	if (nr > 0)
		ctr.addRandomNotificari(nr);
	else
		cout << "numar invalid\n";
}

void ConsoleUI::emptyNotificari()
{
	ctr.emptyNotificari();
}

template<typename T>
T myread(const char* msg) {
	T cmd{};
	while (true) {
		std::cout << std::endl << msg;
		std::cin >> cmd;
		const bool fail = std::cin.fail();
		std::cin.clear();//resetez failbit
		const auto& aux = std::cin.ignore(1000, '\n');
		if (!fail && aux.gcount() <= 1) {
			break; //am reusit sa citesc numar
		}
	}
	return cmd;
}

void ConsoleUI::start()
{
	string tip = "";
	int surface = 0, ap = 0;
	while (true) {
		cout << "1 adauga\n2 tipareste\n3 sterge\n4 modifica\n5 cauta\n6 filtrare tip\n7 filtrarea suprafata\n8 sortare nume\n9 sortare suprafata\n10 sortare tip+suprafata\n11 Lista de notificare\n12 remove if\n13 undo\n0 iesire\n";
		int cmd;
		cin >> cmd;
		try
		{
			switch (cmd)
			{
			case 1:
				adaugaUI();
				break;
			case 2:
				tipareste(ctr.getAll());
				break;
			case 3:
				sterge();
				break;
			case 4:
				modifica();
				break;
			case 5:
				cauta();
				break;
			case 6:
				cout << "Dati tipul: ";
				cin >> tip;
				tipareste(ctr.filterType(tip));
				break;
			case 7:
				cout << "Dati suprafata: ";
				cin >> surface;
				tipareste(ctr.filterSurface(surface));
				break;
			case 8:
				tipareste(ctr.sortName());
				break;
			case 9:
				tipareste(ctr.sortSurface());
				break;
			case 10:
				tipareste(ctr.sortTypeSurface());
				break;
			case 11:
				uiNotificari();
				break;
			case 12:
				cout << "Dati apartament: ";
				cin >> ap;
				tipareste(ctr.removeIfAp(ap));
				break;
			case 13:
				ctr.undo();
				tipareste(ctr.getAll());
				break;
			case 0:
				return;
			default:
				cout << "comanda invalida\n";
			}
		}
		catch (const LocatarRepoException& ex)
		{
			cout << ex << '\n';
		}
		catch (const ValidateException& ex) {
			cout << ex << '\n';
		}
	}
}

void ConsoleUI::uiNotificari()
{
	int cmd = 0;
	bool run = true;
	while (run) {
		printListaNotificareComenzi();
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			addNotificari();
			cout << "numar total de apartamente din lista: " << ctr.getAllNotificari().size() << '\n';
			break;
		case 2:
			addRandomNotificari();
			cout << "numar total de apartamente din lista: " << ctr.getAllNotificari().size() << '\n';

			break;
		case 3:
			emptyNotificari();
			cout << "numar total de apartamente din lista: " << ctr.getAllNotificari().size() << '\n';

			break;
		case 4:
			tipareste(ctr.getAllNotificari());
			cout << "numar total de apartamente din lista: " << ctr.getAllNotificari().size() << '\n';

			break;
		case 5:
			run = false;
			break;
		case 6:
			ctr.exportListCVS(myread<string>("CVS File: "));
			break;
		case 7:
			ctr.exportListHTML(myread<string>("HTML File: "));
			break;
		default:
			break;
		}
	}
}
