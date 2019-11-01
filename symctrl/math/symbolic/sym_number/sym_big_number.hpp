#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_BIG_NUMBER_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_BIG_NUMBER_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_big_number
//
class sym_big_number
    : public Symbolic<sym_big_number> {
public:
  using Type = sym_big_number;

  static constexpr bool isNumeric = true;
  static constexpr bool isComplex = false;

  static inline constexpr bool canEvaluate() noexcept { return true; }

private:
  T real_;

  mutable hash_t hash_;

public:
  explicit inline sym_big_number();
  inline sym_big_number(T m);

  template<typename DT>
  inline sym_big_number(const Symbolic<DT> &m);

  inline sym_big_number &operator=(T rhs);

  template<typename DT>
  inline sym_big_number &operator=(const Symbolic<DT> &rhs);

  template<typename DT>
  inline void apply(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_add(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_diff(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_div(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_mul(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_neg(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_pow(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_sub(const Symbolic<DT> &rhs);

  inline std::string as_str() const;
  inline hash_t hash() const;

  inline T real() const;
  inline T imag() const;
};

// ----------------------------------------------------------------------
// sym_big_number Constructor
//
inline sym_big_number::sym_big_number()
    : real_(0),
      hash_(0) {}

inline sym_big_number::sym_big_number(T m)
    : real_(std::move(m)),
      hash_(0) {}

template<typename DT>
inline sym_big_number::sym_big_number(const Symbolic<DT> &m) {
  apply_(*this, ~m);
}

// ----------------------------------------------------------------------
// sym_big_number Assignment Operator
//
inline sym_big_number &sym_big_number::operator=(T rhs) {
  real_ = rhs;
  hash_ = 0;

  return *this;
}

template<typename DT>
inline sym_big_number &sym_big_number::operator=(const Symbolic<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// sym_big_number Member Function Definitions
//
inline std::string sym_big_number::as_str() const {
  return std::to_string(real_);
}

inline hash_t sym_big_number::hash() const {
  if(hash_ == 0) {
    hash_ = hash_string{}(std::to_string(real_));
  }
  return hash_;
}

inline T sym_big_number::real() const {
  return real_;
}

inline T sym_big_number::imag() const {
  return 0;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_BIG_NUMBER_HPP
