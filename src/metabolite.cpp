#include "metabolite.h"

std::string Metabolite::GetFullname() const {
    return fullname_;
}

std::string Metabolite::GetShortname() const {
    return shortname_;
}

int Metabolite::GetNumParticles() const {
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

bool Metabolite::operator==(const Metabolite &rhs) const {
    if (shortname_ != rhs.GetShortname()) {
        return false;
    }
    if (fullname_ != rhs.GetFullname()) {
        return false;
    }
    if (num_particles_ != rhs.GetNumParticles()) {
        return false;
    }
    return true;
}
bool Metabolite::operator!=(const Metabolite &rhs) const {
    return !(*this == rhs);
}