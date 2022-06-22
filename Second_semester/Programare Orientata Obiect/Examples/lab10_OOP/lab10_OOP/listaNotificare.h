#pragma once
#include <vector>
#include "Locatar.h"

#include "Observer.h"

using std::vector;
class ListaNotificare:public Observable {
private:
	vector<Locatar> listaDeNotificare;
public:
	ListaNotificare() = default;

	/*adauga locatar in lista*/
	void addLocToListaNotificare(const Locatar& l);

	/*goleste lista*/
	void emptyListaNotificare();

	/*adauga random locatari
	vector<Locatar> locatari- lista de locatari din care se adauga
	int number -numarul de adaugari
	*/
	void addRandomLocatari(vector<Locatar> locatari, int number);

	/*returneaza intreaga lista de notificare*/
	const vector<Locatar>& getAllListaNotificare()const;
};