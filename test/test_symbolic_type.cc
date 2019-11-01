#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <memory>

#include <symctrl/math/symbolic.hpp>

using Controls::Math::sym_t;
using Controls::Math::sym_number;
using Controls::Math::sym_var;

// Uncomment this line to enable debugging.
#define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << "----------" << '\n' << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

TEST_CASE("Symbolic Variable: Assignment", "[symbolic]") {
  {
    sym_t x("x");
    REQUIRE(x.as_str() == "x");
    REQUIRE(x == x);
  }

  {
    sym_t x("x");
    REQUIRE(x.as_str() == "x");
    REQUIRE(x == x);
    sym_t y = x;
    REQUIRE(y.as_str() == "x");
    REQUIRE(x == y);
    REQUIRE(y == x);
    REQUIRE(y == y);
    sym_t z = y;
    REQUIRE(z.as_str() == "x");
    REQUIRE(x == z);
    REQUIRE(z == x);
    REQUIRE(y == z);
    REQUIRE(z == y);
    REQUIRE(z == z);
  }

  {
    sym_t x("x");
    sym_t y = x;
    sym_t z = y;
    REQUIRE(z.as_str() == "x");
    REQUIRE(z == x);
    REQUIRE(z == y);
  }

  {
    sym_t x("x");
    sym_t y("x");
    sym_t z("z");
    REQUIRE(x == y);
    REQUIRE(y == x);
    REQUIRE(x != z);
    REQUIRE(y != z);
    REQUIRE(z != x);
    REQUIRE(z != y);
  }
}

TEST_CASE("Symbolic Variable: Add", "[symbolic]") {
  {
    sym_t lhs("lhs");
    sym_t rhs("rhs");
    TEST_DEBUG("r = x + y");
    sym_t r = lhs + rhs;
    REQUIRE(r == lhs + rhs);
  }

  // {
  //   sym_number<int> x = 1;
  //   sym_number<int> y = 2;
  //   TEST_DEBUG("z = x + y");
  //   sym_t z = x + y;
  //   sym_number<int> a = z;
  //   REQUIRE(z == a);
  // }

  // {
  //   sym_t x("x");
  //   sym_t y = x;
  //   y = y + x;
  //   REQUIRE(y == x + x);
  // }

  // {
  //   sym_t x("x");
  //   sym_t y("y");
  //   sym_t z("z");
  //   TEST_DEBUG("a = x + y, b = x + z");
  //   sym_t a = x + y;
  //   sym_t b = x + z;
  //   REQUIRE(a == x + y);
  //   REQUIRE(a == y + x);
  //   REQUIRE(b == x + z);
  //   REQUIRE(b == z + x);
  //   REQUIRE(a != b);
  //   REQUIRE(a != x + z);
  //   REQUIRE(a != z + x);
  //   REQUIRE(b != a);
  //   REQUIRE(b != x + y);
  //   REQUIRE(b != y + x);
  // }

  // {
  //   sym_var a("a");
  //   sym_number<int> b = 1;
  //   TEST_DEBUG("r = a + b");
  //   sym_t r = a + b;
  //   REQUIRE(r == a + b);
  // }

  {
    sym_t a("a");
    sym_t b("b");
    sym_t c("c");
    sym_t d("d");
    TEST_DEBUG("r = a + b + c + d");
    sym_t r = a + b + c + d;
    REQUIRE(r == a + b + c + d);
  }
}

// TEST_CASE("Symbolic Variable: Mul", "[symbolic]") {
//   {
//     sym_t x("x");
//     sym_t y("y");
//     TEST_DEBUG("r = x * y");
//     sym_t r = x * y;
//     REQUIRE(r == x * y);
//     REQUIRE(r == y * x);
//   }
//
//   {
//     sym_t x("x");
//     sym_t y("y");
//     sym_t z("z");
//     TEST_DEBUG("r = x * y * z");
//     sym_t r = x * y * z;
//     REQUIRE(r == x * y * z);
//   }
// }
//
// TEST_CASE("Symbolic Variable: Add/Mul", "[symbolic]") {
//   {
//     sym_t x("x");
//     sym_t y("y");
//     TEST_DEBUG("r = x + y != x * y");
//     sym_t r = x + y;
//     REQUIRE(r == x + y);
//     REQUIRE(r != x * y);
//   }
//
//   {
//     sym_t x("x");
//     sym_t y("y");
//     sym_t z("z");
//     TEST_DEBUG("r = x + y * z");
//     sym_t r = x + y * z;
//     REQUIRE(r == x + y * z);
//   }
// }
//
// TEST_CASE("Symbolic Variable: Pow", "[symbolic]") {
//   {
//     sym_t x("x");
//     sym_t y("y");
//     TEST_DEBUG("r = x ^ y");
//     sym_t r = (x ^ y);
//     REQUIRE(r == (x ^ y));
//     REQUIRE(r != (y ^ x));
//   }
//
//   {
//     sym_t x("x");
//     sym_t y("y");
//     sym_t z("z");
//     TEST_DEBUG("r = x ^ y * z");
//     sym_t r = (x ^ y) * z;
//     REQUIRE(r == (x ^ y) * z);
//     REQUIRE(r == z * (x ^ y));
//     REQUIRE(r != (y ^ x) * z);
//     REQUIRE(r != z * (y ^ x));
//   }
// }
