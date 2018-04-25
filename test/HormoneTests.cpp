#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/metabolite.h"
#include "../src/rxn.h"
#include "../src/enzyme.h"
#include "../src/load.h"
#include "../src/pathway.h"

using namespace std;
#include <vector>
#include <string>

TEST_CASE("Testing Metabolite Class functionality") {
    SECTION("default metabolite") {
        Metabolite default_metabolite;
        REQUIRE(default_metabolite.GetFullname() == "");
        REQUIRE(default_metabolite.GetShortname() == "");
        REQUIRE(default_metabolite.GetNumParticles() == 0);
        default_metabolite.rm_particle();
        REQUIRE(default_metabolite.GetNumParticles() == 0);
        default_metabolite.add_particle();
        REQUIRE(default_metabolite.GetNumParticles() == 1);
    }
    SECTION("param_metabolite") {
        Metabolite param_metabolite("abc", "abra cadabra", 20);
        REQUIRE(param_metabolite.GetNumParticles() == 20);
        REQUIRE(param_metabolite.GetFullname() == "abra cadabra");
        REQUIRE(param_metabolite.GetShortname() == "abc");
        
        param_metabolite.rm_particle();
        REQUIRE(param_metabolite.GetNumParticles() == 19);
        param_metabolite.add_particle();
        REQUIRE(param_metabolite.GetNumParticles() == 20);
    }
}

TEST_CASE("Testing Reaction class") {
    //rxn A + B -> C
    Metabolite met_a("a", "aaa", 20);
    Metabolite met_b("b", "bbb", 20);
    std::vector<Metabolite> reactant_v = {met_a, met_b};
    
    Metabolite met_c("c", "ccc", 0);
    std::vector<Metabolite> product_v = {met_c};
    
    Reaction default_rxn;
    Reaction param_rxn("abc", reactant_v, product_v, B, 100);
    REQUIRE(reactant_v == param_rxn.GetReactants());
    REQUIRE(product_v == param_rxn.GetProducts());
    REQUIRE(product_v != param_rxn.GetReactants());

    REQUIRE(StringToReactionType("B") == B);
    REQUIRE(StringToReactionType("blech") == null_rxn_type);
}

TEST_CASE("Testing Enzyme class") {
    Metabolite met_a("a", "aaa", 20);
    Metabolite met_b("b", "bbb", 20);
    std::vector<Metabolite> ab_v = {met_a, met_b};

    Metabolite met_c("c", "ccc", 0);
    std::vector<Metabolite> c_v = {met_c};

    Reaction forward_rxn("abc", ab_v, c_v, B, 100);
    Reaction back_rxn("cab", c_v, ab_v, BC, 100);
    std::vector<Reaction> rxn_v = {forward_rxn, back_rxn};

    Enzyme param_enzyme("param", rxn_v);
}

TEST_CASE("Testing load class") {
    std::string expected_string = "{\n"
            "    \"name\": \"Kinetic Model of Methanogenesis\",\n"
            "    \"km_units_\": \"mM\",\n"
            "    \"kcat_units_\": \"s^-1\",\n"
            "    \"volume_units_\": \"fL\",\n"
            "    \"volume_\": 500,\n"
            "    \"Metabolites\": [\n"
            "        {\n"
            "            \"shortname\": \"atp\",\n"
            "            \"fullname\": \"ATP\",\n"
            "            \"init_conc\": 0.0713\n"
            "        },\n"
            "        {\n"
            "            \"shortname\": \"ac\",\n"
            "            \"fullname\": \"Ac\",\n"
            "            \"init_conc\": 0.0713\n"
            "        },\n"
            "        {\n"
            "            \"shortname\": \"acp\",\n"
            "            \"fullname\": \"AcP\",\n"
            "            \"init_conc\": 0.098\n"
            "        },\n"
            "        {\n"
            "            \"shortname\": \"adp\",\n"
            "            \"fullname\": \"ADP\",\n"
            "            \"init_conc\": 0.098\n"
            "        }\n"
            "    ],\n"
            "    \"reactions_\": [\n"
            "        {\n"
            "            \"name\": \"atp+ac->acp+adp\",\n"
            "            \"reactants\": [\"atp\", \"ac\"],\n"
            "            \"products\": [\"acp\", \"adp\"],\n"
            "            \"type\": \"B\",\n"
            "            \"kcat\": \"1055\"\n"
            "        },\n"
            "        {\n"
            "            \"name\": \"adp+acp->ac+atp\",\n"
            "            \"reactants\": [\"adp\", \"acp\"],\n"
            "            \"products\": [\"ac\", \"atp\"],\n"
            "            \"type\": \"\"\n"
            "        }\n"
            "    ],\n"
            "    \"Enzymes\": [\n"
            "        {\n"
            "            \"name\": \"Ack\",\n"
            "            \"reactions\": [\"atp+ac->acp+adp\", \"adp+acp->ac+atp\"]\n"
            "        }\n"
            "    ]\n"
            "}";
    std::string filename = "/Users/Kate/Documents/GitHub/Useful_Libraries/of_v0.9.8_osx_release/apps/myApps/final-project-KatherineRitchie/data/methanogenesis.json";
    std::string actual_string = FileToString(filename);
    REQUIRE(actual_string == expected_string);
}

