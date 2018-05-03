#ifndef RXN_H
#define RXN_H

#include "metabolite.h"
#include <vector>
#include <string>

// provides information about the various types of kinetics to apply
// TODO implement accurate physical chemistry simulation
enum ReactionType {
    null_rxn_type = 0,
    B = 1,          // irreversible bimolecular Michaelis-Menten
    BC = 2,         // irreversible bimolecular Michaelis-Menten for the two underlined reactants with a constant flux term for the others, which is set to the  ux calculated for bimolecular reaction
    M = 3,          // irreversible unimolecular Michaelis-Menten
    F = 4           // first order reaction
};

ReactionType StringToReactionType(std::string reaction_type_string);        // converts string to reaction type enum

class Reaction {
    std::string name_;
    std::vector<Metabolite*> reactants_;
    std::vector<Metabolite*> products_;
    ReactionType type_;
    double kcat_;

public:
    // Constructors
    Reaction();
    explicit Reaction(std::string name_v, std::vector<Metabolite*> reactants_v, std::vector<Metabolite*> products_v, ReactionType reaction_type_v, double kcat_v);

    // Accessors
    std::string GetName() const;
    std::vector<Metabolite*> GetReactants() const;
    std::vector<Metabolite*> GetProducts() const;
    ReactionType GetType() const;
    double GetKCat() const;

    // Modifiers
    void SetName(std::string name_v);
    void SetReactants(std::vector<Metabolite*> reactants_v);
    void SetProducts(std::vector<Metabolite*> product_v);
    void SetReactionType(ReactionType reaction_type_v);
    void SetKCat(double kcat_v);

    // Equality operators
    bool operator==(const Reaction &rhs) const;
    bool operator!=(const Reaction &rhs) const;
};

#endif //RXN_H
