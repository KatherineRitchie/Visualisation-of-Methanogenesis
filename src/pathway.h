//
// Created by Katherine Ritchie on 4/22/18.
//

#ifndef PATHWAY_H
#define PATHWAY_H

#include "metabolite.h"
#include "rxn.h"
#include "enzyme.h"
#include "load.h"
#include <iostream>
#include <string>
#include <cstring>
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/prettywriter.h" // for stringify JSON
//TODO find a better way to implement json functionality than straight through the filename constructor

class Pathway {

public:
    enum unit {
        null,
        mM,
        per_sec,
        fL
    };

    Pathway();
    explicit Pathway(std::string json_filename);

    std::string GetName() const;
    unit GetKmUnits() const;
    unit GetKCatUnits() const;
    unit GetVolumeUnits() const;
    int GetVolume() const;
    std::vector<Metabolite> GetMetabolites() const;
    std::vector<Reaction> GetReactions() const;
    std::vector<Enzyme> GetEnzymes() const;

private:
    std::string name_;
    unit km_units_;
    //TODO rename these variables to have an underscore after field name
    unit kcat_units;
    unit volume_units;
    int volume;
    std::vector<Metabolite> Metabolites;
    std::vector<Reaction> Reactions;
    std::vector<Enzyme> Enzymes;
};

#endif //PATHWAY_H
