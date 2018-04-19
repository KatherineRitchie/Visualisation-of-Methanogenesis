//
// Created by Katherine Ritchie on 4/18/18.
//

#include "enzyme.h"

std::string Enzyme::get_name() {
    return name_;
}

std::vector<Reaction> Enzyme::get_reactions() {
    return reactions_;
}