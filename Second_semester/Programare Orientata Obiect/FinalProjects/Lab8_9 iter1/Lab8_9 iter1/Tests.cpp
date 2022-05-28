#include <assert.h>
#include <algorithm>
#include "Tests.h"
#include "Generator.h"
#include "Service.h"
#include "entity.h"

void _test_entity() {
    entity auxiliary("denumire", 100, "alfa", "beta");

    assert(auxiliary.getName() == "denumire");
    assert(auxiliary.getPrice() == 100);
    assert(auxiliary.getManufacturer() == "alfa");
    assert(auxiliary.getSubstance() == "beta");

    assert(auxiliary.getAfis() == "-----> Medicamentul #0\nNumele medicamentului este: denumire\nPretul medicamentului este: 100.000000\nProducatorul medicamentului este: alfa\nSubstanta activa a medicamentului este: beta\n");

    auxiliary.setName("aaaa");
    auxiliary.setPrice(200);
    auxiliary.setManufacturer("aaaa");
    auxiliary.setSubstance("aaaa");

    assert(auxiliary.getName() == "aaaa");
    assert(auxiliary.getPrice() == 200);
    assert(auxiliary.getManufacturer() == "aaaa");
    assert(auxiliary.getSubstance() == "aaaa");

    entity auxiliary_2("denumire", 100, "alfa", "beta");
    assert(auxiliary != auxiliary_2);
}

void _test_addElem() {
    generator gen;
    repository test_subject;
    for (int i = 0; i < 100; ++i) {
        entity aux = gen.genEntity();

        int code = test_subject.addElem(aux);
        assert(test_subject.getElem(code) == aux);
        assert(test_subject.getNrElems() - 1 == i);
    }
    assert(test_subject.getNrElems() == 100);

}

void _test_removeElem() {
    generator gen;
    repository test_subject;
    vector<int>codes;
    for (int i = 0; i < 100; ++i) {

        entity aux = gen.genEntity();
        codes.push_back(test_subject.addElem(aux));
    }

    for (int i = 0; i < 50; ++i) {
        test_subject.removeElem(codes[i]);
    }
    assert(test_subject.getNrElems() == 50);

    for (int i = 49; i >= 0; i--) {
        test_subject.removeElem(codes[i]);
    }
    assert(test_subject.getNrElems() == 0);

}

void _test_changeElement() {
    generator gen;
    repository test_subject;
    vector<entity> memory;
    vector<int>codes;

    for (int i = 0; i < 100; ++i) {
        entity aux = gen.genEntity();
        memory.push_back(aux);

        codes.push_back(test_subject.addElem(aux));
    }
    for (int i = 0; i < 100; ++i) {
        entity aux = gen.genEntity();

        if (i % 2 == 0) {
            test_subject.changeElement(codes[i], aux);
            assert(aux == test_subject.getElem(codes[i]));
        }
        else
            assert(memory[i] == test_subject.getElem(codes[i]));
    }

}


void _test_getAll() {
    generator gen;
    repository test_subject;
    vector<int>codes;

    for (int i = 0; i < 100; ++i) {
        entity aux = gen.genEntity();

        codes.push_back(test_subject.addElem(aux));
    }

    iter_pair res = test_subject.getAll();


    for (int i = 0; i < test_subject.getNrElems() && res.first != res.second; ++res.first, ++i) {
        assert(*(res.first) == test_subject.getElem(codes[i]));
    }

}

void _test_comparator_nume() {

    assert(comparator_nume(entity("bbbb", 300, "aaaa", "bbbb"), entity("cccc", 400, "aaaa", "cccc")) == true);
    assert(comparator_nume(entity("cccc", 200, "aaaa", "cccc"), entity("cccc", 400, "aaaa", "cccc")) == true);
}

