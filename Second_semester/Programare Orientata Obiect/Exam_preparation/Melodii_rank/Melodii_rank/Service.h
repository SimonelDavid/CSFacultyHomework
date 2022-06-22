#pragma once
#include "Repo.h"
#include <algorithm>

class Service {
private:
	Repo& rep;
public:
	Service(Repo& rep) :rep{ rep } {};
	vector<Melodie> getAll() {
		auto cpy = rep.getAll();
		sort(cpy.begin(), cpy.end(), [](Melodie m1, Melodie m2) {
			return m1.getRank() < m2.getRank();
			});
		return cpy;
	}
	vector<int> sameRank();
	int getFr(int rank) {
		int k = 0;
		for (auto& el : getAll())
			if (el.getRank() == rank)
				k++;
		return k;
	}
	void updateRank(int id, int newRank, string titlu);
	void deletePos(int id);
};