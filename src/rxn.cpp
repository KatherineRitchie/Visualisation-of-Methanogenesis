#include "rxn.h"

Reaction::Reaction() {
    reactants_ = std::vector<Metabolite>();
    products_ = std::vector<Metabolite>();
}

Reaction::Reaction(std::vector<Metabolite> reactants_v, std::vector<Metabolite> products_v) {
    reactants_ = reactants_v;
    products_ = products_v;
}

bool Reaction::react() {
    for (Metabolite metabolite : reactants_) {
        metabolite.rm_particle();
    }
    for (Metabolite metabolite : products_) {
        metabolite.add_particle();
    }
    return true;
}
