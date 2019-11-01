#include <cmath>
#include <numeric>
#include <vector>

#include <symctrl/math/functor/kernel.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Utility Functions
//
template< typename InputIt1,
          typename InputIt2 >
inline double
gk_euclidean_distance(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  //
  double init = 0;
  while (first1 != last1) {
    init += ::pow(::fabs(*first1 - *first2), 2);
    ++first1;
    ++first2;
  }
  return init;
}

// ----------------------------------------------------------------------
// Dot Kernel
//
double DotKernel::eval(const std::vector<double> &x,
                       const std::vector<double> &y) {
  //
  return std::inner_product(x.begin(), x.end(), y.begin(), 0);
}

// ----------------------------------------------------------------------
// Polynomial Kernel
//
double PolynomialKernel::eval(const std::vector<double> &x,
                              const std::vector<double> &y) {
  //
  double result = std::inner_product(x.begin(), x.end(), y.begin(), 0);
  result = ::pow(scale_*result + offset_, degree_);
  return result;
}

// ----------------------------------------------------------------------
// Gaussian Kernel
//
double GaussianKernel::eval(const std::vector<double> &x,
                            const std::vector<double> &y) {
  //
  double dist = gk_euclidean_distance(x.begin(), x.end(), y.begin());
  return ::exp((-1*dist)/(2*::pow(sigma_, 2)));
}

} // Math
} // Controls
