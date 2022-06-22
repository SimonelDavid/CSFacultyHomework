#include "petrepo.h"
#include "pet.h"
#include <fstream>
void PetRepoFileV1::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) { //verify if the stream is opened		
		throw PetException("Unable to open file:" + fName);
	}	
	while (!in.eof()) {
		std::string species;
		in >> species;
		std::string type;
		in >> type;

		int price;
		in >> price;
		if (in.eof()) {	//nu am reusit sa citesc numarul
			break;
		}
		Pet p{ type.c_str(), species.c_str(), price };
		PetRepoMemory::store(p);
	}
	in.close();

}

void PetRepoFileV1::writeToFile(const std::vector<Pet>& pets) {
	std::ofstream out(fName);
	if (!out.is_open()) { //verify if the stream is opened
		std::string msg("Unable to open file:");
		throw PetException(msg);
	}
	for (auto& p : pets) {
		out << p.getSpecies();
		out << "\n";
		out << p.getType();
		out << "\n";
		out << p.getPrice();
		out << "\n";
	}
	out.close();
}





void PetRepoFileV2::appendToFile(const Pet& p) {
	std::ofstream out(fName,std::ios::app);
	if (!out.is_open()) { //verify if the stream is opened		
		throw PetException("Unable to open file:" + fName);
	}
	out << p.getSpecies();
	out << "\n";
	out << p.getType();
	out << "\n";
	out << p.getPrice();
	out << "\n";
	out.close();

}

void PetRepoFileV2::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) { //verify if the stream is opened		
		throw PetException("Unable to open file:"+fName);
	}	
	cachedPets.clear();
	while (!in.eof()) {
		std::string species;
		in >> species;
		std::string type;
		in >> type;

		int price;
		in >> price;
		if (in.eof()) {	//nu am reusit sa citesc numarul
			break;
		}
		Pet p{type.c_str(), species.c_str(), price};
		cachedPets.push_back(p);
	}
	in.close();
	
}

void PetRepoFileV2::writeToFile(const std::vector<Pet>& pets) {
	std::ofstream out(fName);
	if (!out.is_open()) { //verify if the stream is opened
		std::string msg("Unable to open file:");
		throw PetException(msg);
	}
	for (auto& p:pets) {		
		out << p.getSpecies();
		out << "\n";
		out << p.getType();
		out << "\n";
		out << p.getPrice();
		out << "\n";
	}
	out.close();
}
