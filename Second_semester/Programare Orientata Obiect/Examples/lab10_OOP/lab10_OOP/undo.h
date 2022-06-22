#pragma once
#include "Locatar.h"
#include "locatarRepo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo {
	Locatar locAdaugat;
	LocatarRepo& rep;
public:
	UndoAdauga(LocatarRepo& rep, const Locatar& l) :rep{ rep }, locAdaugat{ l }{}
	void doUndo() override {
		rep.deletePos(locAdaugat.getApartment());
	}
};

class UndoSterge :public ActiuneUndo {
	Locatar locSters;
	LocatarRepo& rep;
public:
	UndoSterge(LocatarRepo& rep, const Locatar& l) :rep{ rep }, locSters{ l }{}
	void doUndo() override {
		rep.store(locSters);
	}
};

class UndoModifica :public ActiuneUndo {
	Locatar locModificat;
	LocatarRepo& rep;
public:
	UndoModifica(LocatarRepo& rep, const Locatar& l) :rep{ rep }, locModificat{ l }{}
	void doUndo() override {
		rep.modifyPos(locModificat.getApartment(), locModificat);
	}
};