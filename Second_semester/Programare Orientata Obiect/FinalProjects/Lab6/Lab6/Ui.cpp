#include "Ui.h"
#include "gsl.h"

// typedef void(console::*comm)();
void console::run() {

    while (true) {

        cout << "COMENZI:\n";
        cout << "1. Adauga medicament.    \n";
        cout << "2. Sterge medicament.    \n";
        cout << "3. Modifica medicament.  \n";
        cout << "4. Cauta medicament.     \n";
        cout << "5. Afiseaza medicamente. \n";
        cout << "6. Filtreaza medicamente.\n";
        cout << "7. Sorteaza medicamente. \n";
        cout << "8. Iesi din aplicatie.   \n";
        cout << '\n';
        cout << "Introdu numarul comenzii: ";

        string answ;
        cin >> answ;
        cout << '\n';

        const int command = gsl::at(answ,0) - '0';

        cout << "------------------------------\n";
        switch (command) {
        case 1:
            adauga();
            break;
        case 2:
            sterge();
            break;
        case 3:
            modifica();
            break;
        case 4:
            cautare();
            break;
        case 5:
            afisare();
            break;
        case 6:
            filtrare();
            break;
        case 7:
            sortare();
            break;
        case 8:
            return;
        default:
            cout << "Comanda invalida";
        }
        cout << "------------------------------\n";


    }

}

void console::adauga() {
    string line;

    cout << "ADAUGARE\n\n";

    bool ok = true;
    while (ok) {
        ok = false;
        cout << "Introdu numele medicamentului: ";
        string nume;
        cin >> nume;
        cout << '\n';

        cout << "Introdu pretul medicamentului: ";

        string price;
        cin >> price;
        cout << '\n';

        cout << "Introdu producatorul medicamentului: ";

        string producator;
        cin >> producator;
        cout << '\n';

        cout << "Introdu substanta activa a medicamentului: ";
        string substanta;
        cin >> substanta;
        cout << '\n';
        try {
            farmacie.addElem(nume, price, producator, substanta);
        }
        catch (const ValidationError& e) {
            cout << e.getMessage() << '\n' << "Incerci din nou?(y/n)";

            string answer;
            cin >> answer;
            if (gsl::at(answer,0) == 'y')
                ok = true;
            cout << '\n';
        }
    }


}

void console::afiseazaLista() {
    iter_pair lst = farmacie.getAll();

    for (int i = 1; lst.first != lst.second; ++lst.first, ++i) {

        cout << "----Medicamentul #" << i << "----" << '\n';
        cout << lst.first->getAfis();
        cout << '\n';
    }
}

void console::sterge() {
    string line;

    cout << "STERGERE\n\n";

    bool ok = true;
    afiseazaLista();
    while (ok) {
        ok = false;
        cout << "Introdu codul medicamentului: ";
        string code;
        cin >> code;
        cout << '\n';

        const int med = stoi(code);
        try {
            farmacie.deleteElem(med);
        }
        catch (const RangeError& e) {
            cout << e.getMessage() << '\n' << "Incerci din nou?(y/n)";

            string answer;
            cin >> answer;
            if (gsl::at(answer, 0) == 'y')
                ok = true;
            cout << '\n';
        }
    }
}

void console::modifica() {
    string line;

    cout << "MODIFICARE\n\n";


    bool ok = true;
    while (ok) {
        ok = false;
        cout << "Introdu codul medicamentului: ";
        string code;
        cin >> code;
        cout << '\n';

        const int med = stoi(code);

        cout << "Introdu numele actualizat al medicamentului(sau -1 pentru a nu il actualiza): ";

        string nume;
        cin >> nume;
        cout << '\n';

        cout << "Introdu pretul actualizat al medicamentului(sau -1 pentru a nu il actualiza): ";
        string price;

        cin >> price;
        cout << '\n';

        cout << "Introdu producatorul actualizat al medicamentului(sau -1 pentru a nu il actualiza): ";
        string producator;
        cin >> producator;
        cout << '\n';

        cout << "Introdu substanta activa actualizata a medicamentului(sau -1 pentru a nu a o actualiza): ";
        string substanta;
        cin >> substanta;
        cout << '\n';
        try {
            farmacie.changeElem(med, nume, price, producator, substanta);
        }
        catch (const RangeError& e) {
            cout << e.getMessage() << '\n' << "Incerci din nou?(y/n)";

            string answer;
            cin >> answer;
            if (gsl::at(answer, 0) == 'n')
                ok = false;
            cout << '\n';
        }
        catch (const ValidationError& e) {
            cout << e.getMessage() << '\n' << "Incerci din nou?(y/n)";

            string answer;
            cin >> answer;
            if (gsl::at(answer, 0) == 'y')
                ok = true;
            cout << '\n';
        }
    }
}

