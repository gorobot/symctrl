#ifndef SYMCTRL_MATH_RANDOM_RANDOM_DISTRIBUTION_HPP
#define SYMCTRL_MATH_RANDOM_RANDOM_DISTRIBUTION_HPP

#include <random>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// RandomNumberDistribution
//
class SampleVisitor;

class RandomNumberDistribution {
public:
  virtual ~RandomNumberDistribution() {};

  virtual void accept(SampleVisitor &visitor) = 0;
};

// ----------------------------------------------------------------------
// RandomNumberDistribution Class List
//
#ifndef SYMCTRL_RANDOM_DISTRIBUTIONS
#define SYMCTRL_RANDOM_DISTRIBUTIONS(MACRO) \
MACRO(UNIFORM_INT_DISTRIBUTION, uniform_int_distribution) \
MACRO(UNIFORM_REAL_DISTRIBUTION, uniform_real_distribution) \
MACRO(BINOMIAL_DISTRIBUTION, binomial_distribution) \
MACRO(NEGATIVE_BINOMIAL_DISTRIBUTION, negative_binomial_distribution) \
MACRO(GEOMETRIC_DISTRIBUTION, geometric_distribution) \
MACRO(POISSON_DISTRIBUTION, poisson_distribution) \
MACRO(EXPONENTIAL_DISTRIBUTION, exponential_distribution) \
MACRO(GAMMA_DISTRIBUTION, gamma_distribution) \
MACRO(WEIBULL_DISTRIBUTION, weibull_distribution) \
MACRO(EXTREME_VALUE_DISTRIBUTION, extreme_value_distribution) \
MACRO(NORMAL_DISTRIBUTION, normal_distribution) \
MACRO(LOGNORMAL_DISTRIBUTION, lognormal_distribution) \
MACRO(CHI_SQUARED_DISTRIBUTION, chi_squared_distribution) \
MACRO(CAUCHY_DISTRIBUTION, cauchy_distribution) \
MACRO(FISHER_F_DISTRIBUTION, fisher_f_distribution) \
MACRO(STUDENT_T_DISTRIBUTION, student_t_distribution) \
MACRO(DISCRETE_DISTRIBUTION, discrete_distribution) \
MACRO(PIECEWISE_CONSTANT_DISTRIBUTION, piecewise_constant_distribution) \
MACRO(PIECEWISE_LINEAR_DISTRIBUTION, piecewise_linear_distribution)
#endif

// ----------------------------------------------------------------------
// Enum Definition
//
#define SYMCTRL_RANDOM_DISTRIBUTION_ENUM(type, Class) type,
enum DistributionType {
  SYMCTRL_RANDOM_DISTRIBUTIONS(SYMCTRL_RANDOM_DISTRIBUTION_ENUM)
};
#undef SYMCTRL_RANDOM_DISTRIBUTION_ENUM

// ----------------------------------------------------------------------
// Bernoulli Distribution
//
// class bernoulli_distribution :
//   public RandomNumberDistribution, public std::bernoulli_distribution {
// public:
//   using std::bernoulli_distribution::bernoulli_distribution;
//   using std::bernoulli_distribution::operator();
//   using std::bernoulli_distribution::min;
//
//   void accept(SampleVisitor &visitor);
// };

// ----------------------------------------------------------------------
// Class Definitions
//
#define SYMCTRL_RANDOM_DISTRIBUTION_CLASS(type, Class) \
template<typename... Args> class Class : \
  public RandomNumberDistribution, public std::Class<Args...> { \
public: \
  using std::Class<Args...>::Class; \
  using std::Class<Args...>::operator(); \
  \
  void accept(SampleVisitor &visitor); \
};
SYMCTRL_RANDOM_DISTRIBUTIONS(SYMCTRL_RANDOM_DISTRIBUTION_CLASS)
#undef SYMCTRL_RANDOM_DISTRIBUTION_CLASS

// ----------------------------------------------------------------------
// SampleVisitor
//
class SampleVisitor {
private:
  double result_;
  std::random_device &gen_;

public:
  SampleVisitor(std::random_device &gen) : gen_(gen) {};

  #define SYMCTRL_RANDOM_DISTRIBUTION_VISITOR(type, Class) \
  template<typename... Args> \
  void visit(Class<Args...> &m) { result_ = m(gen_); }
  SYMCTRL_RANDOM_DISTRIBUTIONS(SYMCTRL_RANDOM_DISTRIBUTION_VISITOR)
  #undef SYMCTRL_RANDOM_DISTRIBUTION_VISITOR

  double get_result() const { return result_; }
};

inline double sample_distribution(RandomNumberDistribution &m,
                                  std::random_device &gen) {
  SampleVisitor v(gen);
  m.accept(v);
  return v.get_result();
}

// ----------------------------------------------------------------------
// Visitor Definitions
//
#define SYMCTRL_RANDOM_DISTRIBUTION_VISITOR_DEC(type, Class) \
template<typename... Args> \
void Class<Args...>::accept(SampleVisitor &visitor) { \
  visitor.visit(*this); \
}
SYMCTRL_RANDOM_DISTRIBUTIONS(SYMCTRL_RANDOM_DISTRIBUTION_VISITOR_DEC)
#undef SYMCTRL_RANDOM_DISTRIBUTION_VISITOR

} // Math
} // Controls

#endif // SYMCTRL_MATH_RANDOM_RANDOM_DISTRIBUTION_HPP
