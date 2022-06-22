#pragma once
#include "locatarStore.h"

class ConsoleUI {
	LocatarStore& ctr;
	/*
	Citeste datele de la tastatura si adauga Locatar
	arunca exceptie daca: nu se poate salva, nu e valid
	*/
	void adaugaUI();
	/*
	Tipareste o lista de locatari la consola
	*/
	void tipareste(const vector<Locatar>& locatari);
	/*
	sterge un element de pe o pozitie data
	*/
	void sterge();
	/*
	modifica un element de pe o pozitie data
	*/
	void modifica();
	/*
	cauta un locatar
	*/
	void cauta();

	void printListaNotificareComenzi();

	void addNotificari();

	void addRandomNotificari();

	void emptyNotificari();

public:
	ConsoleUI(LocatarStore& ctr) :ctr{ ctr } {}
	ConsoleUI(const ConsoleUI& ot) = delete;
	void start();
	void uiNotificari();
};