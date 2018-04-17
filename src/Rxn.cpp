#include "Rxn.h"

bool Reaction::react() {
    for (Metabolite metabolite : reactants_) {
        metabolite.rm_particle();
    }
    for (Metabolite metabolite : products_) {
        metabolite.add_particle();
    }
    return true;
}
