#include "metabolite.h"

std::string Metabolite::get_fullname() const {
    return fullname_;
}

std::string Metabolite::get_shortname() const {
    return shortname_;
}

int Metabolite::get_num_particles() const {
    return num_particles_;
}

void Metabolite::rm_particle() {
    if (num_particles_ == 0) {
        return;
    }
    num_particles_ = num_particles_ - 1;
}

void Metabolite::add_particle() {
    num_particles_ = num_particles_ + 1;
}
