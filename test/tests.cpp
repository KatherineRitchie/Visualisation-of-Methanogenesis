#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/metabolite.h"
#include "../src/reaction.h"
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
        REQUIRE(default_metabolite.GetInitNumParticles() == (long) 0);
    }
    SECTION("param_metabolite") {
        Metabolite param_metabolite("abc", "abra cadabra", (long) 20, (long) 100, 200);
        REQUIRE(param_metabolite.GetInitNumParticles() == (long) 20);
        REQUIRE(param_metabolite.GetFullname() == "abra cadabra");
        REQUIRE(param_metabolite.GetShortname() == "abc");
        REQUIRE(param_metabolite.GetXPos() == 100);
        REQUIRE(param_metabolite.GetYPos() == 200);
    }
}

TEST_CASE("Testing Reaction class") {
    //rxn A + B -> C
    Metabolite *met_a = new Metabolite("a", "aaa", (long) 20, 100, 200);
    Metabolite *met_b = new Metabolite("b", "bbb", (long) 20, 50, 100);
    std::vector<Metabolite*> reactant_v = {met_a, met_b};
    
    Metabolite *met_c = new Metabolite("c", "ccc", (long) 0, 0, 0);
    std::vector<Metabolite*> product_v = {met_c};
    
    Reaction default_rxn;
    Reaction *param_rxn = new Reaction("abc", reactant_v, product_v, B, 100);
    REQUIRE(reactant_v == param_rxn->GetReactants());
    REQUIRE(product_v == param_rxn->GetProducts());
    REQUIRE(product_v != param_rxn->GetReactants());

    REQUIRE(StringToReactionType("B") == B);
    REQUIRE(StringToReactionType("blech") == null_rxn_type);
}

TEST_CASE("Testing Enzyme class") {
    Metabolite *met_a = new Metabolite("a", "aaa", (long) 20, 0, 0);
    Metabolite *met_b = new Metabolite("b", "bbb", (long) 20, 0, 0);
    std::vector<Metabolite*> ab_v = {met_a, met_b};

    Metabolite *met_c = new Metabolite("c", "ccc", (long) 0, 0, 0);
    std::vector<Metabolite*> c_v = {met_c};

    Reaction *forward_rxn = new Reaction("abc", ab_v, c_v, B, 100);
    Reaction *back_rxn = new Reaction("cab", c_v, ab_v, BC, 100);
    std::vector<Reaction*> rxn_v = {forward_rxn, back_rxn};

    Enzyme *param_enzyme = new Enzyme("param", rxn_v, 0, 0);
    REQUIRE(param_enzyme->GetName() == "param");
    REQUIRE(param_enzyme->GetReactions() == rxn_v);
    REQUIRE(param_enzyme->GetXPos() + param_enzyme->GetYPos() == 0);
}

