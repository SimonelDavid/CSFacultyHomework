#include "Repo.h"
#include <fstream>
#include <sstream>

void Repo::loadFromFile()
{
	ifstream fi(filename);
	string line;
	all.clear();
	while (getline(fi, line)) {
		int i = 0, r = 0;
		string t, a;
		stringstream linestream(line);
		string item;
		int crt = 0;
		while (getline(linestream, item, ';')) {
			if (crt == 0)i = stoi(item);
			if (crt == 1)r = stoi(item);
			if (crt == 2)t = (item);
			if (crt == 3)a = (item);
			crt++;
		}
		Melodie m(i, r, t, a);
		all.push_back(m);
	}
	fi.close();
}

void Repo::storeToFile()
{
	ofstream fo(filename);
	for (auto& el : getAll()) {
		fo << el.getId() << ';' << el.getRank() << ';' << el.getTitlu() << ';' << el.getArtist() << '\n';
	}
	fo.close();
}

void Repo::addMelodie(Melodie m)
{
	all.push_back(m);
	storeToFile();
}

int Repo::getNumberFromArtist(string artist)
{
	int k = 0;
	for (const auto& el : getAll()) {
		if (el.getArtist() == artist)
			k++;
	}
	return k;
}

bool Repo::deletePos(int id)
{
	int pos = 0;
	for (const auto& el : getAll()) {
		if (el.getId() == id)
			if (getNumberFromArtist(el.getArtist()) > 1) {
				all.erase(all.begin() + pos);
				storeToFile();
				return 1;
			}
			else
				return 0;
		pos++;
	}

}
