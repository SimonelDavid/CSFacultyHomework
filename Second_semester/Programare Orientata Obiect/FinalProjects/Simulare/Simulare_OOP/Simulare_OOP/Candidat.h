#ifndef SIMULARE_CANDIDAT_H
#define SIMULARE_CANDIDAT_H
#include <string>
#include <utility>
using std::string;

class Candidat {
private:
    string nume;
    string job;
    string status;
public:
    const string &getNume() const {
        return nume;
    }

    void setNume(const string &nume) {
        Candidat::nume = nume;
    }

    const string &getJob() const {
        return job;
    }

    void setJob(const string &job) {
        Candidat::job = job;
    }

    void setStatus(const string& status) {
        Candidat::status = status;
    }

    const string &getStatus() const {
        return status;
    }

    Candidat(string nume, string job, string status):
        nume{std::move(nume)},
        job{job},
        status{status}{};
    Candidat& operator=(const Candidat& other){
        if(this == &other)return *this;
        this->status = other.status;
        this->job = other.job;
        this->nume = other.nume;
        return *this;
    }

};


#endif //SIMULARE_CANDIDAT_H
