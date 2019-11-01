#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/expression.hpp>
#include <symctrl/math/matrix/operations.hpp>
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

TEST_CASE("Matrix Operations: Type Conversion", "[operations]") {
  Vector<double> a({1, 2});
  Vector<double> b({1, 2});

  {
    SYMCTRL_DEBUG("double = transpose(a) * b");
    double result = transpose(a) * b;
    REQUIRE(result == 5);
  }
}

// TEST_CASE("Matrix Operations: Jacobian", "[operations]") {
//   RCP<const Symbol> x = symbol("x");
//   RCP<const Symbol> y = symbol("y");
//
//   SymbolicVector a({x, mul(x, y)});
//   SymbolicVector b({x, y});
//   SymbolicDense C(2, 2);
//   C = integer(1);
//
//   {
//     REQUIRE(a != b);
//   }
//
//   {
//     SymbolicDense R(2, 2);
//     TEST_DEBUG("R = jacobian(a, b)");
//     R = jacobian(a, b);
//     REQUIRE(eq(*R(0, 0), *integer(1)));
//     REQUIRE(eq(*R(0, 1), *integer(0)));
//     REQUIRE(eq(*R(1, 0), *y));
//     REQUIRE(eq(*R(1, 1), *x));
//   }
//
//   {
//     SymbolicDense R(2, 2);
//     TEST_DEBUG("R = C + jacobian(a, b)");
//     R = C + jacobian(a, b);
//     REQUIRE(eq(*R(0, 0), *integer(2)));
//     REQUIRE(eq(*R(0, 1), *integer(1)));
//     REQUIRE(eq(*R(1, 0), *add(y, integer(1))));
//     REQUIRE(eq(*R(1, 1), *add(x, integer(1))));
//   }
//
//   {
//     SymbolicDense R(2, 2);
//     TEST_DEBUG("R = C * jacobian(a, b)");
//     R = C * jacobian(a, b);
//     REQUIRE(eq(*R(0, 0), *add(y, integer(1))));
//     REQUIRE(eq(*R(0, 1), *x));
//     REQUIRE(eq(*R(1, 0), *add(y, integer(1))));
//     REQUIRE(eq(*R(1, 1), *x));
//   }
//
//   {
//     SymbolicDense R(2, 2);
//     TEST_DEBUG("R = transpose(jacobian(a, b))");
//     R = transpose(jacobian(a, b));
//     REQUIRE(eq(*R(0, 0), *integer(1)));
//     REQUIRE(eq(*R(0, 1), *y));
//     REQUIRE(eq(*R(1, 0), *integer(0)));
//     REQUIRE(eq(*R(1, 1), *x));
//   }
//
//   {
//     Vector<int> c({1, 1});
//     Vector<int> d({1, 1});
//     DenseMatrix<int> S(2, 2);
//
//     // Fails!
//     // S = jacobian(a, b);
//     // S = jacobian(c, d);
//     // R = jacobian(c, d);
//   }
// }

TEST_CASE("Matrix Operations: Norm", "[operations]") {
  Vector<int> v({1, -2, 3});

  {
    auto result = Controls::Math::norm(v, 1);
    REQUIRE(::fabs(result - 6) < 1e-3);
  }

  {
    auto result = Controls::Math::norm(v, 2);
    REQUIRE(::fabs(result - 3.7417) < 1e-3);
  }

  {
    auto result = Controls::Math::norm(v, 3);
    REQUIRE(::fabs(result - 3.3019) < 1e-3);
  }

  {
    auto result = Controls::Math::infinity_norm(v);
    REQUIRE(result == 3);
  }
}

TEST_CASE("Matrix Operations: QR Decomposition", "[operations]") {
  {
    SYMCTRL_DEBUG("QR Decomposition");
    DenseMatrix<double> A(3, 3, {12, -51,   4,
                                  6, 167, -68,
                                 -4,  24, -41});

    //
    DenseMatrix<double> Q(3, 3);
    DenseMatrix<double> R(3, 3);

    Controls::Math::qr(A, Q, R);

    REQUIRE(::fabs(Q[0] - 0.8571) < 1e-3);
    REQUIRE(::fabs(Q[1] - -0.3943) < 1e-3);
    REQUIRE(::fabs(Q[2] - -0.3314) < 1e-3);
    REQUIRE(::fabs(Q[3] - 0.4286) < 1e-3);
    REQUIRE(::fabs(Q[4] - 0.9029) < 1e-3);
    REQUIRE(::fabs(Q[5] - 0.0343) < 1e-3);
    REQUIRE(::fabs(Q[6] - -0.2857) < 1e-3);
    REQUIRE(::fabs(Q[7] - 0.1714) < 1e-3);
    REQUIRE(::fabs(Q[8] - -0.9429) < 1e-3);

    REQUIRE(::fabs(R[0] - 14.0000) < 1e-3);
    REQUIRE(::fabs(R[1] - 21.0000) < 1e-3);
    REQUIRE(::fabs(R[2] - -14.0000) < 1e-3);
    REQUIRE(::fabs(R[3] - 0) < 1e-3);
    REQUIRE(::fabs(R[4] - 175.0000) < 1e-3);
    REQUIRE(::fabs(R[5] - -70.0000) < 1e-3);
    REQUIRE(::fabs(R[6] - 0) < 1e-3);
    REQUIRE(::fabs(R[7] - 0) < 1e-3);
    REQUIRE(::fabs(R[8] - 35.0000) < 1e-3);
  }
}

TEST_CASE("Matrix Operations: Trace", "[operations]") {
  {
    DenseMatrix<int> A(2, 2, {0, 1, 2, 3});
    REQUIRE(Controls::Math::trace(A) == 3);
  }

  {
    DenseMatrix<int> A(2, 2, {5, 1, 2, 3});
    REQUIRE(Controls::Math::trace(A) == 8);
  }
}
