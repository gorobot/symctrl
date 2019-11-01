#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symctrl/math/matrix/block.hpp>
#include <symctrl/math/matrix/constant.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/expression.hpp>

using Controls::Math::BlockMatrix;
using Controls::Math::DenseMatrix;
using Controls::Math::Vector;
using Controls::Math::Zeros;

// Uncomment this line to enable debugging.
// #define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

TEST_CASE("Block: Assignment", "[block]") {
  {
    DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
    DenseMatrix<int> B(2, 2, {2, 2, 2, 2});
    DenseMatrix<int> C(2, 2, {3, 3, 3, 3});
    DenseMatrix<int> D(2, 2, {4, 4, 4, 4});

    BlockMatrix<int> P(2, 2, {A, B, C, D});

    BlockMatrix<int> R(2, 2);
    R = P;

    REQUIRE(R[0] == A);
    REQUIRE(R[1] == B);
    REQUIRE(R[2] == C);
    REQUIRE(R[3] == D);
  }

  {
    DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
    DenseMatrix<int> B(2, 2, {0, 1, 2, 3});
    BlockMatrix<int> R(1, 1, {A});

    R[0][0] = 0;
    R[0][1] = 1;
    R[0][2] = 2;
    R[0][3] = 3;
    REQUIRE(R[0][0] == 0);
    REQUIRE(R[0][1] == 1);
    REQUIRE(R[0][2] == 2);
    REQUIRE(R[0][3] == 3);

    REQUIRE(R[0] == B);
  }

  {
    DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
    DenseMatrix<int> B(2, 2, {2, 2, 2, 2});
    DenseMatrix<int> C(2, 2, {3, 3, 3, 3});
    DenseMatrix<int> D(2, 2, {4, 4, 4, 4});

    BlockMatrix<int> P(2, 2, {A, B, C, D});

    BlockMatrix<int> R(2, 2);
    R = P;
    R[0] = 2;

    REQUIRE(R[0] != A);
    REQUIRE(R[0] == B);
  }

  {
    DenseMatrix<int> A(2, 2, {0, 1, 2, 3});

    BlockMatrix<int> V(2, 2, {A, A, A, A});

    DenseMatrix<int> R(4, 4);
    R = V.as_dense();

    REQUIRE(R == DenseMatrix<int>(4, 4, {0, 1, 0, 1,
                                         2, 3, 2, 3,
                                         0, 1, 0, 1,
                                         2, 3, 2, 3}));
  }

  {
    DenseMatrix<int> A(2, 3, {0, 1, 2, 3, 4, 5});

    BlockMatrix<int> V(2, 2, {A, A, A, A});

    DenseMatrix<int> R(4, 6);
    R = V.as_dense();

    REQUIRE(R == DenseMatrix<int>(4, 6, {0, 1, 2, 0, 1, 2,
                                         3, 4, 5, 3, 4, 5,
                                         0, 1, 2, 0, 1, 2,
                                         3, 4, 5, 3, 4, 5}));
  }

  {
    DenseMatrix<int> A(2, 3, {0, 1, 2, 3, 4, 5});
    DenseMatrix<int> B(2, 2, {0, 1, 2, 3});
    DenseMatrix<int> C(3, 3, {0, 1, 2, 3, 4, 5, 6, 7, 8});
    DenseMatrix<int> D(3, 2, {0, 1, 2, 3, 4, 5});

    BlockMatrix<int> V(2, 2, {A, B, C, D});

    DenseMatrix<int> R(5, 5);
    R = V.as_dense();

    REQUIRE(R == DenseMatrix<int>(5, 5, {0, 1, 2, 0, 1,
                                         3, 4, 5, 2, 3,
                                         0, 1, 2, 0, 1,
                                         3, 4, 5, 2, 3,
                                         6, 7, 8, 4, 5}));
  }

  {
    DenseMatrix<int> A(2, 3, {0, 1, 2, 3, 4, 5});
    DenseMatrix<int> B(2, 2, {0, 1, 2, 3});
    DenseMatrix<int> C(2, 1, {0, 1});
    DenseMatrix<int> D(3, 3, {0, 1, 2, 3, 4, 5, 6, 7, 8});
    DenseMatrix<int> E(3, 2, {0, 1, 2, 3, 4, 5});
    DenseMatrix<int> F(3, 1, {0, 1, 2});

    BlockMatrix<int> V(2, 3, {A, B, C, D, E, F});

    DenseMatrix<int> R(5, 6);
    R = V.as_dense();

    REQUIRE(R == DenseMatrix<int>(5, 6, {0, 1, 2, 0, 1, 0,
                                         3, 4, 5, 2, 3, 1,
                                         0, 1, 2, 0, 1, 0,
                                         3, 4, 5, 2, 3, 1,
                                         6, 7, 8, 4, 5, 2}));
  }
}

