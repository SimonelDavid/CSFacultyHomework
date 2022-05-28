#include <iostream>
#include <QApplication>
#include "Tests.h"
#include "RepoProcesor.h"
#include "RepoPlacaDeBaza.h"
#include "Service.h"
#include "Gui.h"

int main(int argc, char** argv) {
    QApplication a{argc, argv};
    Tests t;
    t.runAll();
    RepoProcesor repoProcesor{"procesoare.txt"};
    RepoPlacaDeBaza repoPlacaDeBaza{"placi.txt"};
    Service service{repoProcesor, repoPlacaDeBaza};
    Gui mainWindow{service};
    mainWindow.show();
    a.exec();
    return 0;
}
