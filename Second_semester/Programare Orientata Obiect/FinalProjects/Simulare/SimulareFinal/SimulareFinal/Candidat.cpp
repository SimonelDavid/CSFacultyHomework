//
// Created by david on 20.05.2022.
//

#include "Candidat.h"

#include <utility>

const string &Candidat::getNume() const {
    return nume;
}

bool Candidat::operator==(const Candidat &rhs) const {
    return id == rhs.getId();
}

bool Candidat::operator!=(const Candidat &rhs) const {
    return !(rhs == *this);
}

void Candidat::setNume(const string &nume) {
    Candidat::nume = nume;
}

const string &Candidat::getJob() const {
    return job;
}

void Candidat::setJob(const string &job) {
    Candidat::job = job;
}

Candidat::Candidat(string nume, string job, string candidatura, string id) : nume(std::move(nume)), job(std::move(job)),
                                                                             status(std::move(candidatura)),
                                                                             id(std::move(id)){}

const string &Candidat::getCandidatura() const {
    return status;
}

void Candidat::setCandidatura(const string &candidatura) {
    Candidat::status = candidatura;
}
