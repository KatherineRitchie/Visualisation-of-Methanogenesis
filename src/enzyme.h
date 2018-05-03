//
// Created by Katherine Ritchie on 4/18/18.
//

#ifndef ENZYME_H
#define ENZYME_H

#include "reaction.h"

class Enzyme {
    std::string name_;
    std::vector<Reaction*> reactions_;
    int x_pos_;
    int y_pos_;

public:
    // Constructors
    Enzyme();
    explicit Enzyme(std::string name_v, std::vector<Reaction*> rxn_v, int x_pos_v, int y_pos_v);

    // Accessors
    std::string GetName() const;
    std::vector<Reaction*> GetReactions() const;
    int GetXPos() const;
    int GetYPos() const;

    // Modifiers
    void SetName(std::string name_v);
    void SetReactions(std::vector<Reaction*> reactions_v);

    // Equality operators
    bool operator==(const Enzyme &rhs) const;
    bool operator!=(const Enzyme &rhs) const;
};

#endif
