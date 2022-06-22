#pragma once
#include "Locatar.h"

#include <vector>
#include <algorithm>
//using std::find_if;
using std::vector;
using std::ostream;

class LocatarRepo {
	vector<Locatar> all;
	/*
	metoda privata verifica daca exista deja l in repository
	*/
	bool exist(const Locatar& l) const;
public:
	LocatarRepo() = default;
	LocatarRepo(const LocatarRepo& l) = delete;
	/*
	Salvare locatar
	arunca exceptie daca mai exista un locatar cu acelasi apartament
	*/
	virtual void store(const Locatar& l);
	/*
	Cauta
	arunca exceptie daca nu exista locatar
	*/
	const Locatar& find(int apartment) const;
	/*
	returneaza toti locatarii
	*/
	const vector<Locatar>& getAll() const noexcept;
	/*sterge un locatar dupa apartament*/
	void deletePos(int apartment);
	/*modifica un locatar dupa apartament*/
	void modifyPos(int apartment, const Locatar& l);
};

class LocatarRepoFile : public LocatarRepo {
private:
	string filename;
	void loadFromFile();

	void saveToFile();

public:
	LocatarRepoFile(string fname) : LocatarRepo(), filename{ fname }{
		loadFromFile();
	};
	void store(const Locatar& l) override;
};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class LocatarRepoException {
	string msg;
public:
	LocatarRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const LocatarRepoException& ex);
	string getMsg()const { return msg; }
};

ostream& operator<<(ostream& out, const LocatarRepoException& ex);

void testeRepo();
void testeFileRepo();