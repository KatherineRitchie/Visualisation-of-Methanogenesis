//
// Created by Katherine Ritchie on 4/22/18.
//

#include "pathway.h"


unit StringToUnit(std::string unit_string) {
    if (unit_string == "mM") {
        return mM;
    }
    if (unit_string == "per_sec") {
        return per_sec;
    }
    if (unit_string == "fL") {
        return fL;
    }
    return null_unit;
}

std::string UnitToString(unit unit_v) {
    if (unit_v == mM) {
        return "mM";
    }
    if (unit_v == per_sec) {
        return "per_sec";
    }
    if (unit_v == fL) {
        return "fL";
    }
    return NULL;
}

Pathway::Pathway() {
    name_ = "";
    kcat_units_ = null_unit;
    km_units_ = null_unit;
    volume_units_ = null_unit;
    metabolites_ = {};
    reactions_ = {};
    enzymes_ = {};
}

Pathway::Pathway(std::string json_filename) {
    std::string json_file = FileToString(json_filename);
    rapidjson::Document document;
    const char *json_char_arr = json_file.c_str();
    std::cout << json_char_arr << std::endl;
    if (document.Parse(json_char_arr).HasParseError()) {
        std::cout << "something is wrong with the json you passed to the pathway constructor!!!" << std::endl;
        return;
    }
    name_ = document["name"].GetString();
    //TODO make it such that units are assigned conditionally
    km_units_ = mM;
    kcat_units_ = per_sec;
    volume_units_ = fL;

    //The following stanza parses the DOM tree and assigns the Metabolites to the Pathway
    for (auto& metabolite : document["Metabolites"].GetArray()) {
        std::string shortname_v = metabolite["shortname"].GetString();
        std::string fullname_v = metabolite["fullname"].GetString();
        //TODO calculate actual number of particles that should be added
        int num_particles_v = metabolite["init_conc"].GetDouble() * 1000;
        int x_pos_v = metabolite["x_pos"].GetInt();
        int y_pos_v = metabolite["y_pos"].GetInt();
        Metabolite new_metabolite(shortname_v, fullname_v, num_particles_v, x_pos_v, y_pos_v);
        metabolites_.push_back(new_metabolite);
        metabolite.GetObject();
    }

    for (auto& reaction : document["Reactions"].GetArray()) {
        std::string name_v = reaction["name"].GetString();

        std::vector<Metabolite> reactant_metabolite_vect;
        for (auto& reactant : reaction["reactants"].GetArray()) {
            reactant_metabolite_vect.push_back(StringToMetabolite(reactant.GetString()));
        }

        std::vector<Metabolite> product_metabolite_vect;
        for (auto& product : reaction["products"].GetArray()) {
            product_metabolite_vect.push_back(StringToMetabolite(product.GetString()));
        }

        ReactionType rxn_type_v = StringToReactionType(reaction["type"].GetString());
        double kcat_v = reaction["kcat"].GetDouble();

        Reaction new_reaction(name_v, reactant_metabolite_vect, product_metabolite_vect, rxn_type_v, kcat_v);
        reactions_.push_back(new_reaction);
    }

    for (auto& enzyme : document["Enzymes"].GetArray()) {
        std::string name_v = enzyme["name"].GetString();
        std::vector<Reaction> reaction_vect;
        for (auto& reaction : enzyme["reactions"].GetArray()) {
            reaction_vect.push_back(StringToReaction(reaction.GetString()));
        }
        int x_pos_v = enzyme["x_pos"].GetInt();
        int y_pos_v = enzyme["y_pos"].GetInt();

        Enzyme new_enzyme(name_v, reaction_vect, x_pos_v, y_pos_v);
        enzymes_.push_back(new_enzyme);
    }
}

std::string Pathway::GetName() const {
    return name_;
}

unit Pathway::GetKmUnits() const {
    return km_units_;
}

unit Pathway::GetKCatUnits() const {
    return kcat_units_;
}

unit Pathway::GetVolumeUnits() const {
    return volume_units_;
}

int Pathway::GetVolume() const {
    return volume_units_;
}

std::vector<Metabolite> Pathway::GetMetabolites() const {
    return metabolites_;
}

std::vector<Reaction> Pathway::GetReactions() const {
    return reactions_;
}

std::vector<Enzyme> Pathway::GetEnzymes() const {
    return enzymes_;
}

Metabolite Pathway::StringToMetabolite(std::string metabolite_string) {
    for (Metabolite metabolite : metabolites_) {
        if (metabolite.GetShortname() == metabolite_string) {
            return metabolite;
        }
    }
    return Metabolite();
}

Reaction Pathway::StringToReaction(std::string reaction_string) {
    for (Reaction reaction : reactions_) {
        if (reaction.GetName() == reaction_string) {
            return reaction;
        }
    }
    return Reaction();
}

Enzyme Pathway::StringToEnzyme(std::string enzyme_string) {
    for (Enzyme enzyme : enzymes_) {
        if (enzyme.GetName() == enzyme_string) {
            return enzyme;
        }
    }
    return Enzyme();
}

