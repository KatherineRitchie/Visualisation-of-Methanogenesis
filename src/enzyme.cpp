//
// Created by Katherine Ritchie on 4/18/18.
//

#include "enzyme.h"

Enzyme::Enzyme() {
    name_ = "";
    reactions_ = std::vector<Reaction>();
}
Enzyme::Enzyme(std::string name_v, std::vector<Reaction> rxn_v) {
    name_ = name_v;
    reactions_ = rxn_v;
}

std::string Enzyme::GetName() const {
    return name_;
}

std::vector<Reaction> Enzyme::GetReactions() const {
    return reactions_;
}

void Enzyme::SetName(std::string name_v) {
    name_ = name_v;
}

void Enzyme::SetReactions(std::vector<Reaction> reactions_v) {
    reactions_ = reactions_v;
}

bool Enzyme::operator==(const Enzyme &rhs) const {
    if (name_ != rhs.GetName()) {
        return false;
    }
    if (reactions_ != rhs.GetReactions()) {
        return false;
    }
    return true;
}

bool Enzyme::operator!=(const Enzyme &rhs) const {
    return !(*this == rhs);
}