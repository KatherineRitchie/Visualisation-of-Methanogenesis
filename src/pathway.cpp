//
// Created by Katherine Ritchie on 4/22/18.
//

#include "pathway.h"

Pathway::Pathway() {
    name_ = "";
    kcat_units = null;
    km_units_ = null;
    volume_units = null;
    Metabolites = {};
    Reactions = {};
    Enzymes = {};
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
    std::cout << "document does not have parse error \n";
    std::cout << "name is " << document["name"].GetString() << std::endl;
    name_ = document["name"].GetString();
    if (std::strncmp(document["km_units"].GetString(), "mM", 2)) {
        km_units_ = mM;
        std::cout << "km_units are mM";
    }
    std::cout << "km_units are not mM";
    //TOdo make it such that units are assigned conditionally
    kcat_units = per_sec;
    const auto &metabolite_v = document["Metabolites"];
    for (int i = 0; i < metabolite_v.Size(); i++) { // Uses SizeType instead of
        std::string shortname_v = document["Metabolites"][i]["shortname"].GetString();
        std::string fullname_v = document["Metabolites"][i]["fullname"].GetString();
        //TODO calculate actual number of particles that should be added
        int num_particles_v = document["Metabolites"][i]["init_conc"].GetDouble() * 1000;
        Metabolites.push_back(Metabolite(shortname_v, fullname_v, num_particles_v));
        std::cout << document["Metabolites"][i]["shortname"].GetString() << std::endl;
    }
    const auto &reaction_v = document["Reactions"];
    for (int rxn_i = 0; rxn_i < reaction_v.Size(); rxn_i++) {
        std::string name_v = document["Reactions"][rxn_i]["name"].GetString();

        const auto &reactant_string_v = document["Reactions"][rxn_i]["reactants"];
        std::vector<Metabolite> product_metabolite_v;
        for (int reactant_i = 0; reactant_i < reactant_string_v.Size(); reactant_i++) {
            product_metabolite_v.push_back(StringToMetabolite(document["Reactions"][rxn_i]["reactants"][reactant_i].GetString()));
        }

        const auto &product_string_v = document["Reactions"][rxn_i]["products"];
        std::vector<Metabolite> reactant_metabolite_v;
        for (int prod_i = 0; prod_i < product_string_v.Size(); prod_i++) {
            product_metabolite_v.push_back(StringToMetabolite(document["Reactions"][rxn_i]["products"][prod_i].GetString()));
        }
    }

    if (std::strncmp(document["kcat_units"].GetString(), "per_sec", 7)) {
        std::cout << "kcat_units are per_sec";
    } else {
        std::cout << "kcat units are not per_sec";
    }
    //TODO find better alternative to hard coding these numbers in
    if (std::strncmp(document["volume_units"].GetString(), "fL", 2)) {
        volume_units = fL;
        std::cout << "vol_units are fL";
    }
//    Metabolites = document["Metabolites"]
//    for (auto& metabolite : document.GetObject())
//        printf("Type of member %s is %s\n",
//               metabolite.name.GetString(), kTypeNames[m.value.GetType()]);
//    std::cout << document["name"].GetString() << std::endl;
    return;
}

std::string Pathway::GetName() const {
    return name_;
}

Pathway::unit Pathway::GetKmUnits() const {
    return km_units_;
}

Pathway::unit Pathway::GetKCatUnits() const {
    return kcat_units;
}

Pathway::unit Pathway::GetVolumeUnits() const {
    return volume_units;
}

int Pathway::GetVolume() const {
    return volume_units;
}

std::vector<Metabolite> Pathway::GetMetabolites() const {
    return Metabolites;
}

std::vector<Reaction> Pathway::GetReactions() const {
    return Reactions;
}

std::vector<Enzyme> Pathway::GetEnzymes() const {
    return Enzymes;
}

//TODO test these 'string to x' methods

Metabolite Pathway::StringToMetabolite(std::string metabolite_string) {
    for (Metabolite metabolite : Metabolites) {
        if (metabolite.GetShortname() == metabolite_string) {
            return metabolite;
        }
    }
    return Metabolite();
}

Reaction Pathway::StringToReaction(std::string reaction_string) {
    for (Reaction reaction : Reactions) {
        if (reaction.GetName() == reaction_string) {
            return reaction;
        }
    }
    return Reaction();
}

Enzyme Pathway::StringToEnzyme(std::string enzyme_string) {
    for (Enzyme enzyme : Enzymes) {
        if (enzyme.GetName() == enzyme_string) {
            return enzyme;
        }
    }
    return Enzyme();
}
