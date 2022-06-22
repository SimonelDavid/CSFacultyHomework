#include "lab10_OOP.h"
#include <QtWidgets/QApplication>

#include "console.h"
#include <stdlib.h>
#include <crtdbg.h>
#include "LocatarStoreGUI.h"
#include "LocatarStoreGUIModel.h"

void addLocatari(LocatarStore& ctr) {
	ctr.addLocatar(1, "Ion", 120, "garsoniera");
	ctr.addLocatar(2, "Ionel", 200, "apartament");
	ctr.addLocatar(3, "Ionut", 11, "garsoniera");
	ctr.addLocatar(4, "Ioana", 360, "duplex");
}

void testAll() {
	testValidate();
	testeRepo();
	testeStore();
	testExporta();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	LocatarRepoFile rep{ "locatari.txt" };
	LocatarValidator val;
	LocatarStore ctr{ rep,val };
	
	//LocatarStoreGUI gui{ ctr };
	LocatarStoreGUIModel gui{ ctr };
	gui.show();
    return a.exec();
}
