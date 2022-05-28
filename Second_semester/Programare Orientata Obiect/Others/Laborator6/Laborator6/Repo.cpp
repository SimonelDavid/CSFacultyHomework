#include "Repo.h"

bool Repo::exist(const Movie& m) const {
    try {
        find(m.title(), m.year());
        return true;
    }
    catch (RepoException&) {
        return false;
    }
}

void Repo::add(const Movie& m) {
    if (exist(m))
        throw RepoException("deja exista");
    all.push_back(m);
}

const std::vector<Movie>& Repo::getAll() const {
    return all;
}

const Movie& Repo::find(const std::string title, const int year) const {
    for (const auto& movie : all) {
        if (movie.title() == title, movie.year() == year)
            return movie;
    }
    throw RepoException("nu exista");
}

void Repo::del(Movie& m) {
    if (!exist(m))
        throw RepoException("nu există");
    for (int i = 0; i < all.size(); i++) {
        if (all[i] == m) {
            all.erase(all.begin() + i);
            return;
        }
    }
}

void Repo::modify(Movie& movie) {
    if (!exist(movie))
        throw RepoException("nu exista");
    for (auto& m : all) {
        if (m == movie) {
            m = movie;
            return;
        }
    }
}


std::ostream& operator<<(std::ostream& out, const RepoException& ex) {
    out << ex.msg;
    return out;
}
