#include "Metabolite.h"

std::string Metabolite::get_fullname() const {
    return fullname_;
}

std::string Metabolite::get_shortname() const {
    return shortname_;
}

void Metabolite::rm_particle() {
    num_particles_ = num_particles_ - 1;
}

void Metabolite::add_particle() {
    num_particles_ = num_particles_ + 1;
}
