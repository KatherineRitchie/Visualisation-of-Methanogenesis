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
    explicit Enzyme(std::string name_v, std::vector<Reaction> rxn_v);

    std::string GetName() const;
    std::vector<Reaction> GetReactions() const;

    bool operator==(const Enzyme &rhs) const;
    bool operator!=(const Enzyme &rhs) const;
};

#endif
