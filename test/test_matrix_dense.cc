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

TEST_CASE("Dense: Assignment", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 2, 3, 4});
  DenseMatrix<int> C(2, 2);

  Vector<int> v1({1, 2});
  REQUIRE(A.row(0) == v1);

  Vector<int> v2({3, 4});
  REQUIRE(A.row(1) == v2);

  Vector<int> v3({1, 3});
  REQUIRE(A.col(0) == v3);

  Vector<int> v4({2, 4});
  REQUIRE(A.col(1) == v4);

  // Assignment
  C = 5;

  REQUIRE(C(0, 0) == 5);
  REQUIRE(C(0, 1) == 5);
  REQUIRE(C(1, 0) == 5);
  REQUIRE(C(1, 1) == 5);

  C = A;

  REQUIRE(C == A);

  C(0, 0) = 2;

  REQUIRE(C != A);

  {
    DenseMatrix<int> M(2, 2, {1, 2, 3, 4});
    M.swap_row(0, 1);
    REQUIRE(M == DenseMatrix<int>(2, 2, {3, 4, 1, 2}));
  }

  {
    DenseMatrix<int> M(2, 2, {1, 2, 3, 4});
    M.swap_col(0, 1);
    REQUIRE(M == DenseMatrix<int>(2, 2, {2, 1, 4, 3}));
  }
}

TEST_CASE("Dense: Add", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + B");
    R = A + B;
    REQUIRE(R[0] == 3);
    REQUIRE(R[1] == 3);
    REQUIRE(R[2] == 3);
    REQUIRE(R[3] == 3);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = 5 + A");
    R = 5 + A;
    REQUIRE(R[0] == 6);
    REQUIRE(R[1] == 6);
    REQUIRE(R[2] == 6);
    REQUIRE(R[3] == 6);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + 5");
    R = A + 5;
    REQUIRE(R[0] == 6);
    REQUIRE(R[1] == 6);
    REQUIRE(R[2] == 6);
    REQUIRE(R[3] == 6);
  }
}

TEST_CASE("Dense: Mul", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * B");
    R = A * B;
    REQUIRE(R[0] == 4);
    REQUIRE(R[1] == 4);
    REQUIRE(R[2] == 4);
    REQUIRE(R[3] == 4);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = 5 * A");
    R = 5 * A;
    REQUIRE(R[0] == 5);
    REQUIRE(R[1] == 5);
    REQUIRE(R[2] == 5);
    REQUIRE(R[3] == 5);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * 5");
    R = A * 5;
    REQUIRE(R[0] == 5);
    REQUIRE(R[1] == 5);
    REQUIRE(R[2] == 5);
    REQUIRE(R[3] == 5);
  }
}

TEST_CASE("Dense: Add/Mul", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});
  DenseMatrix<int> C(2, 2, {3, 3, 3, 3});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + (B + C)");
    R = A + (B + C);
    REQUIRE(R(0, 0) == 6);
    REQUIRE(R(0, 1) == 6);
    REQUIRE(R(1, 0) == 6);
    REQUIRE(R(1, 1) == 6);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * (B + C)");
    R = A * (B + C);
    REQUIRE(R(0, 0) == 10);
    REQUIRE(R(0, 1) == 10);
    REQUIRE(R(1, 0) == 10);
    REQUIRE(R(1, 1) == 10);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + (B * C)");
    R = A + (B * C);
    REQUIRE(R(0, 0) == 13);
    REQUIRE(R(0, 1) == 13);
    REQUIRE(R(1, 0) == 13);
    REQUIRE(R(1, 1) == 13);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * (B * C)");
    R = A * (B * C);
    REQUIRE(R(0, 0) == 24);
    REQUIRE(R(0, 1) == 24);
    REQUIRE(R(1, 0) == 24);
    REQUIRE(R(1, 1) == 24);
  }
}

