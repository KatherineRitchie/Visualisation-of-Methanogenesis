#ifndef RXN_H
#define RXN_H

#include "Metabolite.h"
#include <vector>
#include <string>

class Reaction {
    
    enum ReactionType {
        B,       // irreversible bimolecular Michaelis-Menten
        BC,        // irreversible bimolecular Michaelis-Menten for the two underlined reactants with a constant flux term for the others, which is set to the  ux calculated for bimolecular reaction
        M,        // irreversible unimolecular Michaelis-Menten
        F        // first order reaction
    };
    
    std::string enzyme_;
    std::vector<Metabolite> reactants_;
    std::vector<Metabolite> products_;
    float kcat_;
    float km_;
    ReactionType type_;
    
public:
    bool react();
};
#endif