TEST_CASE("Block: Add", "[block]") {
  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});
  DenseMatrix<int> C(2, 2, {3, 3, 3, 3});
  DenseMatrix<int> D(2, 2, {4, 4, 4, 4});
  DenseMatrix<int> E(2, 2, {5, 5, 5, 5});
  DenseMatrix<int> F(2, 2, {6, 6, 6, 6});
  DenseMatrix<int> G(2, 2, {7, 7, 7, 7});
  DenseMatrix<int> H(2, 2, {8, 8, 8, 8});

  BlockMatrix<int> P(2, 2, {A, B, C, D});
  BlockMatrix<int> Q(2, 2, {E, F, G, H});

  REQUIRE(P[0] == A);
  REQUIRE(P[1] == B);
  REQUIRE(P[2] == C);
  REQUIRE(P[3] == D);

  {
    BlockMatrix<int> R(2, 2);
    TEST_DEBUG("R = P + Q");
    R = P + Q;

    REQUIRE(R[0] == DenseMatrix<int>(2, 2, {6, 6, 6, 6}));
    REQUIRE(R[1] == DenseMatrix<int>(2, 2, {8, 8, 8, 8}));
    REQUIRE(R[2] == DenseMatrix<int>(2, 2, {10, 10, 10, 10}));
    REQUIRE(R[3] == DenseMatrix<int>(2, 2, {12, 12, 12, 12}));
  }

  {
    BlockMatrix<int> R(2, 2);
    TEST_DEBUG("R = 5 + P");
    R = 5 + P;

    REQUIRE(R[0] == DenseMatrix<int>(2, 2, {6, 6, 6, 6}));
    REQUIRE(R[1] == DenseMatrix<int>(2, 2, {7, 7, 7, 7}));
    REQUIRE(R[2] == DenseMatrix<int>(2, 2, {8, 8, 8, 8}));
    REQUIRE(R[3] == DenseMatrix<int>(2, 2, {9, 9, 9, 9}));
  }

  {
    BlockMatrix<int> R(2, 2);
    TEST_DEBUG("R = P + 5");
    R = 5 + P;

    REQUIRE(R[0] == DenseMatrix<int>(2, 2, {6, 6, 6, 6}));
    REQUIRE(R[1] == DenseMatrix<int>(2, 2, {7, 7, 7, 7}));
    REQUIRE(R[2] == DenseMatrix<int>(2, 2, {8, 8, 8, 8}));
    REQUIRE(R[3] == DenseMatrix<int>(2, 2, {9, 9, 9, 9}));
  }
}

TEST_CASE("Block: Hamiltonian", "[block]") {
  DenseMatrix<double> A(2, 2, {0, 1, 2, 3});
  DenseMatrix<double> Q(2, 2, {1, 0, 0, 1});
  Zeros<double, 2, 2> zero;
  BlockMatrix<double> H(2, 2, {A, zero, -Q, -transpose(A)});
  //
  // REQUIRE(Controls::Math::is_hamiltonian(H.as_dense()));
}
