#include "Repository.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::getline;
using std::stod;
bool SongRepository::exists(const Song& s) {
	try {
		find(s.getTitlu(), s.getArtist());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}
const Song& SongRepository::find(string titlu, string artist) {
	/*for (const Song& s : this->allSongs) {
		if (s.getTitlu() == titlu && s.getArtist() == artist) {
			return s;
		}
	}*/
	vector<Song>::iterator f = std::find_if(this->allSongs.begin(), this->allSongs.end(),
		[=](const Song& s) {
		return s.getTitlu() == titlu && s.getArtist() == artist;
		}); 

	if (f != this->allSongs.end())
		return (*f);
	else
		throw RepoException("Melodia cu titlul "+titlu+" si artistul "+artist +" nu exista in lista.\n");
}
void SongRepository::store(const Song& s) {
	if (exists(s)) {
		throw RepoException("Melodia cu titlul " + s.getTitlu() + " si artistul " + s.getArtist() + " exista deja in lista.");
	}
	this->allSongs.push_back(s);
}

const vector<Song>& SongRepository::getAllSongs() {
	return this->allSongs;
}

void SongRepositoryFile::loadFromFile() {
	ifstream songFile(this->filename);
	if (!songFile.is_open()) {
		throw RepoException("Cannot read from file " + filename);
	}
	string line;
	while (getline(songFile, line))
	{
		string titlu, artist, gen;
		double durata;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		//Citire linie de tip "Titlu,Artist,Gen,Durata"
		//separam linia cu separator = ,
		//se pot citi/scrie datele in fisier dupa cum va este usor
		//1 atribut pe o linie, sau pe o linie toate atributele, separate de spatiu etc
		while (getline(linestream, current_item, ','))
		{
			//we should do some checks here, make sure
			//that what we read is correct, throw exception otherwise
			//or 'clean' data we read
			//e.g. remove trailing spaces
			//as of now, if in file we have Venom, Eminem,... and we search
			//find("Venom","Eminem") - no space before artist, it won't work
			if (item_no == 0) titlu = current_item;
			if (item_no == 1) artist = current_item;
			if (item_no == 2) gen = current_item;
			if (item_no == 3) durata = stod(current_item);
			item_no++;
		}
		Song s{ titlu, artist, gen, durata };

		SongRepository::store(s);
		

	}
	songFile.close();
}

void SongRepositoryFile::saveToFile() {
	ofstream songOutput(this->filename);
	if (!songOutput.is_open())
		throw RepoException("Cannot write to file " + filename);
	for (auto& song : getAllSongs()) {
		songOutput << song.getTitlu() << "," << song.getArtist() << ",";
		songOutput << song.getGen() << "," << song.getDurata() << endl;
	}
	songOutput.close();
}

void SongRepositoryFile::store(const Song& s){
	
	SongRepository::store(s);
	
	saveToFile();

}
void testAddRepo() {
	SongRepository testRepo;
	Song song1{ "Yamasha", "Alex Velea","pop",3.45 };
	testRepo.store(song1);
	assert(testRepo.getAllSongs().size() == 1);

	Song song2{ "Raisa", "Fly Project", "pop", 3.42 };
	Song song3{ "Yamasha", "Alex Velea", "rock", 4.32 };
	try {
		testRepo.store(song3);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}


}
void testFindRepo() {
	SongRepository testRepo;

	Song song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };
	Song song2{ "Highway Star","Deep Purple", "rock",2.44 };
	Song song3{ "Holy Diver","Dio", "rock", 4.45 };
	testRepo.store(song1);
	testRepo.store(song2);

	assert(testRepo.exists(song1));
	assert(!testRepo.exists(song3));

	auto foundSong = testRepo.find("Pictures of Home", "Deep Purple");
	assert(foundSong.getArtist() == "Deep Purple");
	assert(foundSong.getDurata() == 3.24);
	assert(foundSong.getGen() == "rock");


	try {
		testRepo.find("Baba O'riley", "The Who");
		assert(false);
	}
	catch (RepoException& ve) {
		
		assert(ve.getErrorMessage()== "Melodia cu titlul Baba O'riley si artistul The Who nu exista in lista.\n");
	}
}

void testeRepo() {
	testAddRepo();
	testFindRepo();
}

void testeFileRepo() {
	std::ofstream ofs;
	ofs.open("test_songs.txt", std::ofstream::out | std::ofstream::trunc);
	ofs << "Hey Hey Rise Up,Pink Floyd,rock,3.32\n";
	ofs << "Legendary,Welshly Arms,alternative,3.38\n";
	ofs << "Never Let Me Go,Florence + The Machine,indie,4.33\n";
	ofs << "Venom,Eminem,hip-hop,2.43\n";
	ofs.close();
	try {
		SongRepositoryFile testRepoF{ "test_songs2.txt" };
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	SongRepositoryFile testRepoF{ "test_songs.txt" };
	assert(testRepoF.getAllSongs().size() == 4);


	auto foundSong = testRepoF.find("Venom", "Eminem");
	assert(foundSong.getArtist() == "Eminem");
	assert(foundSong.getDurata() == 2.43);
	assert(foundSong.getGen() == "hip-hop");

	Song song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };

	testRepoF.store(song1);
	assert(testRepoF.getAllSongs().size() == 5);
	Song foundSong2 = testRepoF.find("Pictures of Home", "Deep Purple");
	assert(foundSong2.getDurata() == 3.24);






	

}