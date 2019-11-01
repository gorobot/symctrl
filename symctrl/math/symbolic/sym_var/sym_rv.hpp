#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_RV_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_RV_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/shims/make_unique.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_rv
//
template<typename T = double>
class sym_rv
    : public Symbolic<sym_rv> {
public:
  using Type = sym_rv;

  static constexpr bool isNumeric = false;
  static constexpr bool isComplex = false;

  static inline constexpr bool canEvaluate() noexcept { return false; }

private:
  std::string name_;
  std::unique_ptr<RandomNumberDistribution> dist_;

  hash_t hash_;

public:
  explicit inline sym_rv();
  explicit inline sym_rv(std::string name, RandomNumberDistribution &dist);

  inline std::string as_str() const;
  inline hash_t hash() const;

  inline T real_value() const;
  inline T imag_value() const;

  inline T sample() const;
};

// ----------------------------------------------------------------------
// sym_rv Constructor
//
inline sym_rv::sym_rv()
    : name_(std::string()),
      hash_(0) {}

inline sym_rv::sym_rv(std::string name, RandomNumberDistribution &dist)
    : name_(name),
      hash_(hash_string{}(name)),
      dist_(make_unique(dist)) {}

// ----------------------------------------------------------------------
// Symbolic Member Function Definitions
//
inline std::string sym_rv::as_str() const {
  return name_;
}

inline hash_t sym_rv::hash() const {
  return hash_;
}

template<typename T>
inline T sym_number<T>::real_value() const {
  return (*this).sample();
}

template<typename T>
inline T sym_number<T>::imag_value() const {
  return T(0);
}

template<typename T>
inline T sym_number<T>::sample() const {
  // Sample from the distribution.
  return 0;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_RV_HPP
