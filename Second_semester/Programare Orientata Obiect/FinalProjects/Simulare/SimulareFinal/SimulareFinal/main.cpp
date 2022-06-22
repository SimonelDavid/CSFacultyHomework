#include <iostream>
#include "Tests.h"
#include "Gui.h"
#include <QApplication>

int main(int argc, char** argv) {
    //Tests::runAll();
    QApplication a{argc, argv};
    Repo r{"cand.txt"};
    Service s{r};
    Gui g{s};
    g.show();
    a.exec();
    return 0;
}
