#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symctrl/math/matrix.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/expression.hpp>
#include <symctrl/math/matrix/vector.hpp>

using Controls::Math::DenseMatrix;
using Controls::Math::Vector;

// Uncomment this line to enable debugging.
// #define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

TEST_CASE("Vector: Assignment", "[vector]") {
  Vector<int> a({1, 1});
  Vector<int> r(2);

  // Assignment
  r = 5;

  REQUIRE(r[0] == 5);
  REQUIRE(r[1] == 5);

  r = a;

  REQUIRE(r == a);

  r[0] = 2;

  REQUIRE(r != a);
}

TEST_CASE("Vector: Add", "[vector]") {
  Vector<int> a({1, 1});
  Vector<int> b({2, 2});

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a + b");
    r = a + b;
    REQUIRE(r[0] == 3);
    REQUIRE(r[1] == 3);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = 5 + a");
    r = 5 + a;
    REQUIRE(r[0] == 6);
    REQUIRE(r[1] == 6);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a + 5");
    r = a + 5;
    REQUIRE(r[0] == 6);
    REQUIRE(r[1] == 6);
  }
}

TEST_CASE("Vector: Mul", "[vector]") {
  Vector<int> a({1, 1});
  Vector<int> b({2, 2});

  // {
  //   Vector<int> r(2);
  //   TEST_DEBUG("r = a * b");
  //   r = a * b;
  //   REQUIRE(r[0] = 3);
  //   REQUIRE(r[1] = 3);
  // }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = 5 * a");
    r = 5 * a;
    REQUIRE(r[0] == 5);
    REQUIRE(r[1] == 5);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a * 5");
    r = a * 5;
    REQUIRE(r[0] == 5);
    REQUIRE(r[1] == 5);
  }

  {
    DenseMatrix<int> A(2, 2, {0, 1, 2, 3});
    Vector<int> x({1, 2});
    Vector<int> r(2);
    TEST_DEBUG("r = A * x");
    r = A * x;
    REQUIRE(r[0] == 2);
    REQUIRE(r[1] == 8);
  }

  // {
  //   SymbolicDense A(2, 2, {integer(0), integer(1), integer(2), integer(3)});
  //   SymbolicVector x({integer(1), integer(2)});
  //   SymbolicVector r(2);
  //   TEST_DEBUG("r = A * x");
  //   r = A * x;
  //   REQUIRE(eq(*r[0], *integer(2)));
  //   REQUIRE(eq(*r[1], *integer(8)));
  // }
}

TEST_CASE("Vector: Add/Mul", "[vector]") {
  Vector<int> a({1, 1});
  Vector<int> b({2, 2});
  Vector<int> c({3, 3});

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a + (b + c)");
    r = a + (b + c);
    REQUIRE(r[0] == 6);
    REQUIRE(r[1] == 6);
  }

  // {
  //   Vector<int> r(2);
  //   TEST_DEBUG("r = a * (b + c)");
  //   r = a * (b + c);
  //   REQUIRE(r[0] == 6);
  //   REQUIRE(r[1] == 6);
  // }

  // {
  //   Vector<int> r(2);
  //   TEST_DEBUG("r = a + (b * c)");
  //   r = a + (b * c);
  //   REQUIRE(r[0] == 6);
  //   REQUIRE(r[1] == 6);
  // }

  // {
  //   Vector<int> r(2);
  //   TEST_DEBUG("r = a * (b * c)");
  //   r = a * (b * c);
  //   REQUIRE(r[0] == 6);
  //   REQUIRE(r[1] == 6);
  // }
}

TEST_CASE("Vector: Sub", "[vector]") {
  Vector<int> a({1, 2});
  Vector<int> b({2, 3});

  {
    Vector<int> r(2);
    TEST_DEBUG("r = -a");
    r = -a;
    REQUIRE(r[0] == -1);
    REQUIRE(r[1] == -2);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a - b");
    r = a - b;
    REQUIRE(r[0] == -1);
    REQUIRE(r[1] == -1);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = 5 - a");
    r = 5 - a;
    REQUIRE(r[0] == 4);
    REQUIRE(r[1] == 3);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a - 5");
    r = a - 5;
    REQUIRE(r[0] == -4);
    REQUIRE(r[1] == -3);
  }
}

TEST_CASE("Vector: transpose", "[vector]") {
  Vector<int> a({1, 2});
  Vector<int> b({2, 3});

  {
    Vector<int> r(2);
    TEST_DEBUG("r = transpose(a)");
    r = transpose(a);
    REQUIRE(r != a);
    REQUIRE(r.nrows() == 1);
    REQUIRE(r.ncols() == 2);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = transpose(transpose(a))");
    r = transpose(transpose(a));
    REQUIRE(r == a);
    REQUIRE(r.nrows() == 2);
    REQUIRE(r.ncols() == 1);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = transpose(a) + transpose(b)");
    r = transpose(a) + transpose(b);
    REQUIRE(r[0] == 3);
    REQUIRE(r[1] == 5);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = transpose(a + b)");
    r = transpose(a + b);
    REQUIRE(r[0] == 3);
    REQUIRE(r[1] == 5);
  }
}

// TEST_CASE("Vector: Mixed operations", "[vector]") {
//   DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
//   Vector<int> x({1, 1});
//
//   {
//     Vector<int> r(2);
//
//     r = A * x;
//
//     REQUIRE(r.nrows() == 2);
//     REQUIRE(r.ncols() == 1);
//
//     REQUIRE(r[0] == 2);
//     REQUIRE(r[1] == 2);
//   }
//
//   {
//     DenseMatrix<int> R(2, 1);
//
//     R = A * x;
//
//     REQUIRE(R.nrows() == 2);
//     REQUIRE(R.ncols() == 1);
//
//     REQUIRE(R[0] == 2);
//     REQUIRE(R[1] == 2);
//   }
//
//   {
//     Vector<int> r(2);
//
//     r = transpose(x) * A;
//
//     REQUIRE(r.nrows() == 1);
//     REQUIRE(r.ncols() == 2);
//
//     REQUIRE(r[0] == 2);
//     REQUIRE(r[1] == 2);
//   }
//
//   {
//     DenseMatrix<int> R(1, 2);
//
//     R = transpose(x) * A;
//
//     REQUIRE(R.nrows() == 1);
//     REQUIRE(R.ncols() == 2);
//
//     REQUIRE(R[0] == 2);
//     REQUIRE(R[1] == 2);
//   }
//
//   {
//     DenseMatrix<int> R(2, 2);
//
//     R = 2 * A;
//
//     REQUIRE(R[0] == 2);
//     REQUIRE(R[1] == 2);
//     REQUIRE(R[2] == 2);
//     REQUIRE(R[3] == 2);
//   }
//
//   {
//     DenseMatrix<int> R(2, 2);
//
//     R = A * 2;
//
//     REQUIRE(R[0] == 2);
//     REQUIRE(R[1] == 2);
//     REQUIRE(R[2] == 2);
//     REQUIRE(R[3] == 2);
//   }
//
//   {
//     SymbolicDense C(2, 2);
//     SymbolicDense D(2, 2, {integer(1), integer(0), integer(0), integer(1)});
//     RCP<const Basic> x = symbol("x");
//
//     C = x * D;
//
//     REQUIRE(eq(*C[0], *x));
//     REQUIRE(eq(*C[1], *integer(0)));
//     REQUIRE(eq(*C[2], *integer(0)));
//     REQUIRE(eq(*C[3], *x));
//   }
//
// }