void console::cautare() {
    string line;

    cout << "CAUTARE\n\n";


    bool ok = true;
    while (ok) {
        ok = false;
        cout << "Introdu numele medicamentului: ";

        string nume;
        cin >> nume;
        cout << '\n';

        cout << "Introdu producatorul medicamentului: ";
        string producator;
        cin >> producator;
        cout << '\n';

        try {
            entity elem = farmacie.searchElem(nume, producator);
            cout << elem.getAfis();
            cout << '\n';
        }
        catch (const ValidationError& e) {
            cout << e.getMessage() << '\n' << "Incerci din nou?(y/n)";

            string answer;
            cin >> answer;
            if (gsl::at(answer, 0) == 'y')
                ok = true;
            cout << '\n';
        }
    }

}

void console::afisare() {
    cout << "AFISARE\n";
    afiseazaLista();
}

void console::filtrare() {
    string line;
    cout << "FILTRARE\n";

    cout << "1. Filtrare dupa nume.\n";
    cout << "2. Filtrare dupa pret.\n";
    cout << "3. Filtrare dupa substanta.\n";
    cout << "Introdu numarul criteriului de filtrare: ";
    int crit;
    cin >> crit;
    cout << '\n';
    iter_pair result;
    string attr;
    bool ok = true;
    while (ok) {
        ok = false;
        switch (crit) {
        case 1:
            cout << "\nFILTRARE DUPA NUME\n";
            cout << "Introdu numele: ";

            cin >> attr;
            cout << '\n';
            try {
                result = farmacie.filterElems(attr, crit);
            }
            catch (const ValidationError& e) {
                cout << e.getMessage() << '\n' << "Incerci din nou?(y/n)";

                string answer;
                cin >> answer;
                if (gsl::at(answer, 0) == 'y')
                    ok = true;
                cout << '\n';
            }
            break;
        case 2:
            cout << "\nFILTRARE DUPA PRET\n";
            cout << "Introdu pretul: ";

            cin >> attr;
            cout << '\n';

            try {
                result = farmacie.filterElems(attr, crit);
            }
            catch (const ValidationError& e) {
                cout << e.getMessage() << '\n' << "Incerci din nou?(y/n)";

                string answer;
                cin >> answer;
                if (gsl::at(answer, 0) == 'y')
                    ok = true;
                cout << '\n';
            }
            break;
        case 3:
            cout << "\nFILTRARE DUPA SUBSTANTA ACTIVA\n";
            cout << "Introdu substanta: ";

            cin >> attr;
            cout << '\n';

            try {
                result = farmacie.filterElems(attr, crit);
            }
            catch (const ValidationError& e) {
                cout << e.getMessage() << '\n' << "Incerci din nou?(y/n)";

                string answer;
                cin >> answer;
                if (gsl::at(answer, 0) == 'y')
                    ok = true;
                cout << '\n';
            }
            break;
        default:
            cout << "Nu ai introdus un criteriu valid";
        }
    }
    for (; result.first != result.second; ++result.first) {
        cout << "------------------\n";
        cout << result.first->getAfis();
        cout << '\n';
    }
}

void console::sortare() {
    string line;
    cout << "SORTARE\n";

    cout << "1. Filtrare dupa nume.\n";
    cout << "2. Filtrare dupa producator.\n";
    cout << "3. Filtrare dupa substanta.\n";
    cout << "Introdu numarul criteriului de filtrare: ";
    int crit;
    cin >> crit;
    cout << '\n';

    farmacie.sortElems(crit);
}

void console::iesire() noexcept {
    return;
}