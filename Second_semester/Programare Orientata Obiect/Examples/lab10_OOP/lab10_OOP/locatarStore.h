#pragma once
#include "locatarRepo.h"
#include "validator.h"
#include <functional>
#include "listaNotificare.h"
#include "undo.h"

using std::function;
using std::unique_ptr;

class LocatarStore {
	LocatarRepo& rep;
	LocatarValidator& val;
	/*
	 Functie de sortare generala
	 maiMareF - functie care compara 2 Locatar, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Pet)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	//vector<Locatar> generalSort(bool (*maiMicF)(const Locatar&, const Locatar&));
	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar locatarii care trec de filtru (fct(pet)==true)
	*/
	//vector<Locatar> filter(function<bool(const Locatar&)> fct);

	ListaNotificare currentListaNotificare;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
public:
	LocatarStore(LocatarRepo& rep, LocatarValidator& val) :rep{ rep }, val{ val }{}
	//LocatarStore(const LocatarStore& l) = delete;
	~LocatarStore();
	//LocatarStore(const LocatarStore& ot) = delete;
	void operator=(const LocatarStore& ot) = delete;
	/*
	 returneaza toti locatarii in ordinea in care au fost adaugati
	*/
	const vector<Locatar>& getAll() noexcept {
		return rep.getAll();
	}
	/*
	Adauga un nou locatar
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void addLocatar(int apartment, const string name, int surface, const string type);
	int typeNumber(const string& type);
	void undo();

	/*
	sterge un locatar de la apartamentul dat
	*/
	void delLocatar(int apartment);
	/*
	modifica locatar
	*/
	void modifLocatar(int apartment, const string name, int surface, const string type);
	/*caouta locatar*/
	Locatar findLocatar(int apartment);
	/*filtreaza dupa tip*/
	vector<Locatar> filterType(string tip);
	/*filtreaza dupa suprafata*/
	vector<Locatar> filterSurface(int suprafata);
	/*sorteaza dupa nume*/
	vector<Locatar> sortName();
	/*sorteaza dupa suprafata*/
	vector<Locatar> sortSurface();
	/*sorteaza dupa tip si suprafata*/
	vector<Locatar> sortTypeSurface();

	vector<Locatar> removeIfAp(int ap);

	void addToNotificari(int nrApartament);

	const vector<Locatar>& getAllNotificari()const;

	ListaNotificare& getListaNotificari() {
		return this->currentListaNotificare;
	}

	void addRandomNotificari(int nr);

	void emptyNotificari();

	void exportListCVS(std::string fName) const;
	void exportListHTML(std::string fName) const;
};

void testeStore();
void testExporta();