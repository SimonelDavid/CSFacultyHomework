#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

class Persoana
{
protected:
	char nume[20];
	int an;

public:
	Persoana(char* s, int a)
	{
		strcpy(nume, s);
		an = a;
	}

	Persoana()
	{
		strcpy(nume, "necunoscut");
		an = 0;
	}

	char* getNume()
	{
		return nume;
	}

	int getAn()
	{
		return an;
	}

	virtual int verifica() = 0;

};


class Concurent : public Persoana
{
	double punctaj;
	static int etapaC;

public: //variabila statica nu o initializez la fiecare ob in parte pt ca va fi aceeasi la fiecare ob in parte
	Concurent(char* n, int a, double p) : Persoana(n, a), punctaj(p)
	{
		//punctaj=p;
	}

	Concurent()
	{
		punctaj = 0;
	}

	//daca trb tablou de obiecte trb constructor()

	double getPunctaj()
	{
		return punctaj;
	}

	int getEtapa()
	{
		return etapaC;
	}

	int verifica()
	{
		if (2022 - an >= 18) return 1;
		return 0;
	}

	static void setEtapa(Concurent tab[], int n)
	{
		int cnt = 0;
		for (int i = 0; i < n; i++)
			if (tab[i].punctaj > 100) cnt++;
		if (cnt == n) etapaC++;
	}

	friend istream& operator>>(istream& stream, Concurent& ob); //neaparat &ob
	friend ostream& operator<<(ostream& stream, Concurent ob);
};


int Concurent::etapaC = 1; //neaparat

istream& operator>>(istream& stream, Concurent& ob) //neaparat &
{
	stream >> ob.nume >> ob.an >> ob.punctaj;
	return stream;
}

ostream& operator<<(ostream& stream, Concurent ob) //neaparat &
{
	stream << ob.nume << ob.an << ob.punctaj << endl;
	return stream;
}

int main()
{
	const int n = 5;
	Concurent tab[n];

	ifstream fi("text.txt", ios::in);
	if (!fi)
	{
		cout << "\n Eroare la deschiderea fisierului...";
		exit(1);
	}

	for (int i = 0; i < n; i++)
	{
		fi >> tab[i]; //preluam din fisier
	}

	fi.close(); //inchidem fluxul

	Persoana* p;
	for (int i = 0; i < n; i++)
	{
		p = &tab[i]; //adr pt fiecare elem
		cout << " nume: " << p->getNume() << "     anul: " << p->getAn() << "     Punctajul: " << tab[i].getPunctaj() << endl;
		//nu se poate p->punctaj ca nu apartine clasei de baza

	}

	int nr = 0;
	for (int i = 0; i < n; i++)
	{
		if (tab[i].verifica()) nr++;
	}
	cout << "\n Numarul concurentilor majori: " << nr;
	Concurent::setEtapa(tab, n);
	cout << "\n Etapa: " << tab[1].getEtapa();
}