#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/metabolite.h"
#include "../src/rxn.h"
#include "../src/enzyme.h"

using namespace std;
#include <vector>

TEST_CASE("Testing Metabolite Class functionality") {
    SECTION("default metabolite") {
        Metabolite default_metabolite;
        REQUIRE(default_metabolite.get_fullname() == "");
        REQUIRE(default_metabolite.get_shortname() == "");
        REQUIRE(default_metabolite.get_num_particles() == 0);
        default_metabolite.rm_particle();
        REQUIRE(default_metabolite.get_num_particles() == 0);
        default_metabolite.add_particle();
        REQUIRE(default_metabolite.get_num_particles() == 1);
    }
    SECTION("param_metabolite") {
        Metabolite param_metabolite("abc", "abra cadabra", 20);
        REQUIRE(param_metabolite.get_num_particles() == 20);
        REQUIRE(param_metabolite.get_fullname() == "abra cadabra");
        REQUIRE(param_metabolite.get_shortname() == "abc");
        
        param_metabolite.rm_particle();
        REQUIRE(param_metabolite.get_num_particles() == 19);
        param_metabolite.add_particle();
        REQUIRE(param_metabolite.get_num_particles() == 20);
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
    Reaction param_rxn("abc", reactant_v, product_v);
    REQUIRE(reactant_v == param_rxn.get_reactants());
    REQUIRE(product_v == param_rxn.get_products());
    REQUIRE(product_v != param_rxn.get_reactants());
}

TEST_CASE("Testing Enzyme class") {
    Metabolite met_a("a", "aaa", 20);
    Metabolite met_b("b", "bbb", 20);
    std::vector<Metabolite> ab_v = {met_a, met_b};

    Metabolite met_c("c", "ccc", 0);
    std::vector<Metabolite> c_v = {met_c};

    Reaction forward_rxn("abc", ab_v, c_v);
    Reaction back_rxn("cab", c_v, ab_v);
    std::vector<Reaction> rxn_v = {forward_rxn, back_rxn};

    Enzyme param_enzyme(rxn_v);

}

