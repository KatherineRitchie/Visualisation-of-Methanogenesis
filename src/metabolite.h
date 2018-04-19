#ifndef METABOLITE_H
#define METABOLITE_H

#include <string>

class Metabolite {
    std::string shortname_;
    std::string fullname_;
    int num_particles_;
    
public:
    //Constructors
    Metabolite() : shortname_(""), fullname_(""), num_particles_(0) {};
    explicit Metabolite(std::string shortname_v, std::string fullname_v, int num_particles_v) : shortname_(shortname_v), fullname_(fullname_v), num_particles_(num_particles_v) {};
    
    //Accessors
    std::string get_fullname() const;
    std::string get_shortname() const;
    int get_num_particles() const;
    
    //Modifiers
    void rm_particle();
    void add_particle();
};

#endif
