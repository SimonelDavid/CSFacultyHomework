#include "Medicament.h"

std::string Movie::title() const {
    return title_;
}

std::string Movie::protagonist() const {
    return protagonist_;
}

int Movie::year() const {
    return year_;
}

std::string Movie::genre() const {
    return genre_;
}

void Movie::set_protagonist(const std::string newProtagonist) {
    protagonist_ = newProtagonist;
}

void Movie::set_year(const int newYear) {
    year_ = newYear;
}

void Movie::set_genre(const std::string newGenre) {
    genre_ = newGenre;
}

Movie::Movie(const Movie& movie) :
    title_{ movie.title_ }, genre_{ movie.genre_ }, year_{ movie.year_ }, protagonist_{ movie.protagonist_ }{
}

Movie::Movie(const std::string title_, const std::string genre_, const int year_, const std::string protagonist_) :
    title_{ title_ }, genre_{ genre_ }, year_{ year_ }, protagonist_{ protagonist_ }{
}

Movie::~Movie() {
}
