#include <iostream>
#include <vector>
#include <map>

#include "main.h"

int main() {
    //load up time resolved dictionary
    //main with global variable containing 2d dictionary, an entry for each metabolic and a vector for each time step
    //display animation
    std::cout << "standard cout dinosaur\n";
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
