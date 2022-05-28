//
// Created by david on 27.03.2022.
//

#include <cassert>
#include <iostream>
#include <sstream>
#include "Tests.h"
#include "Medicament.h"
#include "Repo.h"
#include "Service.h"


void Tests::runAll() {
    createDestroyTest();

    addRepoTest();
    delRepoTest();
    modRepoTest();

    addSrvTest();
    delSrvTest();
    std::cout << "tests ok";
}

void Tests::createDestroyTest() {
    Movie m{ "enter the void", "psychedelic", 2009, "Oscar" };
    assert(m.title() == "enter the void");
    assert(m.genre() == "psychedelic");
    assert(m.year() == 2009);
    assert(m.protagonist() == "Oscar");
    Movie m2{ "enter the void", "psychedelic", 2009, "Oscar" };
    assert(m == m2);
    m2.set_genre("newgenre");
    m2.set_protagonist("protag");
    m2.set_year(1999);
    assert(m2.protagonist() == "protag");
    assert(m2.year() == 1999);
    assert(m2.genre() == "newgenre");
    m = m2;
    assert(m.protagonist() == "protag");
    assert(m.year() == 1999);
    assert(m.genre() == "newgenre");
}

void Tests::addRepoTest() {
    Repo repo;
    Movie m{ "enter the void", "psychedelic", 2009, "Oscar" };
    repo.add(m);
    assert(repo.getAll().size() == 1);
    Movie found = repo.find("enter the void", 2009);
    assert(found == m);
    Movie m2{ "La Double Vie De Veronique", "Drama", 1996, "Veronika" };
    repo.add(m2);
    found = repo.find("La Double Vie De Veronique", 1996);
    assert(found == m2);
    assert(repo.getAll().size() == 2);
    ///adaugare multiplă !
    try {
        repo.add(m);
        assert(false);
    }
    catch (RepoException& e) {
        assert(true);
    }
    //cauta inexistent
    try {
        repo.find("c", 1990);
        assert(false);
    }
    catch (const RepoException& e) {
        std::stringstream os;
        os << e;
        assert(os.str().find("nu exista") >= 0);
    }
}

void Tests::addSrvTest() {
    Repo r;
    Service srv{ r };
    srv.add("Enter The Void", "Psychedelic", 2009, "Oscar");
    assert(r.getAll().size() == 1);
    try {
        ///adăugare multiplă
        srv.add("Enter The Void", "a", 2009, "a");
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void Tests::delRepoTest() {
    Repo repo;
    Movie m{ "enter the void", "psychedelic", 2009, "Oscar" };
    repo.add(m);
    Movie m2{ "La Double Vie De Veronique", "Drama", 1996, "Veronika" };
    repo.add(m2);
    repo.del(m);
    assert(repo.getAll().size() == 1);
    repo.del(m2);
    assert(repo.getAll().empty());
    try {
        repo.del(m);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }

}

void Tests::delSrvTest() {
    Repo repo;
    Movie m{ "enter the void", "psychedelic", 2009, "Oscar" };
    repo.add(m);
    Movie m2{ "La Double Vie De Veronique", "Drama", 1996, "Veronika" };
    repo.add(m2);
    Service srv{ repo };
    srv.del("enter the void", 2009);
    assert(srv.getAll().size() == 1);
    srv.del("La Double Vie De Veronique", 1996);
    assert(srv.getAll().empty());
    try {
        srv.del("foo", 1);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void Tests::modRepoTest() {
    Repo repo;
    Movie m{ "enter the void", "psychedelic", 2009, "Oscar" };
    repo.add(m);
    Movie m2{ "La Double Vie De Veronique", "Drama", 1996, "Veronika" };
    repo.add(m2);
    Movie newM{ "enter the void", "psy", 2009, "osky" };
    repo.modify(newM);
    assert(repo.find("enter the void", 2009).genre() == "psy"
        && repo.find("enter the void", 2009).protagonist() == "osky");
    try {
        Movie mm{ "foo", "foo", 1, "foo" };
        repo.modify(mm);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void Tests::modSrvTest() {
    Repo repo;
    Movie m{ "enter the void", "psychedelic", 2009, "Oscar" };
    repo.add(m);
    Movie m2{ "La Double Vie De Veronique", "Drama", 1996, "Veronika" };
    repo.add(m2);
    Service srv{ repo };
    srv.mod("enter the void", 2009, "psy", "osky");
    assert(repo.find("enter the void", 2009).genre() == "psy"
        && repo.find("enter the void", 2009).protagonist() == "osky");
    try {
        srv.mod("foo", 1, "foo", "foo");
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}
