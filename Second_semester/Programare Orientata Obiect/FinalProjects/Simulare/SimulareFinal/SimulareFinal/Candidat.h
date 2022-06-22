//
// Created by david on 20.05.2022.
//

#ifndef SIMULARE_CANDIDAT_H
#define SIMULARE_CANDIDAT_H
#include <string>
using std::string;

class Candidat {
private:
    string nume, job, status, id;
public:
    Candidat(string nume, string job, string candidatura, string id);

    const string &getNume() const;
    const string &getId() const{return id;};

    void setNume(const string &nume);

    const string &getJob() const;

    void setJob(const string &job);

    const string &getCandidatura() const;

    void setCandidatura(const string &candidatura);

    bool operator==(const Candidat &rhs) const;

    bool operator!=(const Candidat &rhs) const;

};


#endif //SIMULARE_CANDIDAT_H
