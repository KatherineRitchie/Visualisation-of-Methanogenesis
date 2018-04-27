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

int Metabolite::GetXPos() const {
    return x_pos_;
}

int Metabolite::GetYPos() const {
    return y_pos_;
}

void Metabolite::SetFullName(std::string fullname_v) {
    fullname_ = fullname_v;
}

void Metabolite::SetShortName(std::string shortname_v) {
    shortname_ = shortname_v;
}

void Metabolite::SetNumParticles(double init_conc_v, std::string units) {
    num_particles_ = init_conc_v * 1000;
    //TODO fix setNumParticles method to use real chemistry
}

void Metabolite::SetNumParticles(int num_particles_v) {
    num_particles_ = num_particles_v;
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
    //TODO double check that this is the right design choice!!!!!!
    //we do not check for x/y positions as there may be multiple representations of the same chemical
    return true;
}

bool Metabolite::operator!=(const Metabolite &rhs) const {
    return !(*this == rhs);
}