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
    const char* json_char_arr = json_file.c_str();
    std::cout << json_char_arr << std:: endl;
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
    if (std::strncmp(document["kcat_units"].GetString(), "per_sec", 7)) {
        kcat_units = per_sec;
        std::cout << "kcat_units are per_sec";
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
