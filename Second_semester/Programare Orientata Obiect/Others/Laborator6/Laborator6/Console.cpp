#include <iostream>
#include "Console.h"

void Console::run() {
    while (true) {
        std::cout << "Meniu:\n";
        std::cout << "1 adauga\n2 tipareste\n3 Stergere\n4 modifica\n0 Iesire\nDati comanda:";
        int cmd;
        std::cin >> cmd;
        try {
            switch (cmd) {
            case 1:
                add();
                break;
            case 2:
                print(srv.getAll());
                break;
            case 3:
                del();
                break;
            case 4:
                modify();
                break;
            case 0:
                return;
            default:
                std::cout << "Comanda invalida\n";
            }
        }
        catch (const RepoException& ex) {
            std::cout << ex << '\n';
        }
    }
}

void Console::print(const std::vector<Movie>& movies) {
    if (movies.empty())
        return;
    std::cout << "Filme\n";
    for (auto& movie : movies) {
        std::cout << movie.title() << "||" << movie.genre() << "||" << movie.year() << "||" << movie.protagonist() << "\n";
    }
    std::cout << "Sfarsit\n";
}

void Console::add() {
    std::string title, genre, protagonist;
    int year;
    std::cout << "titlu:\n";
    std::cin >> title;
    std::cout << "gen:\n";
    std::cin >> genre;
    std::cout << "an:\n";
    std::cin >> year;
    std::cout << "protagonist:\n";
    std::cin >> protagonist;
    srv.add(title, genre, year, protagonist);
}

void Console::del() {
    std::string title;
    int yea;
    std::cout << "title:";
    std::cin >> title;
    std::cout << "an:";
    std::cin >> yea;
    srv.del(title, yea);
}

void Console::modify() {
    std::string title, genre, protagonist;
    int year;
    std::cout << "title:";
    std::cin >> title;
    std::cout << "an:";
    std::cin >> year;
    std::cout << "nou gen:";
    std::cin >> genre;
    std::cout << "nou prot:";
    std::cin >> protagonist;
    srv.mod(title, year, genre, protagonist);
}



