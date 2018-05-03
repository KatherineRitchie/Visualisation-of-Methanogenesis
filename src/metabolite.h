#ifndef METABOLITE_H
#define METABOLITE_H

#include "simulationConstants.h"
#include <string>

class Metabolite {
    std::string shortname_;
    std::string fullname_;
    long init_num_particles_;
    int x_pos_;
    int y_pos_;
    
public:
    // Constructors
    Metabolite();
    explicit Metabolite(std::string shortname_v, std::string fullname_v, long num_particles_v, int x_pos_v, int y_pos_v);

    // Accessors
    std::string GetFullname() const;
    std::string GetShortname() const;
    long GetInitNumParticles() const;
    int GetXPos() const;
    int GetYPos() const;
    
    // Modifiers
    void SetFullName(std::string fullname_v);
    void SetShortName(std::string shortname_v);
    void SetInitNumParticles(double init_conc_v, double volume_v, std::string units);
    void SetInitNumParticles(long num_particles_v);
    void SetXPos(int x_pos_v);
    void SetYPos(int y_pos_v);

    // Equality operators
    bool operator==(const Metabolite &rhs) const;
    bool operator!=(const Metabolite &rhs) const;
};

// Accepts a double for concentration of a particle in the system and the number of femtolitres and returns the
// number of particles using basic stoichiometry
long ConcToNumParticles(double conc, double num_fL);

#endif