void _test_rapoarte() {
    repository test_subject;
    repository_report raport_test;
    generator gen;
    service test_farmacie;
    vector<entity>memory;
    pair<unordered_map<string, int>::iterator, unordered_map<string, int>::iterator> reports;

    entity aux = gen.genEntity();
    memory.push_back(aux);
    int code = test_subject.addElem(aux);

    entity aux_1 = gen.genEntity();
    memory.push_back(aux_1);
    code = test_subject.addElem(aux_1);

    entity aux_2 = gen.genEntity();
    memory.push_back(aux_2);
    code = test_subject.addElem(aux_2);

    raport_test.addItem(aux.getManufacturer());
    raport_test.addItem(aux_1.getManufacturer());
    assert(raport_test.getItem(aux_2.getManufacturer()) == -1);
    assert(raport_test.getItem(aux.getManufacturer()) == 1);

    raport_test.removeItem(aux.getManufacturer());
    reports = test_farmacie.getReports();
    raport_test.removeItem(aux_1.getManufacturer());

    try {
        raport_test.removeItem(aux_2.getManufacturer());
    }
    catch (const RangeError& e) {
        assert(e.getMessage() == "Elementul nu exista in rapoarte.");
    }
}

void _test_sort() {
    repository auxiliary;
    service test_subject;
    vector<int>codes;
    codes.push_back(auxiliary.addElem(entity("aaaa", 100, "bbbb", "cccc")));
    codes.push_back(auxiliary.addElem(entity("aaaa", 200, "bbbb", "aaaa")));
    codes.push_back(auxiliary.addElem(entity("bbbb", 300, "aaaa", "bbbb")));
    codes.push_back(auxiliary.addElem(entity("cccc", 400, "aaaa", "cccc")));

    test_subject.sortElems(0);
    assert(auxiliary.getElem(codes[0]).getPrice() == 100);
    auxiliary.sortElems(1);
    assert(auxiliary.getElem(codes[0]).getPrice() == 300);
    auxiliary.sortElems(2);
    assert(auxiliary.getElem(codes[0]).getPrice() == 200);
    try {
        auxiliary.sortElems(3);
    }
    catch (const RangeError& e) {
        assert(e.getMessage() == "Introduceti un cod valabil");
    }
}

void _test_addElemS() {
    service test_subject;
    generator gen;

    for (int i = 0; i < 100; ++i) {
        test_subject.addElem(gen.genString(), "100", gen.genString(), gen.genString());
        assert(test_subject.getNrElems() == i + 1);
    }
    // test invalid name
    try {
        test_subject.addElem("-1", "1000", gen.genString(), gen.genString());
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.addElem("", "1000", gen.genString(), gen.genString());
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "Niciun nume primit");
    }
    try {
        test_subject.addElem("1254", "1000", gen.genString(), gen.genString());
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "Numele nu poate contine valori numerice");
    }

    //test invalid price
    try {
        test_subject.addElem(gen.genString(), "-1", gen.genString(), gen.genString());
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.addElem(gen.genString(), "", gen.genString(), gen.genString());
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "Niciun pret primit");
    }
    try {
        test_subject.addElem(gen.genString(), "10a0", gen.genString(), gen.genString());
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "Pretul nu poate contine litere");
    }

    //test invalid manufacturer
    try {
        test_subject.addElem(gen.genString(), "1000", "-1", gen.genString());
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.addElem(gen.genString(), "1000", "", gen.genString());
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "Niciun producator primit");
    }
    try {
        test_subject.addElem(gen.genString(), "1000", "123", gen.genString());
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "Producatorul nu poate contine valori numerice");
    }

    //test invalid substance
    try {
        test_subject.addElem(gen.genString(), "1000", gen.genString(), "-1");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.addElem(gen.genString(), "1000", gen.genString(), "");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "Nicio substanta primita");
    }

}

void _test_deleteElemS() {
    service test_subject;
    generator gen;
    vector<unsigned int> codes;
    for (int i = 0; i < 100; ++i) {
        unsigned int code = test_subject.addElem(gen.genString(), "1000", gen.genString(), gen.genString());
        codes.push_back(code);
    }
    for (int i = 0; i < 50; ++i) {
        test_subject.deleteElem(codes[i]);
    }

    try {
        test_subject.deleteElem(51);
    }
    catch (const RangeError& e) {
        assert(e.getMessage() == "Invalid code.");
    }

    assert(test_subject.getNrElems() == 50);
}

