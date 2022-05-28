#include <assert.h>
#include <algorithm>
#include "Tests.h"
#include "Generator.h"
#include "Service.h"

void test_entity() {
    entity auxiliary("denumire", 100, "alfa", "beta");

    assert(auxiliary.getName() == "denumire");
    assert(auxiliary.getPrice() == 100);
    assert(auxiliary.getManufacturer() == "alfa");
    assert(auxiliary.getSubstance() == "beta");

    assert(auxiliary.getAfis() == "Numele medicamentului este: denumire\nPretul medicamentului este: 100.000000\nProducatorul medicamentului este: alfa\nSubstanta activa a medicamentului este: beta\n");

    auxiliary.setName("aaaa");
    auxiliary.setPrice(200);
    auxiliary.setManufacturer("aaaa");
    auxiliary.setSubstance("aaaa");

    assert(auxiliary.getName() == "aaaa");
    assert(auxiliary.getPrice() == 200);
    assert(auxiliary.getManufacturer() == "aaaa");
    assert(auxiliary.getSubstance() == "aaaa");

}

void test_addElem() {
    generator gen;
    repository test_subject;
    for (int i = 0; i < 100; ++i) {
        entity aux = gen.genEntity();

        test_subject.addElem(aux);
        assert(test_subject.getElem(i) == aux);
        assert(test_subject.getNrElems() - 1 == i);
    }
    assert(test_subject.getNrElems() == 100);

}

void test_removeElem() {
    generator gen;
    repository test_subject;

    entity aux = gen.genEntity();
    test_subject.addElem(aux);
    assert(test_subject.getNrElems() == 1);

    test_subject.removeElem(0);
    assert(test_subject.getNrElems() == 0);

    for (int i = 0; i < 100; ++i) {

        entity aux = gen.genEntity();
        test_subject.addElem(aux);
    }

    for (int i = 0; i < 100; i += 2) {
        test_subject.removeElem(i);
    }
    assert(test_subject.getNrElems() == 50);

    for (int i = 1; i < 100; i += 2) {
        test_subject.removeElem(i);
    }
    assert(test_subject.getNrElems() == 0);
}

void test_changeElement() {
    generator gen;
    repository test_subject;
    vector<entity> memory;
    for (int i = 0; i < 100; ++i) {
        entity aux = gen.genEntity();
        memory.push_back(aux);

        test_subject.addElem(aux);
    }
    for (int i = 0; i < 100; i += 2) {
        entity aux = gen.genEntity();

        test_subject.changeElement(i, aux);

        if (i % 2 == 0)
            assert(aux == test_subject.getElem(i));
    }

}


void test_getAll() {
    generator gen;
    repository test_subject;

    for (int i = 0; i < 100; ++i) {
        entity aux = gen.genEntity();

        test_subject.addElem(aux);
    }

    iter_pair res = test_subject.getAll();

    if (&res.first != nullptr) {
        for (int i = 0; i < test_subject.getNrElems() && res.first != res.second; ++res.first, ++i) {
            assert(*(res.first) == test_subject.getElem(i));
        }
    }
}

void test_comparator_nume() {

    assert(comparator_nume(entity("bbbb", 300, "aaaa", "bbbb"), entity("cccc", 400, "aaaa", "cccc")) == true);
    assert(comparator_nume(entity("cccc", 200, "aaaa", "cccc"), entity("cccc", 400, "aaaa", "cccc")) == true);
}

void test_sort() {
    repository auxiliary;
    service test_subject;
    auxiliary.addElem(entity("aaaa", 100, "bbbb", "cccc"));
    auxiliary.addElem(entity("aaaa", 200, "bbbb", "aaaa"));
    auxiliary.addElem(entity("bbbb", 300, "aaaa", "bbbb"));
    auxiliary.addElem(entity("cccc", 400, "aaaa", "cccc"));

    test_subject.sortElems(0);
    assert(auxiliary.getElem(0).getPrice() == 100);
    auxiliary.sortElems(1);
    assert(auxiliary.getElem(0).getPrice() == 300);
    auxiliary.sortElems(2);
    assert(auxiliary.getElem(0).getPrice() == 200);
    try {
        auxiliary.sortElems(3);
    }
    catch (const RangeError& e) {
        assert(e.getMessage() == "Introduceti un cod valabil");
    }
}

void test_addElemS() {
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

void test_deleteElemS() {
    service test_subject;
    generator gen;

    for (int i = 0; i < 100; ++i) {
        test_subject.addElem(gen.genString(), "1000", gen.genString(), gen.genString());

    }
    for (int i = 0; i < 50; ++i) {
        test_subject.deleteElem(i);
    }

    try {
        test_subject.deleteElem(51);
    }
    catch (const RangeError& e) {
        assert(e.getMessage() == "Index out of range");
    }

    assert(test_subject.getNrElems() == 50);
}

void test_changeElemS() {
    service test_subject;
    generator gen;

    for (int i = 0; i < 100; ++i) {
        test_subject.addElem(gen.genString(), "100", gen.genString(), gen.genString());
    }
    for (int i = 0; i < 100; ++i) {
        entity aux(gen.genString(), 1000, gen.genString(), gen.genString());
        test_subject.changeElem(i, aux.getName(), "1000", aux.getManufacturer(), gen.genString());
        assert(test_subject.getElem(i) == aux);
    }
    try {
        test_subject.changeElem(101, gen.genString(), "1000", gen.genString(), gen.genString());
    }
    catch (const RangeError& e) {
        assert(e.getMessage() == "Index out of range");
    }
    try {
        test_subject.changeElem(2, "-1", "-1", "-1", "-1");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.changeElem(2, gen.genString(), "-1", "-1", "-1");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.changeElem(2, gen.genString(), "100", "-1", "-1");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }
    try {
        test_subject.changeElem(2, gen.genString(), "100", gen.genString(), "-1");
    }
    catch (const ValidationError& e) {
        assert(e.getMessage() == "invalid");
    }

}

void test_searchElemS() {
    service test_subject;

    test_subject.addElem("asdf", "1000", "asdf", "asdf");
    test_subject.addElem("oooo", "1000", "asdf", "asdf");
    test_subject.addElem("bbbb", "1000", "asdf", "asdf");
    test_subject.addElem("cccc", "1000", "asdf", "asdf");

    assert(test_subject.searchElem("oooo", "asdf") == entity("oooo", 1000, "asdf", "asdf"));
    assert(test_subject.searchElem("bbbb", "asdf") == entity("bbbb", 1000, "asdf", "asdf"));
    assert(test_subject.searchElem("cccc", "asdf") == entity("cccc", 1000, "asdf", "asdf"));
    try {
        assert(test_subject.searchElem("bbbc", "asrf") == entity("bbbb", 1000, "asdf", "asdf"));
    }
    catch(const RangeError &e) {
        assert(e.getMessage() == "No element found");
    }
}

void test_filterElems() {
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

void run_tests() {
    // entity
    test_entity();
    // repository
    test_addElem();
    test_removeElem();
    test_changeElement();
    test_getAll();
    test_comparator_nume();
    // service
    test_sort();
    test_addElemS();
    test_deleteElemS();
    test_changeElemS();
    test_searchElemS();
    test_filterElems();
}