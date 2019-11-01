#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symctrl/math/matrix/constant.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/expression.hpp>

using Controls::Math::DenseMatrix;
using Controls::Math::Vector;

using Controls::Math::ConstantMatrix;
using Controls::Math::Identity;
using Controls::Math::Ones;
using Controls::Math::Zeros;

// Uncomment this line to enable debugging.
// #define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

TEST_CASE("Constant: Assignment", "[dense]") {
  ConstantMatrix<int, 2, 2, 1> C;
  Identity<int, 2, 2> I;
  Ones<int, 2, 2> ones;
  Zeros<int, 2, 2> zeros;

  {
    REQUIRE(ConstantMatrix<int, 2, 2, 1>() == Ones<int, 2, 2>());
    REQUIRE(ConstantMatrix<int, 2, 2, 0>() == Zeros<int, 2, 2>());
  }

  {
    DenseMatrix<int> R(2, 2);
    R = C.as_dense();

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 1, 1}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I.as_dense();

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 0, 0, 1}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones.as_dense();

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 1, 1}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros.as_dense();

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 0, 0, 0}));
  }
}

TEST_CASE("Constant: Add", "[static]") {
  Identity<int, 2, 2> I;
  Ones<int, 2, 2> ones;
  Zeros<int, 2, 2> zeros;
  DenseMatrix<int> A(2, 2, {0, 1, 2, 3});

  {
    DenseMatrix<int> R(2, 2);
    R = I + I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 0, 0, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A + I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 2, 4}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I + A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 2, 4}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 + I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {3, 2, 2, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I + 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {3, 2, 2, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 + zeros;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 2, 2, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros + 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 2, 2, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A + zeros;

    REQUIRE(R == A);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros + A;

    REQUIRE(R == A);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 + ones;

    REQUIRE(R == DenseMatrix<int>(2, 2, {3, 3, 3, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones + 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {3, 3, 3, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A + ones;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 2, 3, 4}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones + A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 2, 3, 4}));
  }
}

TEST_CASE("Constant: Mul", "[static]") {
  Identity<int, 2, 2> I;
  Ones<int, 2, 2> ones;
  Zeros<int, 2, 2> zeros;
  DenseMatrix<int> A(2, 2, {0, 1, 2, 3});

  {
    DenseMatrix<int> R(2, 2);
    R = I * I;

    REQUIRE(R == I);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A * I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 1, 2, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I * A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 1, 2, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 * I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 0, 0, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I * 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 0, 0, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A * 2 * I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 2, 4, 6}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 * I * A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 2, 4, 6}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 * zeros;

    REQUIRE(R == zeros);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros * 2;

    REQUIRE(R == zeros);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A * zeros;

    REQUIRE(R == zeros);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros * A;

    REQUIRE(R == zeros);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 * ones;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 2, 2, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones * 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 2, 2, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A * ones;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 5, 5}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones * A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 4, 2, 4}));
  }
}
