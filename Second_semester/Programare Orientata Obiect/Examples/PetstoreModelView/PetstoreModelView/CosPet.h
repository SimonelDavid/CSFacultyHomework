#pragma once
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock

#include "pet.h"
#include "observer.h"
using std::vector;
/*
  Clasa care implementeaza ideea de cos
  Extinde observable, astfel cei interesati se notifica in caz ca s-a schimbat ceva la Cos
*/
class CosPet:public Observable {
	vector<Pet> inCos;
	const PetRepo& rep;
public:
	CosPet(const PetRepo& rep) :rep{rep} {}

	void adauga(const Pet& p) {
		inCos.push_back(p);
		//notificam can dse schimba ceva in cos
		notify();
	}
	void goleste() {
		inCos.clear();
		//notificam can dse schimba ceva in cos
		notify();
	}
	/*
	Umple cosul aleator
	*/
	void umple(int cate) {
		int seed = std::chrono::system_clock::now().time_since_epoch().count();
		vector<Pet> all = rep.getAll();
		std::shuffle(all.begin(), all.end(), std::default_random_engine(seed)); //amesteca vectorul v
		while (inCos.size() < cate && all.size()>0) {
			inCos.push_back(all.back());
			all.pop_back();
		}
		//notificam can dse schimba ceva in cos
		notify();
	}

	vector<Pet> lista() const {
		return inCos;
	}
};