#include "rxn.h"

ReactionType StringToReactionType(std::string reaction_type_string) {
    if (reaction_type_string == "B") {
        return B;
    }
    if (reaction_type_string == "BC") {
        return BC;
    }
    if (reaction_type_string == "M") {
        return M;
    }
    if (reaction_type_string == "F") {
        return F;
    }
    return null_rxn_type;
}


Reaction::Reaction() {
    reactants_ = std::vector<Metabolite*>();
    products_ = std::vector<Metabolite*>();
}

Reaction::Reaction(std::string name_v, std::vector<Metabolite*> reactants_v, std::vector<Metabolite*> products_v, ReactionType reaction_type_v, double kcat_v) {
    name_ = name_v;
    reactants_ = reactants_v;
    products_ = products_v;
    type_ = reaction_type_v;
    kcat = kcat_v;
}

std::string Reaction::GetName() const {
    return name_;
}

std::vector<Metabolite*> Reaction::GetReactants() const {
    return reactants_;
}

std::vector<Metabolite*> Reaction::GetProducts() const {
    return products_;
}

ReactionType Reaction::GetType() const {
    return type_;
}

double Reaction::GetKCat() const {
    return kcat;
}

////TODO test this method
//bool Reaction::CanReact() const {
//    for (Metabolite *reactant : reactants_) {
//        if (reactant->GetCurrNumParticles() <= 0) {
//            return false;
//        }
//    }
//    return true;
//}

void Reaction::SetName(std::string name_v) {
    name_ = name_v;
}

void Reaction::SetReactants(std::vector<Metabolite*> reactants_v) {
    reactants_ = reactants_v;
}

void Reaction::SetProducts(std::vector<Metabolite*> product_v) {
    products_ = product_v;
}

void Reaction::SetReactionType(ReactionType reaction_type_v) {
    type_ = reaction_type_v;
}

void Reaction::SetKCat(double kcat_v) {
    kcat = kcat_v;
}

//TODO figure out why you cant implement equality operator overloads
bool Reaction::operator==(const Reaction &rhs) const {
    if (name_ != rhs.GetName()) {
        return false;
    }
    if (type_ != rhs.GetType()) {
        return false;
    }
    if (kcat != rhs.GetKCat()) {
        return false;
    }
    if (reactants_.size() != rhs.GetReactants().size()) {
        return false;
    }
    if (products_.size() != rhs.GetProducts().size()) {
        return false;
    }
    for (int i = 0; i < reactants_.size(); i++) {
        if (reactants_[i] != rhs.GetReactants()[i]) {
            return false;
        }
    }
    for (int i = 0; i < products_.size(); i++) {
        if (products_[i] != rhs.GetProducts()[i]) {
            return false;
        }
    }
    return true;
}

bool Reaction::operator!=(const Reaction &rhs) const {
    return !(*this == rhs);
}

//bool Reaction::react() {
//
//    //TODO figure out how you want a reaction to occur
//    for (Metabolite* metabolite : reactants_) {
//        metabolite->rm_particle();
//    }
//    for (Metabolite* metabolite : products_) {
//        metabolite->add_particle();
//    }
//    for (Metabolite* metabolite : reactants_) {
//        if (metabolite->GetInitNumParticles() <= 0) {
//            return false;
//        }
//    }
//    return true;
//}
