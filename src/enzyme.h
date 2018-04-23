//
// Created by Katherine Ritchie on 4/18/18.
//

#ifndef ENZYME_H
#define ENZYME_H

#include "rxn.h"

class Enzyme {
    std::string name_;
    std::vector<Reaction> reactions_;

public:
    Enzyme();
    Enzyme(std::vector<Reaction> rxn_v);

    std::string GetName();
    std::vector<Reaction> GetReactions();
};

#endif
