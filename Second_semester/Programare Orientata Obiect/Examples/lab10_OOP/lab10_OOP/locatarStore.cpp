#include "locatarStore.h"
#include <assert.h>
#include "export.h"
#include <map>

//vector<Locatar> LocatarStore::generalSort(bool(*maiMicF)(const Locatar&, const Locatar&))
//{
//	vector<Locatar> v{ rep.getAll() };//fac o copie	
//	for (size_t i = 0; i < v.size(); i++) {
//		for (size_t j = i + 1; j < v.size(); j++) {
//			if (!maiMicF(v[i], v[j])) {
//				//interschimbam
//				Locatar aux = v[i];
//				v[i] = v[j];
//				v[j] = aux;
//			}
//		}
//	}
//	return v;
//}
//
//vector<Locatar> LocatarStore::filter(function<bool(const Locatar&)> fct)
//{
//	vector<Locatar> rez;
//	for (const auto& locatar : rep.getAll()) {
//		if (fct(locatar)) {
//			rez.push_back(locatar);
//		}
//	}
//	return rez;
//}

LocatarStore::~LocatarStore()
{
}

void LocatarStore::addLocatar(int apartment, const string name, int surface, const string type)
{
	Locatar l{ apartment, name, surface, type };
	val.validate(l);
	rep.store(l);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, l));
}

int LocatarStore::typeNumber(const string& type)
{
	std::map<string,int> raport;
	for (auto i : getAll()) {
		raport[i.getType()]++;
	}
	for (auto i : raport) {
		if (i.first == type)
			return i.second;
	}
	return 0;
}

