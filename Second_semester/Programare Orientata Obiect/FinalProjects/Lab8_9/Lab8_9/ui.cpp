#include "ui.h"

console::console(){
    functi.push_back(&console::adauga);
    functi.push_back(&console::sterge);
    functi.push_back(&console::modifica);
    functi.push_back(&console::cautare);
    functi.push_back(&console::afisare);
    functi.push_back(&console::filtrare);
    functi.push_back(&console::sortare);
    functi.push_back(&console::afiseazaRapoarte);
    functi.push_back(&console::undoOperatie);
    functi.push_back(&console::meniuReteta);
    functi.push_back(&console::iesire);
}

// typedef void(console::*comm)();
void console::run(){

    while(true){

        cout<<"COMENZI:\n";
        cout<<"1. Adauga medicament.    \n";
        cout<<"2. Sterge medicament.    \n";
        cout<<"3. Modifica medicament.  \n";
        cout<<"4. Cauta medicament.     \n";
        cout<<"5. Afiseaza medicamente. \n";
        cout<<"6. Filtreaza medicamente.\n";
        cout<<"7. Sorteaza medicamente. \n";
        cout<<"8. Afiseaza rapoartele producatorilor. \n";
        cout<<"9. Undo ultima operatie. \n";
        cout<<"10. MENIU RETETA. \n";
        cout<<"11. Iesi din aplicatie.   \n";
        cout<<'\n';
        cout<<"Introdu numarul comenzii: ";

        string answ;
        cin>>answ;
        cout<<'\n';
        
        int command = stoi(answ);
        cout<<"------------------------------\n";
        (this->*functi[command-1])();
        cout<<"------------------------------\n";


    }

}

void console::adaugaInReteta(){
    cout<<"---------------------\n";
    afisare();
    cout<<"---------------------\n";

    cout<<"Introdu numele medicamentului de adaugat: ";
    string nume;
    cin>>nume;
    cout<<'\n';

    reteta.adaugaPeReteta(nume);

}

void console::golesteReteta(){
    
    cout<<"---------------------\n";
    reteta.golesteReteta();
    cout<<"---------------------\n";
    
}

void console::genereazaReteta(){
    cout<<"---------------------\n";
    cout<<"Introdu numarul de medicamente de adaugat in reteta:";
    int nr;
    cin>>nr;
    cout<<"\n";
    reteta.genereazaReteta(nr);
    cout<<"\n\n";
    cout<<"AU FOST ADAUGATE "<<nr<<"MEDICAMENTE IN RETETA!\n";
    cout<<"---------------------\n";
    
}

void console::exportReteta(){
    cout<<"---------------------\n";
    cout<<"Introdu numele fisierului in care sa se exporte: ";
    string numeFisier;
    cin>>numeFisier;
    cout<<"\n";
    reteta.exportReteta(numeFisier);
    cout<<"RETETA EXPORTATA CU SUCCES!\n";
    cout<<"---------------------\n";

}

void console::meniuReteta(){
    cout<<"COMENZI PENTRU RETETA:\n";
    cout<<"1. Adauga medicament in reteta.\n";
    cout<<"2. Goleste reteta.\n";
    cout<<"3. Genereaza reteta.\n \n";
    cout<<"4. Exporta reteta. \n";

    cout<<"Introdu numarul comenzii: ";
    int com;
    cin>>com;
    cout<<'\n';

    switch(com){
        case 1:
            adaugaInReteta();
            break;
        case 2:
            golesteReteta();
            break;
        
        case 3:
            genereazaReteta();
            break;
        case 4:
            exportReteta();

    }
}

void console::adauga(){
    string line;
    
    cout<<"ADAUGARE\n\n";

    bool ok = true;
    while(ok){
        ok = false;
        cout<<"Introdu numele medicamentului: ";
        string nume;
        cin>>nume;
        cout<<'\n';

        cout<<"Introdu pretul medicamentului: ";
        
        string price;
        cin>>price;
        cout<<'\n';

        cout<<"Introdu producatorul medicamentului: ";
        
        string producator;
        cin>>producator;
        cout<<'\n';
        
        cout<<"Introdu substanta activa a medicamentului: ";
        string substanta;
        cin>>substanta;
        cout<<'\n';
        try{
            farmacie.addElem(nume, price, producator, substanta);
        }catch(ValidationError& e){
            cout<<e.getMessage()<<'\n'<<"Incerci din nou?(y/n)";

            string answer;
            cin>>answer;
            if(answer[0] == 'y')
                ok = true;
            cout<<'\n';
        }
    }


}

void console::afiseazaLista(){
    iter_pair lst = farmacie.getAll();

    for(int i=1;lst.first!=lst.second;++lst.first, ++i){
        cout<<lst.first->getAfis();
        cout<<'\n';
    }
}

void console::sterge(){
    string line;
    
    cout<<"STERGERE\n\n";

    bool ok = true;
    afiseazaLista();
    while(ok){
        ok = false;
        cout<<"Introdu codul medicamentului: ";
        string code;
        cin>>code;
        cout<<'\n';

        int med = stoi(code);
        try{
            farmacie.deleteElem(med);
        }catch(RangeError& e){
            cout<<e.getMessage()<<'\n'<<"Incerci din nou?(y/n)";

            string answer;
            cin>>answer;
            if(answer[0] == 'y')
                ok = true;
            cout<<'\n';
        }
    }
}

