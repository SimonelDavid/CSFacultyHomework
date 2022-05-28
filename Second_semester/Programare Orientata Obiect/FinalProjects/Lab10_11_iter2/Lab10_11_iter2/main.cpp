#include <QtWidgets/QApplication>
#include "Teste.h"
#include "Service.h"
#include "ProductGUI.h"

int main(int argc, char* argv[])
{
	//Test t;
	//t.runTests();

	FileRepo r{ "medicamente.txt", 0.3 };
	Validator v;
	Reteta ret;
	Service s{ r, v, ret };

	QApplication a(argc, argv);
	ProductGUI gui{ s };
	gui.showMaximized();

	return a.exec();
}