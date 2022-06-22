#include "Melodii_rank.h"
#include <QtWidgets/QApplication>
#include "gui.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //examen_oop_muzica w;
    //w.show();
    Repo r("date.txt");
    Service s(r);
    GUI gui(s);
    gui.show();
    return a.exec();
}
