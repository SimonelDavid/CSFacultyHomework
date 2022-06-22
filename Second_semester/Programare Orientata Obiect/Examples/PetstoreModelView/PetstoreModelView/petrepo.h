#pragma once
#include "pet.h"
#include <vector>
#include <algorithm>
#include <string>

class PetRepo {
public:
	virtual void store(const Pet& p) = 0;
	virtual Pet find(const std::string& species, const std::string& type) const = 0;
	virtual void sterge(const Pet& p) = 0;
	virtual const std::vector<Pet>& getAll() const = 0;
	virtual int getTotalPets() {
		return getAll().size();
	}
};

class PetRepoMemory:public PetRepo {
private:
	std::vector<Pet> all;
public:
	PetRepoMemory() {}

	PetRepoMemory(const PetRepoMemory& ot) = delete;//nu vreau sa se copieze repo
	/*
	Salveaza pet
	*/
	virtual void store(const Pet& p) {
		//verificam sa nu mai existe un pet 
		auto found = std::find_if(all.begin(), all.end(), [p](const Pet& pp) {
			return pp.getSpecies()==p.getSpecies() && pp.getType()==p.getType(); });
		if (found != all.end()) {			
			throw PetException{ "Pet existent!!!" };
		}
		all.push_back(p);
	}
	/*
	Cauta pet
	Arunca PetException daca nu exista pet
	*/
	Pet find(const std::string& species,const std::string& type) const override {
		auto found = std::find_if(all.begin(), all.end(), [&](const Pet& pp) {
			return pp.getSpecies()==species && pp.getType()==type.c_str(); });
		if (found == all.end()) {
			throw PetException{ "Pet inexistent!!!" };
		}
		return *found;
	}
	virtual void sterge(const Pet& p) {
		auto found = std::find_if(all.begin(), all.end(), [p](const Pet& pp) {
			return pp.getSpecies()== p.getSpecies() && pp.getType()== p.getType(); });
		if (found == all.end()) {
			throw PetException{ "Pet inexistent!!!" };
		}
		//stergem pet
		all.erase(found);
	}

	const std::vector<Pet>& getAll() const override{
		return all;
	}
};

class PetRepoFileV1 :public PetRepoMemory {
private:
	std::string fName;
	void loadFromFile();
	void writeToFile(const std::vector<Pet>& pets);
public:
	PetRepoFileV1(std::string fName) :PetRepoMemory(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}
	PetRepoFileV1(const PetRepoFileV1& ot) = delete;//nu vreau sa se copieze repo
};

/*
Varianta mai rapida de repo file
La incarcarea din fisier nu verifica duplicate
La adaugare de pet face append la fisier (nu rescrie tot fisierul)
*/
class PetRepoFileV2 :public PetRepo {
private:	
	std::vector<Pet> cachedPets;

	std::string fName;
	void loadFromFile();
	void writeToFile(const std::vector<Pet>& pets);
	void appendToFile(const Pet& p);
public:
	PetRepoFileV2(std::string fName) :PetRepo(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}
	PetRepoFileV2(const PetRepoFileV2& ot) = delete;//nu vreau sa se copieze repo

	int getTotalPets() override{		
		return cachedPets.size();
	}
	void store(const Pet& p) override {		
		auto found = std::find_if(cachedPets.begin(), cachedPets.end(), [p](const Pet& pp) {
			return pp.getSpecies() == p.getSpecies() && pp.getType() == p.getType(); });
		if (found != cachedPets.end()) {
			throw PetException{ "Pet exist!!!" };
		}
		cachedPets.push_back(p);
		appendToFile(p);
	}
	void sterge(const Pet& p) override {		
		auto found = std::find_if(cachedPets.begin(), cachedPets.end(), [p](const Pet& pp) {
			return pp.getSpecies() == p.getSpecies() && pp.getType() == p.getType(); });
		if (found == cachedPets.end()) {
			throw PetException{ "Pet inexistent!!!" };
		}
		//stergem pet		
		cachedPets.erase(found);		
		writeToFile(cachedPets);
	}
	const std::vector<Pet>& getAll() const {

		return cachedPets;
	}

	Pet find(const std::string& species, const std::string& type) const override {		
		auto found = std::find_if(cachedPets.begin(), cachedPets.end(), [&](const Pet& pp) {
			return pp.getSpecies() == species && pp.getType() == type.c_str(); });
		if (found == cachedPets.end()) {
			throw PetException{ "Pet inexistent!!!" };
		}
		return *found;
	}
};