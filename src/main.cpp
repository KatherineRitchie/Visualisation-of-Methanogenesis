#include <iostream>
#include <vector>
#include <map>

#include "main.h"

int main() {
    //load up time resolved dictionary
    //main with global variable containing 2d dictionary, an entry for each metabolic and a vector for each time step
    //display animation
    std::cout << "standard cout dinosaur\n";
    
    Metabolite default_metabolite;
    std::cout << "standard cout dinosaur\n";
    bool one = default_metabolite.get_fullname() == "";
//    bool two = default_metabolite.get_shortname() == NULL;
//    bool three = default_metabolite.get_num_particles() == 0;
//    default_metabolite.rm_particle();
//    std::cout << std::to_string(one) << std::to_string(two) << std::to_string(three) << std::endl;
    return 0;
}

void publish(Metabolite& Metabolite);
void publish(std::vector<Metabolite> metabolite);

void publish(Metabolite& metabolite) {
	channel[metabolite.get_shortname()] = metabolite;
}

void publish(std::vector<Metabolite>& metabolites) {
	for (Metabolite metabolite : metabolites) {
		publish(metabolite);
	}
}
