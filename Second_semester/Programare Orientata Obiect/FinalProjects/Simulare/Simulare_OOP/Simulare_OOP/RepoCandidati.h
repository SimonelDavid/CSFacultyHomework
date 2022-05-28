#ifndef SIMULARE_REPO_H
#define SIMULARE_REPO_H
#include <string>
#include "Candidat.h"
#include <vector>
using std::vector;
using std::string;

class RepoCandidati {
private:
    vector<Candidat> all;
    string path;
public:
    RepoCandidati(string path):path{std::move(path)}{readFromFile();};

    vector<Candidat>& getAll();
    void readFromFile();
    void saveInFile();
    void add(Candidat& candidat);
};


#endif //SIMULARE_REPO_H