void console::modifica(){
    string line;
    
    cout<<"MODIFICARE\n\n";
    

    bool ok = true;
    while(ok){
        ok = false;
        cout<<"Introdu codul medicamentului: ";
        string code;
        cin>>code;
        cout<<'\n';

        int med = stoi(code);
        
        cout<<"Introdu numele actualizat al medicamentului(sau -1 pentru a nu il actualiza): ";

        string nume;
        cin>>nume;
        cout<<'\n';

        cout<<"Introdu pretul actualizat al medicamentului(sau -1 pentru a nu il actualiza): ";
        string price;

        cin>>price;
        cout<<'\n';

        cout<<"Introdu producatorul actualizat al medicamentului(sau -1 pentru a nu il actualiza): ";
        string producator;
        cin>>producator;
        cout<<'\n';
        
        cout<<"Introdu substanta activa actualizata a medicamentului(sau -1 pentru a nu a o actualiza): ";
        string substanta;
        cin>>substanta;
        cout<<'\n';
        try{
            farmacie.changeElem(med, nume, price, producator, substanta);
        }catch(RangeError& e){
            cout<<e.getMessage()<<'\n'<<"Incerci din nou?(y/n)";

            string answer;
            cin>>answer;
            if(answer[0] == 'n')
                ok = false;
            cout<<'\n';
        }catch(ValidationError& e){
            cout<<e.getMessage()<<'\n'<<"Incerci din nou?(y/n)";

            string answer;
            cin>>answer;
            if(answer[0] == 'y')
                ok = true;
        }
    }
}

void console::cautare(){
    string line;
    
    cout<<"CAUTARE\n\n";
    

    bool ok = true;
    while(ok){
        ok = false;
        cout<<"Introdu numele medicamentului: ";

        string nume;
        cin>>nume;
        cout<<'\n';

        cout<<"Introdu producatorul medicamentului: ";
        string producator;
        cin>>producator;
        cout<<'\n';
        
        try{
            entity elem = farmacie.searchElem(nume, producator);
            cout<<elem.getAfis();
            cout<<'\n';
        }catch(ValidationError& e){
            cout<<e.getMessage()<<'\n'<<"Incerci di#include <../undo/undo.h>n nou?(y/n)";

            string answer;
            cin>>answer;
            if(answer[0] == 'y')
                ok = true;
            cout<<'\n';
        }
    }
   
}

void console::afisare(){
    cout<<"AFISARE\n";
    afiseazaLista();
}

void console::filtrare(){
    string line;
    cout<<"FILTRARE\n";

    cout<<"1. Filtrare dupa nume.\n";
    cout<<"2. Filtrare dupa pret.\n";
    cout<<"3. Filtrare dupa substanta.\n";
    cout<<"Introdu numarul criteriului de filtrare: ";
    int crit;
    cin>>crit;
    cout<<'\n';
    iter_pair result;
    string attr;
    bool ok = true;
    while(ok){
        ok = false;
        switch(crit){
            case 1:
                cout<<"\nFILTRARE DUPA NUME\n";
                cout<<"Introdu numele: ";

                cin>>attr;
                cout<<'\n';
                try{
                    result = farmacie.filterElems(attr, crit);
                }catch(ValidationError& e){
                    cout<<e.getMessage()<<'\n'<<"Incerci din nou?(y/n)";

                    string answer;
                    cin>>answer;
                    if(answer[0] == 'y')
                        ok = true;
                    cout<<'\n';
                }
                break;
            case 2:
                cout<<"\nFILTRARE DUPA PRET\n";
                cout<<"Introdu pretul: ";

                cin>>attr;
                cout<<'\n';

                try{
                    result = farmacie.filterElems(attr, crit);
                }catch(ValidationError& e){
                    cout<<e.getMessage()<<'\n'<<"Incerci din nou?(y/n)";

                    string answer;
                    cin>>answer;
                    if(answer[0] == 'y')
                        ok = true;
                    cout<<'\n';
                }
                break;
            case 3:
                cout<<"\nFILTRARE DUPA SUBSTANTA ACTIVA\n";
                cout<<"Introdu substanta: ";

                cin>>attr;
                cout<<'\n';

                try{
                    result = farmacie.filterElems(attr, crit);
                }catch(ValidationError& e){
                    cout<<e.getMessage()<<'\n'<<"Incerci din nou?(y/n)";

                    string answer;
                    cin>>answer;
                    if(answer[0] == 'y')
                        ok = true;
                    cout<<'\n';
                }
                break;
        }
    }
    for(;result.first!=result.second;++result.first){
        cout<<"------------------\n";
        cout<<result.first->getAfis();
        cout<<'\n';
    }
}

void console::sortare(){
    string line;
    cout<<"SORTARE\n";

    cout<<"1. Filtrare dupa nume.\n";
    cout<<"2. Filtrare dupa producator.\n";
    cout<<"3. Filtrare dupa substanta.\n";
    cout<<"Introdu numarul criteriului de filtrare: ";
    int crit;
    cin>>crit;
    cout<<'\n';

    farmacie.sortElems(crit);
}

void console::iesire(){
    
    exit(0);
}

void console::undoOperatie(){
    try{
        farmacie.UNDO();
        cout<<"Undo realizat cu succes!\n";
    }catch(RangeError& e){
        cout<<e.getMessage()<<'\n';
    }
}

void console::afiseazaRapoarte(){
    pair<unordered_map<string, int>::iterator,unordered_map<string, int>::iterator> to_iter = farmacie.getReports();

    for(;to_iter.first!= to_iter.second; ++to_iter.first){
        std::cout<<"Producatorul "<< to_iter.first->first<<" are "<<to_iter.first->second<<
        (to_iter.first->second ==1 ? " medicament" : " medicamente")<<'\n';
    }
}