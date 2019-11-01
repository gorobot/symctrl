#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <chrono>

#include <symctrl/math/matrix.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/expression.hpp>
#include <symctrl/math/matrix/static.hpp>
#include <symctrl/math/matrix/vector.hpp>

using Controls::Math::DenseMatrix;
using Controls::Math::Vector;

using Controls::Math::StaticDense;
using Controls::Math::StaticVector;

using Controls::Math::is_lower;
using Controls::Math::is_square;
using Controls::Math::is_upper;

// Uncomment this line to enable debugging.
// #define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

TEST_CASE("Static: Assignment", "[static]") {
  {
    StaticDense<int, 2, 2> A({0, 1, 2, 3});
    REQUIRE(A == DenseMatrix<int>(2, 2, {0, 1, 2, 3}));
  }

  {
    DenseMatrix<int> A(2, 2, {0, 1, 2, 3});
    REQUIRE(A == StaticDense<int, 2, 2>({0, 1, 2, 3}));
  }

  {
    StaticVector<int, 2, 1> A({1, 2});
    REQUIRE(A == Vector<int>({1, 2}));
  }

  {
    Vector<int> A({1, 2});
    REQUIRE(A == StaticVector<int, 2, 1>({1, 2}));
  }

  {
    DenseMatrix<int> A(2, 2, {0, 1, 2, 3});
    StaticDense<int, 2, 2> R = A;

    REQUIRE(R == A);
  }

  {
    StaticDense<int, 2, 2> A({0, 1, 2, 3});
    DenseMatrix<int> R = A;

    REQUIRE(R == A);
  }

  {
    Vector<int> A({1, 2});
    StaticVector<int, 2, 1> R = A;

    REQUIRE(R == A);
  }

  {
    StaticVector<int, 2, 1> A({1, 2});
    Vector<int> R = A;

    REQUIRE(R == A);
  }
}

TEST_CASE("Static: Add", "[static]") {
  StaticDense<int, 2, 2> A({1, 1, 1, 1});
  StaticDense<int, 2, 2> B({2, 2, 2, 2});

  {
    StaticDense<int, 2, 2> R;
    TEST_DEBUG("R = A + B");
    R = A + B;
    REQUIRE(R[0] == 3);
    REQUIRE(R[1] == 3);
    REQUIRE(R[2] == 3);
    REQUIRE(R[3] == 3);
  }
}

TEST_CASE("Static: Mul", "[static]") {
  StaticDense<int, 2, 2> A({1, 1, 1, 1});
  StaticDense<int, 2, 2> B({2, 2, 2, 2});

  {
    StaticDense<int, 2, 2> R;
    TEST_DEBUG("R = A * B");
    R = A * B;
    REQUIRE(R[0] == 4);
    REQUIRE(R[1] == 4);
    REQUIRE(R[2] == 4);
    REQUIRE(R[3] == 4);
  }

  {
    StaticDense<int, 2, 3> C({1, 2, 3, 4, 5, 6});
    StaticDense<int, 3, 2> D({1, 2, 3, 4, 5, 6});
    StaticDense<int, 2, 2> R;
    TEST_DEBUG("R = C * D");
    R = C * D;
    REQUIRE(R[0] == 22);
    REQUIRE(R[1] == 28);
    REQUIRE(R[2] == 49);
    REQUIRE(R[3] == 64);
  }
}


TEST_CASE("Static: Traits", "[static]") {
  {
    StaticDense<int, 3, 3> A({0, 1, 2, 3, 4, 5, 6, 7, 8});
    StaticDense<int, 3, 3> B({0, 1, 2, 3, 4, 5, 6, 7, 8});
    StaticDense<int, 3, 3> R;
    using nano = std::chrono::nanoseconds;
    auto start = std::chrono::high_resolution_clock::now();
    R = A*B;
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "duration dense mul: "
              << std::chrono::duration_cast<nano>(finish - start).count()
              << '\n';
  }

  {
    StaticDense<int, 3, 3> L({1, 0, 0, 1, 1, 0, 1, 1, 1});
    using nano = std::chrono::nanoseconds;
    auto start = std::chrono::high_resolution_clock::now();
    is_lower(L);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "duration is_lower static: "
              << std::chrono::duration_cast<nano>(finish - start).count()
              << '\n';
    REQUIRE(is_square(L));
    REQUIRE(is_lower(L));
  }

  {
    DenseMatrix<int> L(3, 3, {1, 0, 0, 1, 1, 0, 1, 1, 1});
    using nano = std::chrono::nanoseconds;
    auto start = std::chrono::high_resolution_clock::now();
    is_lower(L);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "duration is_lower dense: "
              << std::chrono::duration_cast<nano>(finish - start).count()
              << '\n';
    REQUIRE(is_square(L));
    REQUIRE(is_lower(L));
  }

  {
    StaticDense<int, 3, 3> S({1, 1, 1, 1, 1, 1, 1, 1, 1});
    using nano = std::chrono::nanoseconds;
    auto start = std::chrono::high_resolution_clock::now();
    is_square(S);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "duration is_square static: "
              << std::chrono::duration_cast<nano>(finish - start).count()
              << '\n';
    REQUIRE(is_square(S));
  }

  {
    DenseMatrix<int> S(3, 3, {1, 1, 1, 1, 1, 1, 1, 1, 1});
    using nano = std::chrono::nanoseconds;
    auto start = std::chrono::high_resolution_clock::now();
    is_square(S);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "duration is_square dense: "
              << std::chrono::duration_cast<nano>(finish - start).count()
              << '\n';
    REQUIRE(is_square(S));
  }

  {
    StaticDense<int, 3, 3> U({1, 1, 1, 0, 1, 1, 0, 0, 1});
    using nano = std::chrono::nanoseconds;
    auto start = std::chrono::high_resolution_clock::now();
    is_upper(U);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "duration is_upper static: "
              << std::chrono::duration_cast<nano>(finish - start).count()
              << '\n';
    REQUIRE(is_square(U));
    REQUIRE(is_upper(U));
  }

  {
    DenseMatrix<int> U(3, 3, {1, 1, 1, 0, 1, 1, 0, 0, 1});
    using nano = std::chrono::nanoseconds;
    auto start = std::chrono::high_resolution_clock::now();
    is_upper(U);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "duration is_upper dense: "
              << std::chrono::duration_cast<nano>(finish - start).count()
              << '\n';
    REQUIRE(is_square(U));
    REQUIRE(is_upper(U));
  }

}
