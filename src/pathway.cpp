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

Pathway::Pathway(std::string name_v, unit km_unit_v, unit kcat_unit_v, unit volume_unit_v, int volume_v,
        std::vector<Metabolite*> metabolites_vect, std::vector<Reaction*> reactions_vect, std::vector<Enzyme*>
enzymes_vect) {
    name_ = name_v;
    km_units_ = km_unit_v;
    kcat_units_ = kcat_unit_v;
    volume_ = volume_unit_v;
    metabolites_ = metabolites_vect;
    reactions_ = reactions_vect;
    enzymes_ = enzymes_vect;
    //initialise curr_state map
    for (Metabolite *metabolite : metabolites_) {
        curr_state[metabolite] = metabolite->GetInitNumParticles();
    }
}

Pathway::Pathway(std::string json_filename) {
    std::string json_file = FileToString(json_filename);
    rapidjson::Document document;
    const char *json_char_arr = json_file.c_str();
    if (document.Parse(json_char_arr).HasParseError()) {
        std::cout << "something is wrong with the json you passed to the pathway constructor!!!" << std::endl;
        return;
    }

    // The following four lines parses the DOM tree and fills out the names and units of the Pathway
    name_ = document["name"].GetString();
    km_units_ = StringToUnit(document["km_units"].GetString());
    kcat_units_ = StringToUnit(document["kcat_units"].GetString());
    volume_units_ = StringToUnit(document["volume_units"].GetString());

    // The following stanza parses the DOM tree and assigns the Metabolites to the Pathway
    for (auto& metabolite : document["Metabolites"].GetArray()) {
        std::string shortname_v = metabolite["shortname"].GetString();
        std::string fullname_v = metabolite["fullname"].GetString();
        double init_conc_v = metabolite["init_conc"].GetDouble();
        int volume_v = document["volume"].GetDouble();
        long num_particles_v = ConcToNumParticles(init_conc_v, volume_v);
        int x_pos_v = metabolite["x_pos"].GetInt();
        int y_pos_v = metabolite["y_pos"].GetInt();

        Metabolite *new_metabolite = new Metabolite(shortname_v, fullname_v, num_particles_v, x_pos_v, y_pos_v);
        metabolites_.push_back(new_metabolite);
        metabolite.GetObject();
    }

    //initialise curr_state map with Metabolites
    for (Metabolite *metabolite : metabolites_) {
        curr_state[metabolite] = metabolite->GetInitNumParticles();
    }

    // The following stanza parses the DOM tree and assigns the Reactions to the Pathway
    for (auto& reaction : document["Reactions"].GetArray()) {
        std::string name_v = reaction["name"].GetString();

        std::vector<Metabolite*> reactant_metabolite_vect;
        for (auto& reactant : reaction["reactants"].GetArray()) {
            reactant_metabolite_vect.push_back(StringToMetabolite(reactant.GetString()));
        }

        std::vector<Metabolite*> product_metabolite_vect;
        for (auto& product : reaction["products"].GetArray()) {
            product_metabolite_vect.push_back(StringToMetabolite(product.GetString()));
        }

        ReactionType rxn_type_v = StringToReactionType(reaction["type"].GetString());
        double kcat_v = reaction["kcat"].GetDouble();

        Reaction *new_reaction = new Reaction(name_v, reactant_metabolite_vect, product_metabolite_vect, rxn_type_v, kcat_v);
        reactions_.push_back(new_reaction);
    }

    // The following stanza parses the DOM tree and assigns the Enzymes to the Pathway
    for (auto& enzyme : document["Enzymes"].GetArray()) {
        std::string name_v = enzyme["name"].GetString();
        std::vector<Reaction*> reaction_vect;
        for (auto& reaction : enzyme["reactions"].GetArray()) {
            reaction_vect.push_back(StringToReaction(reaction.GetString()));
        }
        int x_pos_v = enzyme["x_pos"].GetInt();
        int y_pos_v = enzyme["y_pos"].GetInt();

        Enzyme *new_enzyme = new Enzyme(name_v, reaction_vect, x_pos_v, y_pos_v);
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

std::vector<Metabolite*> Pathway::GetMetabolites() const {
    return metabolites_;
}

std::vector<Reaction*> Pathway::GetReactions() const {
    return reactions_;
}

std::vector<Enzyme*> Pathway::GetEnzymes() const {
    return enzymes_;
}

bool Pathway::CanReact(Reaction* reaction) {
    for (Metabolite *reactant : reaction->GetReactants()) {
        if (curr_state[reactant] <= reaction->GetKCat()) {
            return false;
        }
    }
    return true;
}

double Pathway::GetEnzymeEfficacy(const Enzyme& enzyme) const {
    double enzyme_efficacy = 0.0;
    for (Reaction *reaction : enzyme.GetReactions()) {
        enzyme_efficacy += reaction->GetKCat();
    }
    enzyme_efficacy = enzyme_efficacy / enzyme.GetReactions().size();
    // Division by 1000 is arbitrary, it allows the user to see the kcat values of enzymes between 0 and 100 reactions
    // per sec. The design tradeoff is that all enzymes with high kcat values are similarly clumped together as just
    // 'fast'.
    enzyme_efficacy = enzyme_efficacy / 1000;
    return enzyme_efficacy;
}

Metabolite* Pathway::StringToMetabolite(std::string metabolite_string) {
    for (Metabolite* metabolite : metabolites_) {
        if (metabolite->GetShortname() == metabolite_string) {
            return metabolite;
        }
    }
    return nullptr;
}

void Pathway::incrementTime() {
    std::map<Metabolite*, int> change_in_particles;
    for (Metabolite *metabolite : metabolites_) {
        change_in_particles[metabolite] = 0;
    }

    for (Enzyme *enzyme : enzymes_) {
        for (Reaction *reaction : enzyme->GetReactions()) {
            // kcat is a measure of reactions per second. If we are incrementing the time by one second, we must repeat
            // a reaction that many times
            for (int kcat_idx = 0; kcat_idx < (int) reaction->GetKCat(); kcat_idx++) {
                for (Metabolite *reactant : reaction->GetReactants()) {
                    if (CanReact(reaction)) {
                        // react one particle of every reactant
                        change_in_particles[reactant] -= 1;
                    }
                }
                for (Metabolite *product : reaction->GetProducts()) {
                    if (CanReact(reaction)) {
                        // create one particle of every product
                        change_in_particles[product] += 1;
                    }
                }
            }
        }
    }

    // apply changes to curr_state map ***all at the same time***
    for (Metabolite *metabolite : metabolites_) {
        long new_num_particles = (curr_state[metabolite] + change_in_particles[metabolite]);
        new_num_particles = (new_num_particles < 0 ? curr_state[metabolite] : new_num_particles);
        curr_state[metabolite] = new_num_particles;
    }
}

Reaction* Pathway::StringToReaction(std::string reaction_string) {
    for (Reaction* reaction : reactions_) {
        if (reaction->GetName() == reaction_string) {
            return reaction;
        }
    }
    return nullptr;
}

Enzyme* Pathway::StringToEnzyme(std::string enzyme_string) {
    for (Enzyme* enzyme : enzymes_) {
        if (enzyme->GetName() == enzyme_string) {
            return enzyme;
        }
    }
    return nullptr;
}
