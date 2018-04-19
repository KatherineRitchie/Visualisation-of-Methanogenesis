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
    std::string get_name();
    std::vector<Reaction> get_reactions();
};

#endif