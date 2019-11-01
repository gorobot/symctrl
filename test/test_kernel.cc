#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

#include <symctrl/math/functor/kernel.hpp>
#include <symctrl/math/matrix/dense.hpp>

TEST_CASE("Kernel: Dot Kernel", "[kernel]") {
  std::vector<double> x = {1, 2};
  std::vector<double> y = {3, 4};
  double result;

  Controls::Math::DotKernel k;

  result = k(x, y);

  REQUIRE(result == 11);
}

TEST_CASE("Kernel: Polynomial Kernel", "[kernel]") {
  std::vector<double> x = {1, 2};
  std::vector<double> y = {3, 4};
  double result;

  Controls::Math::PolynomialKernel k(1, 0, 2);

  result = k(x, y);

  REQUIRE(result == 121);
}

TEST_CASE("Kernel: Gaussian Kernel", "[kernel]") {
  std::vector<double> x = {1, 2};
  std::vector<double> y = {3, 4};
  double result;

  Controls::Math::GaussianKernel k(2);

  result = k(x, y);

  REQUIRE(::fabs(result - 0.3679) < 1e-3);
}

// TEST_CASE("Kernel: dot kernel gramian", "[kernel]") {
//   std::vector<double> x = {1, 2};
//   std::vector<double> y = {3, 4};
//
//   Controls::DotKernel k;
//
//   Controls::DenseMatrix<double> M(2, 2);
//
//   gramian(k, x, M);
//
//   REQUIRE(M(0, 0) == 1);
//   REQUIRE(M(0, 1) == 2);
//   REQUIRE(M(1, 0) == 2);
//   REQUIRE(M(1, 1) == 4);
//   // Symmetric
//   REQUIRE(M(0, 1) == M(1, 0));
//   // Positive Definite
//   for(auto it = M.begin(); it != M.end(); ++it) {
//     REQUIRE(*it > 0);
//   }
//
//   gramian(k, x, y, M);
//
//   REQUIRE(M(0, 0) == 3);
//   REQUIRE(M(0, 1) == 4);
//   REQUIRE(M(1, 0) == 6);
//   REQUIRE(M(1, 1) == 8);
// }
//
// TEST_CASE("Kernel: polynomial kernel gramian", "[kernel]") {
//   std::vector<double> x = {1, 2};
//   std::vector<double> y = {3, 4};
//
//   Controls::PolynomialKernel k(1, 0, 2);
//
//   Controls::DenseMatrix<double> M(2, 2);
//
//   gramian(k, x, M);
//
//   REQUIRE(M(0, 0) == 1);
//   REQUIRE(M(0, 1) == 4);
//   REQUIRE(M(1, 0) == 4);
//   REQUIRE(M(1, 1) == 16);
//   // Symmetric
//   REQUIRE(M(0, 1) == M(1, 0));
//   // Positive Definite
//   for(auto it = M.begin(); it != M.end(); ++it) {
//     REQUIRE(*it > 0);
//   }
//
//   gramian(k, x, y, M);
//
//   REQUIRE(M(0, 0) == 9);
//   REQUIRE(M(0, 1) == 16);
//   REQUIRE(M(1, 0) == 36);
//   REQUIRE(M(1, 1) == 64);
// }
//
// TEST_CASE("Kernel: gaussian kernel gramian", "[kernel]") {
//   std::vector<double> x = {1, 2};
//   std::vector<double> y = {3, 4};
//
//   Controls::GaussianKernel k(2);
//
//   Controls::DenseMatrix<double> A(2, 2);
//
//   gramian(k, x, A);
//
//   REQUIRE(A(0, 0) == 1);
//   REQUIRE(::fabs(A(0, 1) - 0.8825) < 1e-3);
//   REQUIRE(::fabs(A(1, 0) - 0.8825) < 1e-3);
//   REQUIRE(A(1, 1) == 1);
//   // Symmetric
//   REQUIRE(A(0, 1) == A(1, 0));
//   // Positive Definite
//   for(auto it = A.begin(); it != A.end(); ++it) {
//     REQUIRE(*it > 0);
//   }
//
//   gramian(k, x, y, A);
//
//   REQUIRE(::fabs(A(0, 0) - 0.6065) < 1e-3);
//   REQUIRE(::fabs(A(0, 1) - 0.3247) < 1e-3);
//   REQUIRE(::fabs(A(1, 0) - 0.8825) < 1e-3);
//   REQUIRE(::fabs(A(1, 1) - 0.6065) < 1e-3);
//
//   Controls::DenseMatrix<double> X(3, 2, {1, 2, 3, 4, 5, 6});
//
//   Controls::DenseMatrix<double> B(3, 3);
//
//   gramian(k, X, B);
//
//   REQUIRE(B(0, 0) == 1);
//   REQUIRE(::fabs(B(0, 1) - 0.3679) < 1e-3);
//   REQUIRE(::fabs(B(0, 2) - 0.0183) < 1e-3);
//   REQUIRE(::fabs(B(1, 0) - 0.3679) < 1e-3);
//   REQUIRE(B(1, 1) == 1);
//   REQUIRE(::fabs(B(1, 2) - 0.3679) < 1e-3);
//   REQUIRE(::fabs(B(2, 0) - 0.0183) < 1e-3);
//   REQUIRE(::fabs(B(2, 1) - 0.3679) < 1e-3);
//   REQUIRE(B(2, 2) == 1);
//   // Symmetric
//   REQUIRE(B(0, 1) == B(1, 0));
//   REQUIRE(B(0, 2) == B(2, 0));
//   REQUIRE(B(1, 2) == B(2, 1));
//   // Positive Definite
//   for(auto it = B.begin(); it != B.end(); ++it) {
//     REQUIRE(*it > 0);
//   }
// }

// TEST_CASE("Kernel: dot kernel estimate", "[kernel]") {
//   std::vector<int> x = {1, 2};
//   std::vector<int> y = {3, 4};
//   std::vector<double> alpha = {2, 3};
//   std::vector<double> result(2);
//
//   Controls::KernelFunction<int>
//   *k = new Controls::DotKernel<int>;
//
//   Controls::kernel_estimate(x, y, alpha, k, result);
//
//   REQUIRE(result.at(0) == 18);
//   REQUIRE(result.at(1) == 36);
// }
//
// TEST_CASE("Kernel: polynomial kernel estimate", "[kernel]") {
//   std::vector<int> x = {1, 2};
//   std::vector<int> y = {3, 4};
//   std::vector<double> alpha = {2, 3};
//   std::vector<double> result(2);
//
//   Controls::KernelFunction<int>
//   *k = new Controls::PolynomialKernel<int>(1, 0, 2);
//
//   Controls::kernel_estimate(x, y, alpha, k, result);
//
//   REQUIRE(result.at(0) == 66);
//   REQUIRE(result.at(1) == 264);
// }
//
// TEST_CASE("Kernel: gaussian kernel estimate", "[kernel]") {
//   std::vector<int> x = {1, 2};
//   std::vector<int> y = {3, 4};
//   std::vector<double> alpha = {2, 3};
//   std::vector<double> result(2);
//
//   Controls::KernelFunction<int>
//   *k = new Controls::GaussianKernel<int>(2);
//
//   Controls::kernel_estimate(x, y, alpha, k, result);
//
//   REQUIRE(::fabs(result.at(0) - 2.1870) < 1e-3);
//   REQUIRE(::fabs(result.at(1) - 3.5846) < 1e-3);
// }
//
// TEST_CASE("Kernel: double integrator", "[kernel]") {
//   REQUIRE(1 == 1);
// }
