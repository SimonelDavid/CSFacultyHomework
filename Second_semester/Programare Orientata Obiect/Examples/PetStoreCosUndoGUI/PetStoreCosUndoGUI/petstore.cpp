// ConsoleApplication4.cpp : Defines the entry point for the console application.
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include "pet.h"

#include "petservice.h"
#include "storeui.h"

void addSamplePetss(PetService& ctr) {
	ctr.add( "Pasare", "Papagal", 20);
	ctr.add( "Pasare", "Randunica", 2);
	ctr.add( "Peste", "Pastrav", 90);
	ctr.add( "Peste", "Rechin", 100);
	ctr.add( "Pasare", "Soim", 200);
}

int mainConsole()
{
	
	testPet();	
	testCtr();
	testPetRepos();

	{
	//PetRepo rep;
	PetRepoFile rep{ "pets.txt" };
	PetService ctr{ rep };
	//addSamplePets(ctr);
	PetUI ui{ ctr };
	ui.startUI();
	}
	_CrtDumpMemoryLeaks();

    return 0;
}

