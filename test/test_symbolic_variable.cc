#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <memory>

#include <symctrl/math/symbolic.hpp>

using Controls::Math::sym_t;
using Controls::Math::sym_number;
using Controls::Math::sym_var;

// Uncomment this line to enable debugging.
// #define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << "----------" << '\n' << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

TEST_CASE("Symbolic Variable: Assignment", "[symbolic]") {
  {
    sym_var x("x");
    REQUIRE(x.as_str() == "x");
    REQUIRE(x == x);
  }

  {
    sym_var x("x");
    REQUIRE(x.as_str() == "x");
    REQUIRE(x == x);
    sym_var y = x;
    REQUIRE(y.as_str() == "x");
    REQUIRE(x == y);
    REQUIRE(y == x);
    REQUIRE(y == y);
    sym_var z = y;
    REQUIRE(z.as_str() == "x");
    REQUIRE(x == z);
    REQUIRE(z == x);
    REQUIRE(y == z);
    REQUIRE(z == y);
    REQUIRE(z == z);
  }

  {
    sym_var x("x");
    sym_var y = x;
    sym_var z = y;
    REQUIRE(z.as_str() == "x");
    REQUIRE(z == x);
    REQUIRE(z == y);
  }

  {
    sym_var x("x");
    sym_var y("x");
    sym_var z("z");
    REQUIRE(x == y);
    REQUIRE(y == x);
    REQUIRE(x != z);
    REQUIRE(y != z);
    REQUIRE(z != x);
    REQUIRE(z != y);
  }
}
