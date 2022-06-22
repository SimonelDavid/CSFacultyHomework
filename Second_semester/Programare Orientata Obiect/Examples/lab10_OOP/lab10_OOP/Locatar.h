#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Locatar
{
private:
	std::string name;
	std::string type;
	int apartment, surface;
public:
	Locatar() {

	}
	Locatar(int a, const string n, int s, const string t) :apartment{ a }, name{ n }, surface{ s }, type{ t }{};
	Locatar(const Locatar& l) :apartment{ l.apartment }, name{ l.name }, surface{ l.surface }, type{ l.type }{
	};

	int getApartment() const noexcept {
		return apartment;
	}

	string getName() const {
		return name;
	}

	int getSurface() const noexcept {
		return surface;
	}

	string getType() const {
		return type;
	}
};
/*compara 2 nume*/
bool cmpName(const Locatar& l1, const Locatar& l2);
/*compara 2 suprafete*/
bool cmpSurface(const Locatar& l1, const Locatar& l2);