TEST_CASE("Dense: Sub", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = -A");
    R = -A;
    REQUIRE(R[0] == -1);
    REQUIRE(R[1] == -1);
    REQUIRE(R[2] == -1);
    REQUIRE(R[3] == -1);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A - B");
    R = A - B;
    REQUIRE(R[0] == -1);
    REQUIRE(R[1] == -1);
    REQUIRE(R[2] == -1);
    REQUIRE(R[3] == -1);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = 5 - A");
    R = 5 - A;
    REQUIRE(R[0] == 4);
    REQUIRE(R[1] == 4);
    REQUIRE(R[2] == 4);
    REQUIRE(R[3] == 4);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A - 5");
    R = A - 5;
    REQUIRE(R[0] == -4);
    REQUIRE(R[1] == -4);
    REQUIRE(R[2] == -4);
    REQUIRE(R[3] == -4);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A - -B");
    R = A - -B;
    REQUIRE(R[0] == 3);
    REQUIRE(R[1] == 3);
    REQUIRE(R[2] == 3);
    REQUIRE(R[3] == 3);
  }
}

TEST_CASE("Dense: transpose", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 2, 3, 1});
  DenseMatrix<int> B(2, 2, {1, 3, 2, 1});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A)");
    R = transpose(A);
    REQUIRE(R(0, 0) == 1);
    REQUIRE(R(0, 1) == 3);
    REQUIRE(R(1, 0) == 2);
    REQUIRE(R(1, 1) == 1);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(transpose(A))");
    R = transpose(transpose(A));
    REQUIRE(R(0, 0) == 1);
    REQUIRE(R(0, 1) == 2);
    REQUIRE(R(1, 0) == 3);
    REQUIRE(R(1, 1) == 1);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A) + transpose(B)");
    R = transpose(A) + transpose(B);
    REQUIRE(R(0, 0) == 2);
    REQUIRE(R(0, 1) == 5);
    REQUIRE(R(1, 0) == 5);
    REQUIRE(R(1, 1) == 2);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A + B)");
    R = transpose(A + B);
    REQUIRE(R(0, 0) == 2);
    REQUIRE(R(0, 1) == 5);
    REQUIRE(R(1, 0) == 5);
    REQUIRE(R(1, 1) == 2);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A) * transpose(B)");
    R = transpose(A) * transpose(B);
    REQUIRE(R(0, 0) == 10);
    REQUIRE(R(0, 1) == 5);
    REQUIRE(R(1, 0) == 5);
    REQUIRE(R(1, 1) == 5);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A * B)");
    R = transpose(A * B);
    REQUIRE(R(0, 0) == 5);
    REQUIRE(R(0, 1) == 5);
    REQUIRE(R(1, 0) == 5);
    REQUIRE(R(1, 1) == 10);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + transpose(B)");
    R = A + transpose(B);
    REQUIRE(R(0, 0) == 2);
    REQUIRE(R(0, 1) == 4);
    REQUIRE(R(1, 0) == 6);
    REQUIRE(R(1, 1) == 2);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A) + B");
    R = transpose(A) + B;
    REQUIRE(R(0, 0) == 2);
    REQUIRE(R(0, 1) == 6);
    REQUIRE(R(1, 0) == 4);
    REQUIRE(R(1, 1) == 2);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * transpose(B)");
    R = A * transpose(B);
    REQUIRE(R(0, 0) == 7);
    REQUIRE(R(0, 1) == 4);
    REQUIRE(R(1, 0) == 6);
    REQUIRE(R(1, 1) == 7);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A) * B");
    R = transpose(A) * B;
    REQUIRE(R(0, 0) == 7);
    REQUIRE(R(0, 1) == 6);
    REQUIRE(R(1, 0) == 4);
    REQUIRE(R(1, 1) == 7);
  }
}

TEST_CASE("Dense: DenseMatrix checks", "[dense]") {
  {
    DenseMatrix<int> A(2, 2, {1, 2, 2, 1});
    DenseMatrix<int> B(2, 2, {1, 2, 3, 1});

    REQUIRE(is_symmetric(A));
    REQUIRE(!is_symmetric(B));
  }

  {
    DenseMatrix<int> A(2, 2, {1, 1, 0, 1});
    DenseMatrix<int> B(2, 2, {1, 0, 1, 1});

    REQUIRE(is_upper(A));
    REQUIRE(!is_upper(B));
  }

  {
    DenseMatrix<int> A(2, 2, {1, 0, 1, 1});
    DenseMatrix<int> B(2, 2, {1, 1, 0, 1});

    REQUIRE(is_lower(A));
    REQUIRE(!is_lower(B));
  }
}
