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
#include <cstring>
#include <map>
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/prettywriter.h" // for stringify JSON

enum unit {
    null_unit = 0,
    mM = 1,
    per_sec = 2,
    fL = 3
};

unit StringToUnit(std::string unit_string);
std::string UnitToString(unit unit_v);

class Pathway {
    std::string name_;
    unit km_units_;
    unit kcat_units_;
    unit volume_units_;
    int volume_;
    std::vector<Metabolite*> metabolites_;
    std::vector<Reaction*> reactions_;
    std::vector<Enzyme*> enzymes_;


public:
    //This hashmap allows the graphics to very easily access what colour the Metabolite should be
    std::map<Metabolite, long> curr_state;

    Pathway();
    Pathway(std::string name_v, unit km_unit_v, unit kcat_unit_v, unit volume_unit_v, int volume_v,
            std::vector<Metabolite*> metabolites_vect, std::vector<Reaction*> reactions_vect, std::vector<Enzyme*>
            enzymes_vect);
    //TODO break up this horrible constructor its truly atrocious
    explicit Pathway(std::string json_filename);

    //Accessors
    std::string GetName() const;
    unit GetKmUnits() const;
    unit GetKCatUnits() const;
    unit GetVolumeUnits() const;
    int GetVolume() const;
    std::vector<Metabolite*> GetMetabolites() const;
    std::vector<Reaction*> GetReactions() const;
    std::vector<Enzyme*> GetEnzymes() const;

    //Modifiers
    void incrementTime();

    //The following functions accept a standard string and return a copy of a metabolite, reaction or enzyme
    // that is present in the pathway. If a matching one is not found, then a default reaction, metablite or
    // enzyme is returned.
    Metabolite* StringToMetabolite(std::string metabolite_string);   //Accepts metabolite shortName eg atp
    Reaction* StringToReaction(std::string reaction_string);         //Accepts Reaction name eg atp+ac->acp+adp
    Enzyme* StringToEnzyme(std::string enzyme_string);               //Accepts enzyme name eg Ack
};

#endif //PATHWAY_H