void _test_changeElemS() {
    service test_subject;
    generator gen;
    vector<unsigned int>codes;
    for (int i = 0; i < 100; ++i) {
        int code = test_subject.addElem(gen.genString(), "100", gen.genString(), gen.genString());
        codes.push_back(code);
    }
    for (int i = 0; i < 100; ++i) {
        entity aux(gen.genString(), 1000, gen.genString(), gen.genString());
        test_subject.changeElem(codes[i], aux.getName(), "1000", aux.getManufacturer(), gen.genString());
        assert(test_subject.getElem(codes[i]) == aux);
    }
    try {
        test_subject.changeElem(101, gen.genString(), "1000", gen.genString(), gen.genString());
    }
    catch (const RangeError& e) {
        assert(e.getMessage() == "Invalid code.");
    }
    try {
        test_subject.changeElem(codes[2], "-1", "-1", "-1", "-1");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.changeElem(codes[2], gen.genString(), "-1", "-1", "-1");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.changeElem(codes[2], gen.genString(), "100", "-1", "-1");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.changeElem(codes[2], gen.genString(), "100", gen.genString(), "-1");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }

}

void _test_searchElemS() {
    service test_subject;

    test_subject.addElem("asdf", "1000", "asdf", "asdf");
    test_subject.addElem("oooo", "1000", "asdf", "asdf");
    test_subject.addElem("bbbb", "1000", "asdf", "asdf");
    test_subject.addElem("cccc", "1000", "asdf", "asdf");

    assert(test_subject.searchElem("oooo", "asdf") == entity("oooo", 1000, "asdf", "asdf"));
    assert(test_subject.searchElem("bbbb", "asdf") == entity("bbbb", 1000, "asdf", "asdf"));
    assert(test_subject.searchElem("cccc", "asdf") == entity("cccc", 1000, "asdf", "asdf"));

    assert(test_subject.searchElem("-1", "asdf") == entity("asdf", 1000, "asdf", "asdf"));
    assert(test_subject.searchElem("cccc", "-1") == entity("cccc", 1000, "asdf", "asdf"));
    try {
        assert(test_subject.searchElem("bbbc", "asrf") == entity("bbbb", 1000, "asdf", "asdf"));
    }
    catch (const RangeError& e) {
        assert(e.getMessage() == "No element found");
    }
}

void _test_filterElems() {
    service test_subject;

    test_subject.addElem("dddd", "1126", "eeee", "yyyy");
    test_subject.addElem("oooo", "2738", "bbbb", "tttt");
    test_subject.addElem("bbbb", "9384", "zzzz", "pppp");
    test_subject.addElem("cccc", "1287", "wwww", "aaaa");

    iter_pair result;

    // test prim criteriu
    result = test_subject.filterElems("oooo", 1);
    assert(result.first->getSubstance() == "tttt");
    try {
        result = test_subject.filterElems("-1", 1);
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }

    // test al doilea criteriu
    result = test_subject.filterElems("9384", 2);
    assert(result.first->getName() == "bbbb");
    try {
        result = test_subject.filterElems("-1", 2);
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }

    // test al treilea criteriu
    result = test_subject.filterElems("aaaa", 3);
    assert(result.first->getName() == "cccc");
    try {
        result = test_subject.filterElems("-1", 3);
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }

    // test criteriu invalid
    try {
        result = test_subject.filterElems("-1", 4);
    }
    catch (const RangeError& e) {
        assert(e.getMessage() == "Invalid crit.");
    }

    // test getAll()
    result = test_subject.getAll();
    assert(result.first->getName() == "dddd");
}

void _test_reteta() {
    generator gen;
    service test_farmacie;
    service_reteta test_subject = service_reteta(test_farmacie);
    vector<int>codes;

    int code = test_farmacie.addElem("aaaa", "100", gen.genString(), gen.genString());
    codes.push_back(code);
    code = test_farmacie.addElem("bbbb", "100", gen.genString(), gen.genString());
    codes.push_back(code);
    code = test_farmacie.addElem("cccc", "100", gen.genString(), gen.genString());
    codes.push_back(code);

    test_subject.adaugaPeReteta("aaaa");
    test_subject.golesteReteta();
    test_subject.genereazaReteta(2);
    test_subject.exportReteta("test.csv");
}

void run_all_tests() {
    // entity
    _test_entity();
    // repository
    _test_addElem();
    _test_removeElem();
    _test_changeElement();
    _test_getAll();
    _test_comparator_nume();
    _test_rapoarte();
    // service
    _test_sort();
    _test_addElemS();
    _test_deleteElemS();
    _test_changeElemS();
    _test_searchElemS();
    _test_filterElems();
    _test_reteta();
}