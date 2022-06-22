#pragma once
#include "Domain.h"
#include <vector>

class Repo {
private:
	string filename;
	vector<Melodie> all;
public:
	Repo(string f) :filename{ f } { loadFromFile(); };
	void loadFromFile();
	void storeToFile();
	void addMelodie(Melodie m);
	vector<Melodie> getAll() { return all; };
	void updateRank(int id, int newRank, string titlu) {
		int pos = 0;
		for (const auto& el : getAll()) {
			if (el.getId() == id) {
				all.erase(all.begin() + pos);
				Melodie m{ id,newRank,titlu,el.getArtist() };
				all.push_back(m);
			}
			pos++;
		}
		storeToFile();
	}
	int getNumberFromArtist(string artist);
	bool deletePos(int id);
};