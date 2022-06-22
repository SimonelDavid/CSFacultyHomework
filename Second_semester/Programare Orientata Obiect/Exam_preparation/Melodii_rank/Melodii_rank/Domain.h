#pragma once
#include <string>

using namespace std;

class Melodie {
private:
	int id, rank;
	string titlu, artist;
public:
	Melodie() { id = 0; rank = 0; titlu = ""; artist = ""; }
	Melodie(int i, int r, string t, string a) :id{ i }, rank{ r }, titlu{ t }, artist{ a }{};
	//Melodie(Melodie& ot) { id = ot.getId(); rank = ot.getRank }
	int getId() const noexcept {
		return id;
	}
	int getRank() const noexcept {
		return rank;
	}
	string getTitlu() const {
		return titlu;
	}
	string getArtist() const {
		return artist;
	}
};