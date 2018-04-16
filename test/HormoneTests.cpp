#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testing Hormone Class functionality") {
    SECTION("default hormone") {
        Hormone default_hormone():
        REQUIRE(default_hormone.get_fullname() == NULL);
        REQUIRE(default_hormone.get_shortname() == NULL);
        REQUIRE(default_hormone.get_num_particles() == 0);
        default_hormone.rm_particle();
        REQUIRE(default_hormone.get_num_particles() == 0);
        default_hormone.add_particle();
        REQUIRE(default_hormone.get_num_particles() == 1);
    }
    SECTION("parameterised hormone") {
        Hormone param_hormone("abc", "abra cadabra", 20);
        REQUIRE(param_hormone.get_num_particles() == 20);
        REQUIRE(param_hormone.get_fullname() == "abra cadabra");
        REQUIRE(param_hormone.get_shortname() == "abd");
        
        param_hormone.rm_particle();
        REQUIRE(param_hormone.get_num_particles() == 19);
        param_hormone.add_particles();
        REQUIRE(param_hormone.get_num_particles() == 20);
    }
}

TEST_CASE("Testing Reaction class") {
}
