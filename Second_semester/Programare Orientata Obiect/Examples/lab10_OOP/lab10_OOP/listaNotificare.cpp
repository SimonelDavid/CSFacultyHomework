#include "listaNotificare.h"
#include <random>

void ListaNotificare::addLocToListaNotificare(const Locatar& l)
{
	this->listaDeNotificare.push_back(l);
	notify();
}

void ListaNotificare::emptyListaNotificare()
{
	this->listaDeNotificare.clear();
	notify();
}

void ListaNotificare::addRandomLocatari(vector<Locatar> locatari, int number)
{
	shuffle(locatari.begin(), locatari.end(), std::default_random_engine(std::random_device{}()));
	while (listaDeNotificare.size() < number && locatari.size() > 0) {
		listaDeNotificare.push_back(locatari.back());
		locatari.pop_back();
	}
	notify();
}

const vector<Locatar>& ListaNotificare::getAllListaNotificare()const
{
	return this->listaDeNotificare;
}
