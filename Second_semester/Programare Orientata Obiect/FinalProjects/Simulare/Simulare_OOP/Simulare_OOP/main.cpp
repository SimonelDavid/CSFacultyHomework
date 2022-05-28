#include <iostream>
#include <QApplication>
#include "Tests.h"
#include "RepoCandidati.h"
#include "Service.h"
#include "Gui.h"

int main(int argc, char** argv) {
    QApplication a{argc, argv};
    Tests t;
    t.runAll();
    RepoCandidati repoCandidati{"candidati.txt"};
    Service service{repoCandidati};
    Gui mainWindow{service};
    mainWindow.show();
    a.exec();
    return 0;
}