TEST_CASE("Testing load class") {
    std::string expected_string = "{"
            "    \"name\": \"Kinetic Model of Methanogenesis\","
            "    \"km_units\": \"mM\","
            "    \"kcat_units\": \"per_sec\","
            "    \"volume_units\": \"fL\","
            "    \"volume\": 20,"
            "    \"Metabolites\": ["
            "        {"
            "            \"shortname\": \"atp\","
            "            \"fullname\": \"ATP\","
            "            \"init_conc\": 0.0713,"
            "            \"x_pos\": 120,"
            "            \"y_pos\": 120"
            "        },"
            "        {"
            "            \"shortname\": \"ac\","
            "            \"fullname\": \"Ac\","
            "            \"init_conc\": 0.0713,"
            "            \"x_pos\": 360,"
            "            \"y_pos\": 120"
            "        },"
            "        {"
            "            \"shortname\": \"acp\","
            "            \"fullname\": \"AcP\","
            "            \"init_conc\": 0.098,"
            "            \"x_pos\": 360,"
            "            \"y_pos\": 360"
            "        },"
            "        {"
            "            \"shortname\": \"adp\","
            "            \"fullname\": \"ADP\","
            "            \"init_conc\": 0.098,"
            "            \"x_pos\": 120,"
            "            \"y_pos\": 360"
            "        }"
            "    ],"
            "    \"Reactions\": ["
            "        {"
            "            \"name\": \"atp+ac->acp+adp\","
            "            \"reactants\": [\"atp\", \"ac\"],"
            "            \"products\": [\"acp\", \"adp\"],"
            "            \"type\": \"B\","
            "            \"kcat\": 1055.0"
            "        },"
            "        {"
            "            \"name\": \"adp+acp->ac+atp\","
            "            \"reactants\": [\"adp\", \"acp\"],"
            "            \"products\": [\"ac\", \"atp\"],"
            "            \"type\": \"B\","
            "            \"kcat\": 1260.0"
            "        }"
            "    ],"
            "    \"Enzymes\": ["
            "        {"
            "            \"name\": \"Ack\","
            "            \"reactions\": [\"atp+ac->acp+adp\", \"adp+acp->ac+atp\"],"
            "            \"x_pos\": 240,"
            "            \"y_pos\": 240"
            "        }"
            "    ]"
            "}";
    std::string filename = "/Users/Kate/Documents/GitHub/Useful_Libraries/of_v0.9.8_osx_release/apps/myApps/final-project-KatherineRitchie/data/test_json.json";
    std::string actual_string = FileToString(filename);
    REQUIRE(actual_string == expected_string);
}

TEST_CASE("Testing pathway constructors, and \"string to enzyme/metabolite/reaction\" functions") {
    SECTION("default pathway") {
        Pathway default_pathway;
        REQUIRE(default_pathway.GetName() == "");
        REQUIRE(default_pathway.GetKCatUnits() == 0);
        REQUIRE(default_pathway.GetMetabolites().size() == 0);
    }
    SECTION("parameterised pathway") {
        std::string filename = "/Users/Kate/Documents/GitHub/Useful_Libraries/of_v0.9.8_osx_release/apps/myApps/final-project-KatherineRitchie/data/test_json.json";
        Pathway methanogenesis_pathway(filename);
        REQUIRE(methanogenesis_pathway.GetName() == "Kinetic Model of Methanogenesis");
        REQUIRE(methanogenesis_pathway.GetKmUnits() == mM);
        REQUIRE(methanogenesis_pathway.GetKCatUnits() == per_sec);

        long num_particles_atp_ac = (long) (pow(10.0, 4) * (double) (0.0713 * 6.023 * 500));
        long num_particles_acp_adp = (long) (pow(10.0, 4) * (double) (0.098 * 6.023 * 500));
        Metabolite *atp = new Metabolite("atp", "ATP", num_particles_atp_ac, 120, 120);
        Metabolite *ac = new Metabolite("ac", "Ac", num_particles_atp_ac, 360, 120);
        Metabolite *acp = new Metabolite("acp", "AcP", num_particles_acp_adp, 360, 360);
        Metabolite *adp = new Metabolite("adp", "ADP", num_particles_acp_adp, 120, 360);
        std::vector<Metabolite*> expected_metabolites = { atp, ac, acp, adp};
        REQUIRE(methanogenesis_pathway.GetMetabolites()[0]->GetShortname() == expected_metabolites[0]->GetShortname());

        Reaction *forward_rxn = new Reaction("atp+ac->acp+adp", std::vector<Metabolite*>({atp, ac}), std::vector<Metabolite*>({acp, adp}), B, 1055.0);
        Reaction *back_rxn = new Reaction("adp+acp->ac+atp", std::vector<Metabolite*>({adp, acp}), std::vector<Metabolite*>({ac, atp}), B, 1260.0);
        const std::vector<Reaction*> expected_rxns = {forward_rxn, back_rxn};
        REQUIRE(methanogenesis_pathway.GetReactions()[0]->GetType() == expected_rxns[0]->GetType());

        Enzyme *ack = new Enzyme("Ack", std::vector<Reaction*>({forward_rxn, back_rxn}), 0, 0);
        std::vector<Enzyme*> expected_enzymes = {ack};
        REQUIRE(methanogenesis_pathway.GetEnzymes()[0]->GetReactions()[0]->GetType() == expected_enzymes[0]->GetReactions()[0]->GetType());
        REQUIRE(methanogenesis_pathway.GetEnzymes()[0]->GetReactions()[0]->GetKCat() == expected_enzymes[0]->GetReactions()[0]->GetKCat());
        REQUIRE(methanogenesis_pathway.GetEnzymes()[0]->GetReactions().size() == expected_enzymes[0]->GetReactions().size());
        REQUIRE(methanogenesis_pathway.GetEnzymes()[0]->GetReactions().size() == expected_enzymes[0]->GetReactions().size());
        REQUIRE(methanogenesis_pathway.StringToEnzyme("Ack")->GetName() == ack->GetName());
    }
}

