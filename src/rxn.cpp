#include "rxn.h"

Reaction::Reaction() {
    reactants_ = std::vector<Metabolite>();
    products_ = std::vector<Metabolite>();
}

Reaction::Reaction(std::string name_v, std::vector<Metabolite> reactants_v, std::vector<Metabolite> products_v, ReactionType reaction_type_v, double kcat_v) {
    name_ = name_v;
    reactants_ = reactants_v;
    products_ = products_v;
    type_ = reaction_type_v;
    kcat = kcat_v;
}

std::string Reaction::GetName() const {
    return name_;
}

std::vector<Metabolite> Reaction::GetReactants() const {
    return reactants_;
}

std::vector<Metabolite> Reaction::GetProducts() const {
    return products_;
}

Reaction::ReactionType Reaction::GetType() const {
    return type_;
}

double Reaction::GetKCat() const {
    return kcat;
}

//TODO figure out why you cant implement equality operator overloads
bool Reaction::operator==(const Reaction &rhs) const {
    if (name_ != rhs.GetName()) {
        return false;
    }
    if (reactants_ != rhs.GetReactants()) {
        return false;
    }
    if (products_ != rhs.GetProducts()) {
        return false;
    }
    if (type_ != rhs.GetType()) {
        return false;
    }
    if (kcat != rhs.GetKCat()) {
        return false;
    }
    return true;
}

bool Reaction::operator!=(const Reaction &rhs) const {
    return !(*this == rhs);
}

////TODO figure out why you cant implement equality operator overloads
//bool operator==(const Reaction &lhs, const Reaction &rhs) const {
//    if (lhs.GetName() != rhs.GetName()) {
//        return false;
//    }
//    if (lhs.GetReactants() != rhs.GetReactants()) {
//        return false;
//    }
//    if (lhs.GetProducts() != rhs.GetProducts()) {
//        return false;
//    }
//    if (lhs.GetType() != rhs.GetType()) {
//        return false;
//    }
//    if (lhs.GetKCat() != rhs.GetKCat()) {
//        return false;
//    }
//    return true;
//}
//
//bool operator!=(const Reaction &lhs, const Reaction &rhs) const {
//    return !(lhs == rhs);
//}

bool Reaction::react() {
    for (Metabolite metabolite : reactants_) {
        metabolite.rm_particle();
    }
    for (Metabolite metabolite : products_) {
        metabolite.add_particle();
    }
    return true;
}
