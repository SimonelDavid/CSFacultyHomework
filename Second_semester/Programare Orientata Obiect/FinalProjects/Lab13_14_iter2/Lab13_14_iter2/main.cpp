#include <QtWidgets/QApplication>
#include "Service.h"
#include "ProductGUI.h"
#include "ProductGUIModel.h"

int main(int argc, char* argv[])
{

	FileRepo r{ "medicamente.txt", 0.2 };
	Validator v;
	Reteta ret;
	Service s{ r, v, ret };

	QApplication a(argc, argv);

	//ProductGUIModel gui{ s, ret, r};
	ProductGUI gui{ s, ret, r };
	gui.showMaximized();

	return a.exec();
}