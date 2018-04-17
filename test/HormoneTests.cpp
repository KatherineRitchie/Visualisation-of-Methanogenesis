#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/Metabolite.h"

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
}
