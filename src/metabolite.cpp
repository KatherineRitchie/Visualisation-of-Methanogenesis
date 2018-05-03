#include "metabolite.h"
#include <math.h>

Metabolite::Metabolite() {
    shortname_ = "";
    fullname_ = "";
    init_num_particles_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
}

Metabolite::Metabolite(std::string shortname_v, std::string fullname_v, long num_particles_v, int x_pos_v, int y_pos_v) {
    shortname_ = shortname_v;
    fullname_ = fullname_v;
    init_num_particles_ = num_particles_v;
    x_pos_ = x_pos_v;
    y_pos_ = y_pos_v;
}

std::string Metabolite::GetFullname() const {
    return fullname_;
}

std::string Metabolite::GetShortname() const {
    return shortname_;
}

long Metabolite::GetInitNumParticles() const {
    return init_num_particles_;
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

void Metabolite::SetInitNumParticles(double init_conc_v, double volume_v, std::string units) {
    init_num_particles_ = ConcToNumParticles(init_conc_v, volume_v);
}

void Metabolite::SetInitNumParticles(long num_particles_v) {
    init_num_particles_ = num_particles_v;
}

void Metabolite::SetXPos(int x_pos_v) {
    x_pos_ = x_pos_v;
}
void Metabolite::SetYPos(int y_pos_v) {
    y_pos_ = y_pos_v;
}

bool Metabolite::operator==(const Metabolite &rhs) const {
    if (shortname_ != rhs.GetShortname()) {
        return false;
    }
    if (fullname_ != rhs.GetFullname()) {
        return false;
    }
    if (init_num_particles_ != rhs.GetInitNumParticles()) {
        return false;
    }
    // we do not check for x/y positions as there may be multiple representations of the same chemical in future
    // iterations
    return true;
}

bool Metabolite::operator!=(const Metabolite &rhs) const {
    return !(*this == rhs);
}

long ConcToNumParticles(double conc, double numfL) {
    // this is what an accurate simulation would ordinarily return, but we will not use this number to make our
    // simulation easier to handle
    // return (long) AVOGRADROS_POW * LITRES_IN_A_FEMTOLITRE * (double) (conc * AVOGADROS_NUM * numfL));
    return (long) (pow(10.0, 4) * (double)(conc * AVOGADROS_NUM * numfL));
}
