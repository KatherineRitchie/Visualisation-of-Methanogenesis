#ifndef RXN_H
#define RXN_H

#include "metabolite.h"
#include <vector>
#include <string>

enum ReactionType {
    null_rxn_type = 0,
    B = 1,          // irreversible bimolecular Michaelis-Menten
    BC = 2,         // irreversible bimolecular Michaelis-Menten for the two underlined reactants with a constant flux term for the others, which is set to the  ux calculated for bimolecular reaction
    M = 3,          // irreversible unimolecular Michaelis-Menten
    F = 4           // first order reaction
};

ReactionType StringToReactionType(std::string reaction_type_string);

class Reaction {
    std::string name_;
    std::vector<Metabolite*> reactants_;
    std::vector<Metabolite*> products_;
    ReactionType type_;
    double kcat;

public:
    Reaction();
    explicit Reaction(std::string name_v, std::vector<Metabolite*> reactants_v, std::vector<Metabolite*> products_v, ReactionType reaction_type_v, double kcat_v);

    //Accessor
    std::string GetName() const;
    std::vector<Metabolite*> GetReactants() const;
    std::vector<Metabolite*> GetProducts() const;
    ReactionType GetType() const;
    double GetKCat() const;

    bool react();

    //Modifiers
    void SetName(std::string name_v);
    void SetReactants(std::vector<Metabolite*> reactants_v);
    void SetProducts(std::vector<Metabolite*> product_v);
    void SetReactionType(ReactionType reaction_type_v);
    void SetKCat(double kcat_v);

    bool operator==(const Reaction &rhs) const;
    bool operator!=(const Reaction &rhs) const;
};

#endif //RXN_H
