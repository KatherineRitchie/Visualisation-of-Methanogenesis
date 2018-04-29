#ifndef METABOLITE_H
#define METABOLITE_H

#include <math.h>
#include "string"

class Metabolite {
    std::string shortname_;
    std::string fullname_;
    long num_particles_;
    int x_pos_;
    int y_pos_;
    
public:
    //Constructors
    Metabolite() : shortname_(""), fullname_(""), num_particles_(0) {};
    explicit Metabolite(std::string shortname_v, std::string fullname_v, long num_particles_v, int x_pos_v, int y_pos_v) : shortname_(shortname_v), fullname_(fullname_v), num_particles_(num_particles_v), x_pos_(x_pos_v), y_pos_(y_pos_v) {};

    //Big 3
//    Metabolite(const Metabolite& source);                                           // Copy constructor
//    Metabolite(Metabolite&& source) noexcept;                                       // Move constructor
    ~Metabolite();                                                                  // Destructor

    //Accessors
    std::string GetFullname() const;
    std::string GetShortname() const;
    long GetNumParticles() const;
    int GetXPos() const;
    int GetYPos() const;
    
    //Modifiers
    void SetFullName(std::string fullname_v);
    void SetShortName(std::string shortname_v);
    void SetNumParticles(double init_conc_v, double volume_v, std::string units);
    void SetNumParticles(long num_particles_v);
    void SetXPos(int x_pos_v);
    void SetYPos(int y_pos_v);

    void rm_particle();
    void add_particle();

    bool operator==(const Metabolite &rhs) const;
    bool operator!=(const Metabolite &rhs) const;
};

long ConcToNumParticles(double conc, double num_fL);

#endif