TEST_CASE("testing string to unit and string to reaction type") {
    REQUIRE(fL == StringToUnit("fL"));
    REQUIRE(null_unit == StringToUnit("blech"));
    REQUIRE("mM" == UnitToString(mM));

    REQUIRE(B == StringToReactionType("B"));
    REQUIRE(null_rxn_type == StringToReactionType("blech"));
}

TEST_CASE("testing time incrementer") {
    Metabolite *met_a = new Metabolite("a", "aaa", 20, 0, 0);
    Metabolite *met_b = new Metabolite("b", "bbb", 20, 0, 0);
    std::vector<Metabolite*> ab_v = {met_a, met_b};

    Metabolite *met_c = new Metabolite("c", "ccc", 0, 0, 0);
    std::vector<Metabolite*> c_v = {met_c};

    Reaction *forward_rxn = new Reaction("abc", ab_v, c_v, B, 2);
    Reaction *back_rxn = new Reaction("cba", c_v, ab_v, B, 1);
    std::vector<Reaction*> rxn_v = {forward_rxn, back_rxn};

    Enzyme *enzyme = new Enzyme("param", rxn_v, 0, 0);
    Pathway pathway("simple", mM, per_sec, fL, 500, std::vector<Metabolite*>({met_a, met_b, met_c}), std::vector<Reaction*>
        ({forward_rxn, back_rxn}), std::vector<Enzyme*>({enzyme}));

    pathway.incrementTime();

    REQUIRE(pathway.curr_state[met_a] == 18);
    REQUIRE(pathway.curr_state[met_b] == 18);
    REQUIRE(pathway.curr_state[met_c] == 2);
}

TEST_CASE("testing canReact() method") {
    Metabolite *met_a = new Metabolite("a", "aaa", 20, 0, 0);
    Metabolite *met_b = new Metabolite("b", "bbb", 20, 0, 0);
    std::vector<Metabolite*> ab_v = {met_a, met_b};

    Metabolite *met_c = new Metabolite("c", "ccc", 0, 0, 0);
    std::vector<Metabolite*> c_v = {met_c};

    Reaction *possible_rxn = new Reaction("abc", ab_v, c_v, B, 2);
    Reaction *impossible_rxn = new Reaction("dec", c_v, ab_v, B, 2);
    std::vector<Reaction*> rxn_vect = {possible_rxn, impossible_rxn};

    Enzyme *enzyme = new Enzyme("enzyme", rxn_vect, 0, 0);
    Pathway pathway("simple", mM, per_sec, fL, 500, std::vector<Metabolite*>({met_a, met_b, met_c}), rxn_vect, std::vector<Enzyme*>({enzyme}));

    REQUIRE(pathway.CanReact(possible_rxn) == true);
    REQUIRE(pathway.CanReact(impossible_rxn) == false);

    pathway.incrementTime();
    pathway.incrementTime();

    REQUIRE(pathway.CanReact(possible_rxn) == true);
    REQUIRE(pathway.CanReact(impossible_rxn) == true);
}
