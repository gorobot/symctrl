#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symctrl/math/matrix.hpp>
#include <symctrl/math/symbolic.hpp>

using Controls::Math::DenseMatrix;
using Controls::Math::Vector;

using Controls::Math::sym_t;
using Controls::Math::sym_number;
using Controls::Math::sym_var;

// Uncomment this line to enable debugging.
#define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

TEST_CASE("Symbolic Matrix: Assignment", "[symbolic]") {
  {
    DenseMatrix<sym_t> A(2, 2, {0, 1, 2, 3});
    REQUIRE(A[0] == 0);
    REQUIRE(A[1] == 1);
    REQUIRE(A[2] == 2);
    REQUIRE(A[3] == 3);
  }

  {
    sym_t a(1);
    sym_t b(1);
    sym_t c(2);
    REQUIRE(a == b);
    REQUIRE(b == a);
    REQUIRE(a != c);
    REQUIRE(b != c);
    REQUIRE(c != a);
    REQUIRE(c != b);
  }

  {
    sym_t a = 1;
    sym_t b = 1;
    sym_t c = 2;
    REQUIRE(a == b);
    REQUIRE(b == a);
    REQUIRE(a != c);
    REQUIRE(b != c);
    REQUIRE(c != a);
    REQUIRE(c != b);
  }
}

TEST_CASE("Symbolic Matrix: Add", "[symbolic]") {
  DenseMatrix<sym_t> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<sym_t> B(2, 2, {2, 2, 2, 2});

  {
    DenseMatrix<sym_t> R(2, 2);
    TEST_DEBUG("R = A + B");
    R = A + B;
    REQUIRE(R[0] == 3);
    REQUIRE(R[1] == 3);
    REQUIRE(R[2] == 3);
    REQUIRE(R[3] == 3);
  }

  {
    sym_t a = 1;
    sym_t b = 2;
    TEST_DEBUG("r = a + b");
    sym_t r = a + b;
    REQUIRE(r == a + b);
    REQUIRE(r == b + a);
  }

  {
    sym_t a = 1;
    sym_t b = 2;
    sym_t c = 3;
    TEST_DEBUG("r = a + b + c");
    sym_t r = a + b + c;
    REQUIRE(r == a + b + c);
    REQUIRE(r == a + c + b);
    REQUIRE(r == b + a + c);
    REQUIRE(r == b + c + a);
    REQUIRE(r == c + a + b);
    REQUIRE(r == c + b + a);
  }
}

TEST_CASE("Symbolic Matrix: Mul", "[symbolic]") {
  {
    TEST_DEBUG("r = 1 * 2");
    sym_t r = 1 * 2;
    REQUIRE(r == 2);
    REQUIRE(r == 1 * 2);
  }

  {
    sym_t a = 1;
    sym_t b = 2;
    TEST_DEBUG("r = a * b");
    sym_t r = a * b;
    REQUIRE(r == a * b);
    REQUIRE(r == b * a);
  }

  {
    sym_t a = 1;
    sym_t b = 2;
    sym_t c = 3;
    TEST_DEBUG("r = a * b * c");
    sym_t r = a * b * c;
    REQUIRE(r == a * b * c);
    REQUIRE(r == a * c * b);
    REQUIRE(r == b * a * c);
    REQUIRE(r == b * c * a);
    REQUIRE(r == c * a * b);
    REQUIRE(r == c * b * a);
  }
}

TEST_CASE("Symbolic Matrix: Add/Mul", "[symbolic]") {
  {
    sym_t a = 1;
    sym_t b = 2;
    TEST_DEBUG("r = a + b != a * b");
    sym_t r = a + b;
    REQUIRE(r == a + b);
    REQUIRE(r != a * b);
  }

  {
    sym_t a = 1;
    sym_t b = 2;
    sym_t c = 3;
    TEST_DEBUG("r = a + b * c");
    sym_t r = a + b * c;
    REQUIRE(r == a + b * c);
    REQUIRE(r == a + c * b);
    REQUIRE(r == b * c + a);
    REQUIRE(r == c * b + a);
  }
}
