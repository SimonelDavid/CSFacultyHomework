#include "SEMINAR6.h"
#include "SongStoreGUI.h"
#include <QtWidgets/QApplication>

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include "UI.h"
#include <iostream>
using std::cout;
using std::endl;
void testAll() {
	testeDomain();
	cout << "Finished domain tests." << endl;
	testeRepo();
	testeFileRepo();
	cout << "Finished repo tests." << endl;
	testeService();
	cout << "Finished service tests." << endl;

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	//SongRepository repo;
	SongRepositoryFile repoFile{ "songs.txt" };

	SongValidator val;
	SongStore srv{ repoFile,val };
	SongStoreGUI gui{ srv };

	//gui.setWindowState(Qt::WindowMaximized);

	gui.show();
    return a.exec();
}
