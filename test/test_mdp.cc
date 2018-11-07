#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symctrl/mdp.hpp>

TEST_CASE("Analysis: ctrb", "[analysis]") {
  REQUIRE(1 == 1);
  REQUIRE(2 == 2);
}
