#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_NUMBER_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_NUMBER_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/recover.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_number
//
template<typename T>
class sym_number
    : public Symbolic<sym_number<T>> {
public:
  using Type = sym_number<T>;

  static constexpr bool isNumeric = true;
  static constexpr bool isComplex = false;

  static inline constexpr bool canEvaluate() noexcept { return true; }

private:
  T real_;

  mutable hash_t hash_;

public:
  explicit inline sym_number();
  inline sym_number(T m);

  template<typename DT>
  inline sym_number(const Symbolic<DT> &m);

  inline sym_number &operator=(T rhs);

  template<typename DT>
  inline sym_number &operator=(const Symbolic<DT> &rhs);

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

private:
  // friend type recover<type>(std::shared_ptr<void>);
};

// ----------------------------------------------------------------------
// sym_number Constructor
//
template<typename T>
inline sym_number<T>::sym_number()
    : real_(0),
      hash_(0) {}

template<typename T>
inline sym_number<T>::sym_number(T m)
    : real_(std::move(m)),
      hash_(0) {}

template<typename T>
template<typename DT>
inline sym_number<T>::sym_number(const Symbolic<DT> &m) {
  apply_(*this, ~m);
}

// ----------------------------------------------------------------------
// sym_number Assignment Operator
//
template<typename T>
inline sym_number<T> &sym_number<T>::operator=(T rhs) {
  real_ = rhs;
  hash_ = 0;

  return *this;
}

template<typename T>
template<typename DT>
inline sym_number<T> &sym_number<T>::operator=(const Symbolic<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// sym_number Member Function Definitions
//
template<typename T>
inline std::string sym_number<T>::as_str() const {
  return std::to_string(real_);
}

template<typename T>
inline hash_t sym_number<T>::hash() const {
  if(hash_ == 0) {
    hash_ = hash_string{}(std::to_string(real_));
  }
  return hash_;
}

template<typename T>
inline T sym_number<T>::real() const {
  return real_;
}

template<typename T>
inline T sym_number<T>::imag() const {
  return 0;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_NUMBER_HPP
