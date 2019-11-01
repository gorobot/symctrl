#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

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

TEST_CASE("Symbolic Number: Assignment", "[symbolic]") {
  {
    sym_number<double> a = 1;
    REQUIRE(a == 1);
    REQUIRE(a == sym_number<double>(1));
    REQUIRE(a == a);
  }

  {
    sym_number<double> a(1);
    sym_number<double> b(1);
    sym_number<double> c(2);
    REQUIRE(a == b);
    REQUIRE(b == a);
    REQUIRE(a != c);
    REQUIRE(b != c);
    REQUIRE(c != a);
    REQUIRE(c != b);
  }

  {
    sym_number<double> a = 1;
    sym_number<double> b = 1;
    sym_number<double> c = 2;
    REQUIRE(a == b);
    REQUIRE(b == a);
    REQUIRE(a != c);
    REQUIRE(b != c);
    REQUIRE(c != a);
    REQUIRE(c != b);
  }

  {
    sym_number<double> a = 1;
    sym_number<double> b = a;
    REQUIRE(a == 1);
    REQUIRE(b == 1);
    a = 2;
    REQUIRE(a == 2);
    REQUIRE(b == 1);
  }
}

TEST_CASE("Symbolic Number: Add", "[symbolic]") {
  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    TEST_DEBUG("r = a + b")
    sym_number<double> r = a + b;
    REQUIRE(r == 3);
  }

  {
    sym_number<double> a = 1;
    TEST_DEBUG("r = diff(a)")
    sym_number<double> r = diff(a);
    REQUIRE(r == 0);
  }

  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    TEST_DEBUG("r = a + b")
    sym_number<double> r = a + b;
    REQUIRE(r == 3);
  }

  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    sym_number<double> c = 3;
    TEST_DEBUG("r = a + b + c");
    sym_number<double> r = a + b + c;
    REQUIRE(r == 6);
  }

  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    REQUIRE(a == 1);
    REQUIRE(b == 2);
    TEST_DEBUG("a = a + b");
    a = a + b;
    REQUIRE(a == 3);
    REQUIRE(b == 2);
  }

  // {
  //   sym_number<double> a = 1;
  //   sym_number<double> b = a;
  //   // sym_number<double> c = b + 1;
  //   // REQUIRE(c == 2);
  // }
  //
  // {
  //   sym_number<double> a = 1;
  //   // a += 1;
  //   // REQUIRE(a == 2);
  // }
}

TEST_CASE("Symbolic Number: Mul", "[symbolic]") {
  {
    TEST_DEBUG("r = 1 * 2");
    sym_number<double> r = 1 * 2;
    REQUIRE(r == 2);
    REQUIRE(r == 1 * 2);
  }

  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    TEST_DEBUG("r = a * b");
    sym_number<double> r = a * b;
    REQUIRE(r == 2);
  }

  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    sym_number<double> c = 3;
    TEST_DEBUG("r = a * b * c");
    sym_number<double> r = a * b * c;
    REQUIRE(r == 6);
  }
}

TEST_CASE("Symbolic Number: Add/Mul", "[symbolic]") {
  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    TEST_DEBUG("r = a + b != a * b");
    sym_number<double> r = a + b;
    REQUIRE(r == 3);
    REQUIRE(r != 2);
  }

  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    sym_number<double> c = 3;
    TEST_DEBUG("r = a + b * c");
    sym_number<double> r = a + b * c;
    REQUIRE(r == a + b * c);
    REQUIRE(r == a + c * b);
    REQUIRE(r == b * c + a);
    REQUIRE(r == c * b + a);
  }
}

TEST_CASE("Symbolic Number: Pow", "[symbolic]") {
  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    TEST_DEBUG("r = a ^ b");
    sym_number<double> r = (a ^ b);
    REQUIRE(r == (a ^ b));
    REQUIRE(r != (b ^ a));
  }

  {
    sym_number<double> a = 1;
    sym_number<double> b = 2;
    sym_number<double> c = 3;
    TEST_DEBUG("r = a ^ b * c");
    sym_number<double> r = (a ^ b) * c;
    REQUIRE(r == (a ^ b) * c);
    REQUIRE(r == c * (a ^ b));
    REQUIRE(r != (b ^ a) * c);
    REQUIRE(r != c * (b ^ a));
  }
}
