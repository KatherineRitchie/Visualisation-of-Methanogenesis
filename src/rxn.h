#ifndef RXN_H
#define RXN_H

#include "metabolite.h"
#include <vector>
#include <string>

class Reaction {
    
    enum ReactionType {
        B,       // irreversible bimolecular Michaelis-Menten
        BC,        // irreversible bimolecular Michaelis-Menten for the two underlined reactants with a constant flux term for the others, which is set to the  ux calculated for bimolecular reaction
        M,        // irreversible unimolecular Michaelis-Menten
        F        // first order reaction
    };


    std::string name_;
    std::vector<Metabolite> reactants_;
    std::vector<Metabolite> products_;
    ReactionType type_;
    
public:
    Reaction();
    Reaction(std::string name_v, std::vector<Metabolite> reactants_v, std::vector<Metabolite> products_v);

    std::vector<Metabolite> GetReactants();
    std::vector<Metabolite> GetProducts();

    bool react();
};
#endif
