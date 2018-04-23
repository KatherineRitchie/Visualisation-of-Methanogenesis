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
    bool one = default_metabolite.GetFullname() == "";
//    bool two = default_metabolite.GetShortname() == NULL;
//    bool three = default_metabolite.GetNumParticles() == 0;
//    default_metabolite.rm_particle();
//    std::cout << std::to_string(one) << std::to_string(two) << std::to_string(three) << std::endl;
    return 0;
}

void publish(Metabolite& Metabolite);
void publish(std::vector<Metabolite> metabolite);

void publish(Metabolite& metabolite) {
	channel[metabolite.GetShortname()] = metabolite;
}

void publish(std::vector<Metabolite>& metabolites) {
	for (Metabolite metabolite : metabolites) {
		publish(metabolite);
	}
}
