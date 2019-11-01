#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_COMPLEX_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_COMPLEX_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_complex
//
template<typename T>
class sym_complex
    : public Symbolic<sym_complex<T>> {
public:
  using Type = sym_complex<T>;

  static constexpr bool isNumeric = true;
  static constexpr bool isComplex = true;

  static inline constexpr bool canEvaluate() noexcept { return true; }

private:
  T real_;
  T imag_;

  mutable hash_t hash_;

public:
  explicit inline sym_complex();
  inline sym_complex(T real, T imag);

  // inline sym_complex(const sym_complex<T> &) = default;
  // inline sym_complex(sym_complex<T> &&) = default;

  // inline sym_complex<T> &operator=(const sym_complex<T> &) = default;
  // inline sym_complex<T> &operator=(sym_complex<T> &&) = default;

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
// sym_complex Constructor
//
template<typename T>
inline sym_complex<T>::sym_complex()
    : real_(0),
      imag_(0),
      hash_(0) {}

template<typename T>
inline sym_complex<T>::sym_complex(T real, T imag)
    : real_(std::move(real)),
      imag_(std::move(imag)),
      hash_(0) {}

// ----------------------------------------------------------------------
// sym_complex Member Function Definitions
//
template<typename T>
inline std::string sym_complex<T>::as_str() const {
  return std::to_string(real_);
}

template<typename T>
inline hash_t sym_complex<T>::hash() const {
  if(hash_ == 0) {
    hash_ = hash_string{}(std::to_string(real_ ^ imag_));
  }
  return hash_;
}

template<typename T>
inline T sym_complex<T>::real() const {
  return real_;
}

template<typename T>
inline T sym_complex<T>::imag() const {
  return imag_;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_COMPLEX_HPP
