#pragma once

#include <string.h>
#include <iostream>
#include <ostream>
#include <string>
using std::string;
class PetException {
	std::string msg;
public:
	PetException(const string& m) :msg{ m } {};
	string getMsg()const { return msg; }
};


class Pet {
private:
	std::string type;
	std::string species;
	int price;
public:
	/*
	Constructor default
	*/
	Pet():Pet("","",0) {		
	}
	/*
	  Constructor 3 param
	*/
	Pet(const std::string& t, const std::string& s, int p) :type{ t }, species{ s }, price{ p } {
	}
	/*
	Constuructor copiere
	Copieaza continutul lui p in obiectul current
	*/
	Pet(const Pet& p) = default;

		/*
		Operator de assignare
		apelat cand se scrie p1 = p2;
		Continutul lui p2 (ot) copiat in p1
		Obs: p1 are deja ceva inainte de atribuire - trebuie dealocat memoria
		*/
	Pet& operator=(const Pet& ot) = default;

	int getPrice() const {
		return price;
	}

	void setPrice(int price) {
		this->price = price;
	}

	const string& getType() const {
		return type;
	}
	const string& getSpecies() const {
		return species;
	}
	friend std::ostream& operator<<(std::ostream& os, const Pet&p);
};

std::ostream& operator<<(std::ostream& os, const Pet& p);

int cmpByPrice(const Pet& p1, const Pet& p2);

int cmpByType(const Pet& p1, const Pet& p2);

void testPet();
