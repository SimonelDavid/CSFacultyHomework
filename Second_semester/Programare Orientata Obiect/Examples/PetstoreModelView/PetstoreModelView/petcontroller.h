#pragma once
#include "pet.h"
#include "petrepo.h"
#include <vector>
#include "undo.h"
#include <memory>
#include "CosPet.h"
#include "export.h"
#include "PetValidator.h"
using std::unique_ptr;
class PetService {
private:
	PetRepo& repo;	
	PetValidator validator;
	//tinem pointeri la ActiuneUndo pentru ca vrem apel polimorfic
	//punem unique_ptr pentru ca avem responsabilitatea de a elibera memoria pentru 
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
	//std::vector<ActiuneUndo*> undoActions;

	CosPet cos;
public:
	PetService(PetRepo& rep) :repo{ rep }, cos{rep} {}
	~PetService();
	PetService(const PetService& ot) = delete;//nu vreau sa se copiez
	void operator=(const PetService& ot) = delete;//nu vreau sa mearga assignment
	/*
	Adauga pet
	Arunca PetException daca pet e invalid sau mai exista in aplicatie
	*/
	void add(const std::string& type, const std::string& species, int price);
	
	/*
	Cauta pet
	Arunca PetException daca nu exista pet
	*/
	Pet find(const string& species,const string& type) {
		return repo.find(species, type);
	}
	/*
	  Toate
	*/
	std::vector<Pet> getAllPets();

	/*
	Sortat dupa pret
	*/
	std::vector<Pet> getSortByPrice();
	/*
	Sortat dupa tip
	*/
	std::vector<Pet> getSortByType();

	std::vector<Pet> getFilterByPrice(int price);

	void undo();

	std::vector<Pet> addToCos(std::string species, std::string type);

	std::vector<Pet> addRandom(int cate);

	std::vector<Pet> golesteCos();
	
	std::vector<Pet> toateDinCos();

	void exportaCosCVS(std::string fName);

	void exportaCosHTML(std::string fName);

	CosPet& getCos() {
		return cos;
	}
	void genereazaAleatorAnimale(int cate);

	int getTotalPets() {
		return repo.getTotalPets();
	}
};


void testCtr();