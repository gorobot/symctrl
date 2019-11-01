#ifndef SYMCTRL_MATH_FUNCTOR_KERNEL_HPP
#define SYMCTRL_MATH_FUNCTOR_KERNEL_HPP

#include <vector>

#include <symctrl/math/functor/functor.hpp>
#include <symctrl/math/functor/lambda.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// KernelFunction Signature
//
#ifndef KERNEL_FUNCTION_PARAMS
#define KERNEL_FUNCTION_PARAMS \
double, \
const std::vector<double> &, \
const std::vector<double> &
#endif

// ----------------------------------------------------------------------
// KernelFunction
//
// Example:
//
// Data: (1.0, 1.0), (1.2, 2.1), (1.4, 3.6)
// Matrix:
//   [1.0, 1.0]
//   [1.2, 2.1]
//   [1.4, 3.6]
class KernelFunction
    : public Functor<KernelFunction, KERNEL_FUNCTION_PARAMS> {
public:
  using type = BaseFunctor<KERNEL_FUNCTION_PARAMS>;

  virtual double eval(const std::vector<double> &x,
                      const std::vector<double> &y) = 0;
};

template<typename F>
inline KernelFunction::type *kernel_function(F&& f) {
  return new LambdaFunctor<F, KERNEL_FUNCTION_PARAMS>(f);
}

template<typename T>
inline bool is_a_kernel_function(T &b) {
  return dynamic_cast<KernelFunction::type *>(&b) != nullptr;
}

// ----------------------------------------------------------------------
// Dot Kernel
//
class DotKernel
    : public KernelFunction {
public:
  explicit inline DotKernel() {}

  double eval(const std::vector<double> &x,
              const std::vector<double> &y);
};

// ----------------------------------------------------------------------
// Polynomial Kernel
//
class PolynomialKernel
    : public KernelFunction {
private:
  double scale_;
  double offset_;
  int degree_;

public:
  explicit inline PolynomialKernel(const double scale,
                                   const double offset,
                                   const int degree);

  double eval(const std::vector<double> &x,
              const std::vector<double> &y);
};

inline PolynomialKernel::PolynomialKernel(const double scale,
                                          const double offset,
                                          const int degree)
    : scale_(scale),
      offset_(offset),
      degree_(degree) {}

// ----------------------------------------------------------------------
// Gaussian Kernel
//
class GaussianKernel
    : public KernelFunction {
private:
  double sigma_;

public:
  explicit inline GaussianKernel(const double sigma);

  double eval(const std::vector<double> &x,
              const std::vector<double> &y);
};

inline GaussianKernel::GaussianKernel(const double sigma)
    : sigma_(sigma) {}

} // Math
} // Controls

#endif // SYMCTRL_MATH_FUNCTOR_KERNEL_HPP
