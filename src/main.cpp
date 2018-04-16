#include <iostream>
#include <vector>
#include <map>

//~~~~~~~~~~~~~~~~~~~~~~~HORMONE FILE~~~~~~~~~~~~~~~~~~~~~~~

class Hormone {
    std::string shortname_;
    std::string fullname_;
    int num_particles_;

    public:
	//Constructors
        Hormone() : shortname_(NULL), fullname_(NULL), num_particles_(0) {};
	Hormone(std::string shortname_v, std::string fullname_v, int num_particles_v) : shortname_(shortname_v), fullname_(fullname_v), num_particles_(num_particles_v) {};

        //Accessors
        std::string get_fullname() const;
        std::string get_shortname() const;
        int get_num_particles() const;

        //Modifiers
        void rm_particle();
        void add_particle();
};

std::string Hormone::get_fullname() const {
	return fullname_;
}

std::string Hormone::get_shortname() const {
	return shortname_;
}

void Hormone::rm_particle() {
	num_particles_ = num_particles_ - 1;
}

void Hormone::add_particle() {
	num_particles_ = num_particles_ + 1;
}

//~~~~~~~~~~~~~RXN FILE~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Reaction {

	enum ReactionType {
		B;		// irreversible bimolecular Michaelis-Menten
		BC;		// irreversible bimolecular Michaelis-Menten for the two underlined reactants with a constant flux term for the others, which is set to the  ux calculated for bimolecular reaction
		M;		// irreversible unimolecular Michaelis-Menten
		F;		// first order reaction
	}

	std::string enzyme_;
    std::vector<Hormone> reactants_;
	std::vector<Hormone> products_;
	float kcat_;
	float km_;
	ReactionType type_;
    
    public:
    bool react();
}

bool Reaction::react() {
    for (Hormone hormone : reactants_) {
        hormone.rm_particle;
    }
    for (Hormone hormone : products_) {
        hormone.add_particle;
    }
    return true;
}

//~~~~~~~~~~~~~~~~~MAIN FILE~~~~~~~~~~~~~~~~~~~~~~~~
std::map<std::string, Hormone> channel;

int main() {
    //load up time resolved dictionary
    //main with global variable containing 2d dictionary, an entry for each metabolic and a vector for each time step
    //display animation
    std::cout << "standard cout dinosaur\n";
    return 0;
}

void publish(Hormone& hormone);
void publish(std::vector<Hormone> hormones);

void publish(Hormone& hormone) {
	channel[hormone.get_shortname()] = hormone;
}

void publish(std::vector<Hormone>& hormones) {
	for (Hormone hormone : hormones) {
		publish(hormone);
	}
}
