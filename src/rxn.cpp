#include "rxn.h"

Reaction::Reaction() {
    reactants_ = std::vector<Metabolite>();
    products_ = std::vector<Metabolite>();
}

Reaction::Reaction(std::string name_v, std::vector<Metabolite> reactants_v, std::vector<Metabolite> products_v) {
    name_ = name_v;
    reactants_ = reactants_v;
    products_ = products_v;
}

std::vector<Metabolite> Reaction::get_reactants() {
    return reactants_;
}

std::vector<Metabolite> Reaction::get_products() {
    return products_;
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
