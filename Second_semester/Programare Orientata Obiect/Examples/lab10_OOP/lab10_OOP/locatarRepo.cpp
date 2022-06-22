#include "locatarRepo.h"
#include <assert.h>
#include <sstream>
#include <fstream>
#include <algorithm>
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::find_if;

bool LocatarRepo::exist(const Locatar& l)const
{
    try {
        find(l.getApartment());
        return true;
    }
    catch (LocatarRepoException&) {
        return false;
    }
}

void LocatarRepo::store(const Locatar& l)
{
    if (exist(l)) {
        throw LocatarRepoException("Exista deja locatar apartament: " + l.getApartment());
    }
    all.push_back(l);
}

const Locatar& LocatarRepo::find(int apartment)const
{
    /* vector<Locatar>::iterator f = std::find_if(this->all.begin(), this->all.end(), [=](const Locatar& l) {
         return l.getApartment() == apartment; });
     for (auto& l : all)
     {
         if (l.getApartment() == apartment)
             return l;
     }
     throw LocatarRepoException("Nu exista locatar apartament: " + apartment);*/
     /*vector<Locatar>::iterator*/
    auto f = std::find_if(this->all.begin(), this->all.end(),
        [=](const Locatar& s) {
            return s.getApartment() == apartment;
        });

    if (f != this->all.end())
        return (*f);
    else
        throw LocatarRepoException("Nu exista locatar apartament: " + apartment);
}

void LocatarRepo::deletePos(int apartment)
{
    int index = -1;
    for (int i = 0; i < all.size(); i++)
        if (all[i].getApartment() == apartment)
            index = i;
    if (index < 0)
        throw LocatarRepoException("apartament invalid");
    all.erase(all.begin() + index);
}

void LocatarRepo::modifyPos(int apartment, const Locatar& l)
{
    bool apare = 0;
    for (int i = 0; i < all.size(); i++)
        if (all[i].getApartment() == apartment) {
            all[i] = l;
            apare = 1;
            break;
        }
    if (apare == 0)
        throw LocatarRepoException("apartament invalid");
}

const vector<Locatar>& LocatarRepo::getAll() const noexcept
{
    return all;
}

ostream& operator<<(ostream& out, const LocatarRepoException& ex)
{
    out << ex.msg;
    return out;
}


void testeRepo() {
    LocatarRepo rep;
    rep.store(Locatar{ 1,"a",10,"b" });
    assert(rep.getAll().size() == 1);
    assert(rep.find(1).getSurface() == 10);
    rep.store(Locatar{ 2,"c",5,"d" });
    assert(rep.getAll().size() == 2);
    try {
        rep.store(Locatar{ 1,"a",2,"c" });
        assert(false);
    }
    catch (const LocatarRepoException&) {
        assert(true);
    }
    try {
        rep.find(12);
        assert(false);
    }
    catch (const LocatarRepoException& e) {
        std::stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
    rep.modifyPos(1, { 1,"aa",100,"bb" });
    assert(rep.find(1).getName() == "aa");
    try {
        rep.modifyPos(22, { 1,"aa",100,"bb" });
        assert(false);
    }
    catch (const LocatarRepoException& e) {
        std::stringstream os;
        os << e;
        assert(os.str().find("invalid") >= 0);
    }
    rep.deletePos(1);
    assert(rep.getAll().size() == 1);
    try {
        rep.deletePos(22);
        assert(false);
    }
    catch (const LocatarRepoException& e) {
        std::stringstream os;
        os << e;
        assert(os.str().find("invalid") >= 0);
    }
    testeFileRepo();
}


void LocatarRepoFile::loadFromFile()
{
    ifstream locatarFile(this->filename);
    if (!locatarFile.is_open()) {
        throw LocatarRepoException("Cannot read from file " + filename);
    }
    string line;
    while (getline(locatarFile, line)) {
        string name, type;
        int apartment = 0, surface = 0;
        stringstream linestream(line);
        string current_item;
        int item_no = 0;
        while (getline(linestream, current_item, ',')) {
            if (item_no == 0)apartment = stoi(current_item);
            if (item_no == 1)name = current_item;
            if (item_no == 2)surface = stoi(current_item);
            if (item_no == 3)type = current_item;
            item_no++;
        }
        Locatar l{ apartment,name,surface,type };
        LocatarRepo::store(l);
    }
    locatarFile.close();
}

void LocatarRepoFile::saveToFile()
{
    ofstream locatarOutput(this->filename);
    if (!locatarOutput.is_open())
        throw LocatarRepoException("Cannot write to file" + filename);
    for (auto& loc : getAll()) {
        locatarOutput << loc.getApartment() << "," << loc.getName() << "," << loc.getSurface() << "," << loc.getType() << "\n";
    }
    locatarOutput.close();
}

void LocatarRepoFile::store(const Locatar& l)
{
    LocatarRepo::store(l);
    saveToFile();
}

void testeFileRepo()
{
    std::ofstream of;
    of.open("test.txt", std::ofstream::out | std::ofstream::trunc);
    of << "1,Ion,120,garsoniera\n";
    of << "2, Ionel, 200, apartament\n";
    of << "3, Ionut, 11, garsoniera\n";
    of << "4, Ioana, 360, duplex\n";
    of.close();
    try {
        LocatarRepoFile testRepoF{ "test2.txt" };
        assert(false);
    }
    catch (LocatarRepoException&) {
        assert(true);
    }
    LocatarRepoFile testRepoF{ "test.txt" };
    assert(testRepoF.getAll().size() == 4);
    Locatar loc{ 10,"Ioan",2000,"tip2" };
    testRepoF.store(loc);
    assert(testRepoF.getAll().size() == 5);
}