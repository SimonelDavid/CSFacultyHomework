#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Sejur
{
protected:
	char destinatie[20];
	int pret_calatorie;
	int pret_cazare;

public:
	Sejur(char* s, int a, int b)
	{
		strcpy(destinatie, s);
		pret_calatorie = a;
		pret_cazare = b;
	}

	Sejur()
	{
		strcpy(destinatie, "necunoscut");
		pret_calatorie = 0;
		pret_cazare = 0;
	}

	char* getDestinatie()
	{
		return destinatie;
	}

	int getPretCalatorie()
	{
		return pret_calatorie;
	}

	int getPretCazare()
	{
		return pret_cazare;
	}
	
	virtual int pretTotal()
	{
		return pret_calatorie + pret_cazare;
	}

};


class Concediu : public Sejur
{
	char pret_muzee[20];

public: //variabila statica nu o initializez la fiecare ob in parte pt ca va fi aceeasi la fiecare ob in parte
	Concediu(char* n, int a, int b, char* p) : Sejur(n, a, b), pret_muzee(p)
	{
		//pret_muzee=p;
	}
	int pret = stoi(pret_muzee);
	Concediu()
	{
		pret = 0;
	}

	//daca trb tablou de obiecte trb constructor()

	double pretMuzee()
	{
		return pret;
	}

	int pretTotal()
	{
		pret += pretTotal();
		return pret;
	}

	friend istream& operator>>(istream& stream, Concediu& ob); //neaparat &ob
	friend ostream& operator<<(ostream& stream, Concediu ob);
};


istream& operator>>(istream& stream, Concediu& ob) //neaparat &
{
	stream >> ob.destinatie >> ob.pret_calatorie >> ob.pret_muzee;
	return stream;
}

ostream& operator<<(ostream& stream, Concediu ob) //neaparat &
{
	stream << ob.destinatie << ob.pret_calatorie << ob.pret_muzee << endl;
	return stream;
}

int main()
{
	const int n = 4;
	Concediu tab[n];

	for (int i = 0; i < n; i++)
	{
		cin >> tab[i];
	}

	Sejur* p;
	for (int i = 0; i < n; i++)
	{
		p = &tab[i]; //adr pt fiecare elem
		cout << " destinatie: " << p->getDestinatie() << "     anul: " << p->getPretCalatorie() << "     Punctajul: " << tab[i].pretMuzee() << endl;
		//nu se poate p->pret_muzee ca nu apartine clasei de baza

	}

	int nr = 0;
	for (int i = 0; i < n; i++)
	{
		nr += tab[i].pretTotal();
	}
	cout << "\n Numarul concurentilor majori: " << nr;
}