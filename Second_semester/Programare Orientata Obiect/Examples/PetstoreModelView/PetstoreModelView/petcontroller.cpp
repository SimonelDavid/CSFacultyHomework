#include "petcontroller.h"
#include <vector>
#include <algorithm>
#include <assert.h>
#include <iterator>
#include <memory>
#include "undo.h"
#include <stdlib.h>
/*
Adauga pet
Arunca PetException daca pet e invalid sau mai exista in aplicatie
*/
void PetService::add(const std::string& type, const std::string& species, int price) {
	Pet p{ type.c_str(),species.c_str(),price };
	validator.validate(p);
	repo.store(p);			

	undoActions.push_back(std::make_unique<UndoAdauga>(repo, p));
	//undoActions.push_back(new UndoAdauga {repo, p});
}

void PetService::undo() {
	if (undoActions.empty()) {
		throw PetException{"Nu mai exista operatii"};
	}
	/*
	ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;
	*/
	// Varianta cu unique_ptr
	//obs: la obiecte unique_ptr nu putem face copie
	undoActions.back()->doUndo();
	undoActions.pop_back();	
}
PetService::~PetService() {
	
	/*In varianta cu unique_ptr nu mai e nevoie
	for (auto act : undoActions) {
		delete act;
	}*/
	
}
/*
Toate
*/
std::vector<Pet> PetService::getAllPets() {
	return repo.getAll();	
}


/*
Sortat dupa pret
*/
std::vector<Pet> PetService::getSortByPrice() {
	auto v = repo.getAll();
	std::sort(v.begin(), v.end(), [](const Pet& p1, const Pet& p2) {return p1.getPrice()<p2.getPrice(); });
	return v;
}
/*
Sortat dupa tip
*/
std::vector<Pet> PetService::getSortByType() {
	auto v = repo.getAll();
	//folosim o functie lamba pentru compararea de elemente
	std::sort(v.begin(), v.end(), [](const Pet& p1, const Pet& p2) {
		return p1.getType()<p2.getType(); 
	});
	return v;
}
/*
Filtrare dupa pret
*/
std::vector<Pet> PetService::getFilterByPrice(int price) {
	std::vector<Pet> rez;
	auto all = repo.getAll();
	std::copy_if(all.begin(), all.end(),back_inserter(rez), [=](const Pet& p) {return p.getPrice() > price; });	
	return rez;
}

std::vector<Pet> PetService::addToCos(std::string species, std::string type) {
	Pet p = repo.find(species, type);
	cos.adauga(p);
	return cos.lista();
}

std::vector<Pet> PetService::addRandom(int cate) {
	cos.umple(cate);
	return cos.lista();
}

std::vector<Pet> PetService::golesteCos() {
	cos.goleste();
	return cos.lista();
}
/*
Genereaza animale cu species,type, si pret aleator
*/
void PetService::genereazaAleatorAnimale(int cate) {
	srand(time(NULL));
	string posible_chars{ "abcdefghijklmnoprstuvxyz" };
	for (int i = 0; i < cate; i++) {
		int lg = rand()%10 + 2;
		string species(lg, ' ');
		string type(lg, ' ');
		for (int j = 0; j < lg;j++){
		  int randomCharPoz = rand()%posible_chars.size();
		  species[j] = posible_chars[randomCharPoz];
		  randomCharPoz = rand() % posible_chars.size();
		  type[j] = posible_chars[randomCharPoz];
		}
		Pet p{ type,species, rand()%100 + 20 };
		try {
			repo.store(p);
		}
		catch (PetException& e) {
			//ignor... este o sansa sa generam acelasi pet
		}		
	}
}

std::vector<Pet> PetService::toateDinCos() {
	return cos.lista();
}

void PetService::exportaCosCVS(std::string fName) {
	exportToCVS(fName,cos.lista());
}

void PetService::exportaCosHTML(std::string fName) {
	exportToHTML(fName, cos.lista());
}

void testCtr() {
	PetRepoMemory rep;
	PetService ctr{ rep };
	ctr.add("aaa", "bbb", 3);
	ctr.add("ccc", "bbb", 2);
	ctr.add("bbb", "bbb", 1);

	std::vector<Pet> v = ctr.getSortByPrice();
	assert(v[0].getPrice() == 1);
	assert(v[1].getPrice() == 2);
	assert(v[2].getPrice() == 3);

	std::vector<Pet> v2 = ctr.getSortByType();
	assert(v2.at(0).getType()=="aaa");
	assert(v2.at(1).getType()=="bbb");
	assert(v2.at(2).getType()=="ccc");

	//testam si assigment operator de la vectordinamic
	v = v2;
	assert(v[0].getType()=="aaa");
	assert(v[1].getType()=="bbb");
	assert(v[2].getType()=="ccc");
	

	std::vector<Pet> filtrat = ctr.getFilterByPrice(2);
	assert(filtrat.size() == 1);
	assert(filtrat[0].getPrice() == 3);
}