void LocatarStore::undo()
{
	if (undoActions.empty()) {
		throw LocatarRepoException{ "No more undo" };
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void LocatarStore::delLocatar(int apartment)
{
	Locatar l = findLocatar(apartment);
	rep.deletePos(apartment);

	undoActions.push_back(std::make_unique<UndoSterge>(rep, l));
}

void LocatarStore::modifLocatar(int apartment, const string name, int surface, const string type)
{
	Locatar lInitial = findLocatar(apartment);
	Locatar l{ apartment, name, surface, type };
	val.validate(l);
	rep.modifyPos(apartment, l);
	undoActions.push_back(std::make_unique<UndoModifica>(rep, lInitial));
}

Locatar LocatarStore::findLocatar(int apartment)
{
	try {
		return rep.find(apartment);
	}
	catch (LocatarRepoException) {
		return { -1,"",-1,"" };
	}
}

vector<Locatar> LocatarStore::filterType(string tip)
{
	const vector<Locatar>& all = getAll();
	vector<Locatar> filteredLocatar;
	std::copy_if(all.begin(), all.end(), back_inserter(filteredLocatar),
		[tip](const Locatar& m) {
			return m.getType() == tip;
		});
	return filteredLocatar;
	/*return filter([tip](const Locatar& l) {
		return l.getType() == tip;
		});*/
}

vector<Locatar> LocatarStore::filterSurface(int suprafata)
{
	const vector<Locatar>& all = getAll();
	vector<Locatar> filteredLocatar;
	std::copy_if(all.begin(), all.end(), back_inserter(filteredLocatar),
		[suprafata](const Locatar& m) {
			return m.getSurface() <= suprafata;
		});
	return filteredLocatar;
	/*return filter([suprafata](const Locatar& l) {
		return l.getSurface() < suprafata;
		});*/
}

vector<Locatar> LocatarStore::sortName()
{
	vector<Locatar> sortedCopy{ getAll() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpName);
	return sortedCopy;
}

vector<Locatar> LocatarStore::sortSurface()
{
	vector<Locatar> sortedCopy{ getAll() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpSurface);
	return sortedCopy;
}

vector<Locatar> LocatarStore::sortTypeSurface()
{
	vector<Locatar> sortedCopy{ getAll() };
	sort(sortedCopy.begin(), sortedCopy.end(), [](const Locatar& l1, const Locatar& l2) {
		if (l1.getType() == l2.getType()) {
			return l1.getSurface() < l2.getSurface();
		}
		return l1.getType() < l2.getType();
		});
	return sortedCopy;
}


vector<Locatar> LocatarStore::removeIfAp(int ap)
{
	vector<Locatar> all = getAll();
	auto it = std::remove_if(all.begin(), all.end(),
		[ap](const Locatar& m) {
			return (m.getApartment() >= ap);
		});
	all.resize(distance(all.begin(), it));
	return all;
}

void LocatarStore::addToNotificari(int nrApartament)
{
	const auto& loc = rep.find(nrApartament);
	currentListaNotificare.addLocToListaNotificare(loc);
}

const vector<Locatar>& LocatarStore::getAllNotificari()const
{
	return currentListaNotificare.getAllListaNotificare();
}

void LocatarStore::addRandomNotificari(int nr)
{
	currentListaNotificare.addRandomLocatari(this->getAll(), nr);
}

void LocatarStore::emptyNotificari()
{
	currentListaNotificare.emptyListaNotificare();
}

void LocatarStore::exportListCVS(std::string fName)const
{
	exportToCVS(fName, this->getAllNotificari());

}

void LocatarStore::exportListHTML(std::string fName)const
{
	exportToHTML(fName, this->getAllNotificari());
}



void testAdd() {
	LocatarRepo repo;
	LocatarValidator val;
	LocatarStore ctr{ repo,val };
	ctr.addLocatar(1, "a", 2, "b");
	assert(ctr.getAll().size() == 1);
	ctr.modifLocatar(1, "c", 3, "d");
	assert(ctr.getAll()[0].getName() == "c");
	ctr.delLocatar(1);
	assert(ctr.getAll().size() == 0);
	assert(ctr.findLocatar(1).getApartment() == -1);
	ctr.undo();
	assert(ctr.getAll().size() == 1);
	ctr.undo();
	assert(ctr.getAll().size() == 1);
	ctr.undo();
	assert(ctr.getAll().size() == 0);
	try {
		ctr.undo();
		assert(false);
	}
	catch (LocatarRepoException) {
		assert(true);
	}
}

void testFilter() {
	LocatarRepo repo;
	LocatarValidator val;
	LocatarStore ctr{ repo,val };
	ctr.addLocatar(1, "Ion", 120, "garsoniera");
	ctr.addLocatar(2, "Ionel", 200, "apartament");
	ctr.addLocatar(3, "Ionut", 11, "garsoniera");
	ctr.addLocatar(4, "Ioana", 360, "duplex");
	assert(ctr.filterSurface(130)[0].getApartment() == 1);
	assert(ctr.filterType("apartament")[0].getApartment() == 2);
	assert(ctr.removeIfAp(2).size() == 1);
}

void testSort() {
	LocatarRepo repo;
	LocatarValidator val;
	LocatarStore ctr{ repo,val };
	ctr.addLocatar(1, "Ion", 120, "garsoniera");
	ctr.addLocatar(2, "Ionel", 200, "apartament");
	ctr.addLocatar(3, "Ionut", 11, "garsoniera");
	ctr.addLocatar(4, "Ioana", 360, "duplex");
	assert(ctr.sortName()[0].getApartment() == 4);
	assert(ctr.sortSurface()[0].getApartment() == 3);
	assert(ctr.sortTypeSurface()[0].getApartment() == 2);
}

void testListaNotificare() {
	LocatarRepo repo;
	LocatarValidator val;
	LocatarStore ctr{ repo,val };
	ctr.addLocatar(1, "Ion", 120, "garsoniera");
	ctr.addLocatar(2, "Ionel", 200, "apartament");
	ctr.addLocatar(3, "Ionut", 11, "garsoniera");
	ctr.addLocatar(4, "Ioana", 360, "duplex");
	ctr.addToNotificari(1);
	assert(ctr.getAllNotificari()[0].getApartment() == 1);
	ctr.emptyNotificari();
	assert(ctr.getAllNotificari().size() == 0);
	ctr.addRandomNotificari(3);
	assert(ctr.getAllNotificari().size() == 3);
}

void testeStore()
{
	testAdd();
	testFilter();
	testSort();
	testListaNotificare();
}
#include <fstream>
void testExporta()
{
	LocatarRepo repo;
	LocatarValidator val;
	LocatarStore ctr{ repo,val };
	ctr.addLocatar(1, "Ion", 120, "garsoniera");
	ctr.addLocatar(2, "Ionel", 200, "apartament");
	ctr.addLocatar(3, "Ionut", 11, "garsoniera");
	ctr.addLocatar(4, "Ioana", 360, "duplex");
	ctr.addRandomNotificari(3);
	ctr.exportListCVS("testExport.cvs");
	std::ifstream in("testExport.cvs");
	assert(in.is_open());
	int countLines = 0;
	while (!in.eof()) {
		string line;
		in >> line;
		countLines++;
	}
	in.close();
	assert(countLines == 4);
	ctr.exportListHTML("testExport.html");
	in.open("testExport.html");
	assert(in.is_open());
	try {
		ctr.exportListCVS("test/Export.cvs");
		assert(false);
	}
	catch (LocatarRepoException&) {
		assert(true);
	}
	try {
		ctr.exportListHTML("a/b/c/Export.html");
		assert(false);
	}
	catch (LocatarRepoException&) {
		assert(true);
	}
}