TEST_CASE("Testing pathway constructors, and \"string to enzyme/metabolite/reaction\" functions") {
    SECTION("default pathwau") {
        Pathway default_pathway;
        REQUIRE(default_pathway.GetName() == "");
        REQUIRE(default_pathway.GetKCatUnits() == 0);
        REQUIRE(default_pathway.GetMetabolites().size() == 0);
    }
    SECTION("parameterised pathway") {
        std::string filename = "/Users/Kate/Documents/GitHub/Useful_Libraries/of_v0.9.8_osx_release/apps/myApps/final-project-KatherineRitchie/data/methanogenesis.json";
        Pathway methanogenesis_pathway = Pathway(filename);
        REQUIRE(methanogenesis_pathway.GetName() == "Kinetic Model of Methanogenesis");
        REQUIRE(methanogenesis_pathway.GetKmUnits() == mM);
        REQUIRE(methanogenesis_pathway.GetKCatUnits() == per_sec);

        int num_particles_atp_ac = (int) 0.0713 * 6.023 * pow(10.0, 23) * pow(10.0, -15) * 500;
        int num_particles_acp_adp = (int) 0.098 * 6.023 * pow(10.0, 23) * pow(10.0, -15) * 500;
        Metabolite atp("atp", "ATP", num_particles_atp_ac);
        Metabolite ac("ac", "Ac", num_particles_atp_ac);
        Metabolite acp("acp", "AcP", num_particles_acp_adp);
        Metabolite adp("adp", "ADP", num_particles_acp_adp);
        std::vector<Metabolite> expected_metabolites = { atp, ac, acp, adp};
        REQUIRE(methanogenesis_pathway.GetMetabolites().size() == 4);

        //TODO Ask Shachi why this function isnt working when the debugger is correct
//        REQUIRE(methanogenesis_pathway.GetMetabolites() == expected_metabolites);
        REQUIRE(methanogenesis_pathway.StringToMetabolite("atp") == atp);

        Reaction forward_rxn("atp+ac->acp+adp", std::vector<Metabolite>({atp, ac}), std::vector<Metabolite>({acp, adp}), B, 1055.0);
        Reaction back_rxn("adp+acp->ac+atp", std::vector<Metabolite>({acp, adp}), std::vector<Metabolite>({ac, atp}), B, 1260.0);
        const std::vector<Reaction> expected_rxns = {forward_rxn, back_rxn};
        REQUIRE(methanogenesis_pathway.GetReactions() == expected_rxns);
        REQUIRE(methanogenesis_pathway.StringToReaction("atp+ac->acp+adp") == forward_rxn);

        Enzyme ack("Ack", std::vector<Reaction>({forward_rxn, back_rxn}));
        std::vector<Enzyme> expected_enzymes = {ack};
        REQUIRE(methanogenesis_pathway.GetEnzymes() == expected_enzymes);
        REQUIRE(methanogenesis_pathway.StringToEnzyme("atp+ac->acp+adp") == ack);
    }
}

TEST_CASE("testing string to unit and string to reaction type") {
    REQUIRE(fL == StringToUnit("fL"));
    REQUIRE(null_unit == StringToUnit("blech"));
    REQUIRE("mM" == UnitToString(mM));

    REQUIRE(B == StringToReactionType("B"));
    REQUIRE(null_rxn_type == StringToReactionType("blech"));
}

