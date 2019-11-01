#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_DIV_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_DIV_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/div.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
// #include <symctrl/math/symbolic/type_traits/is_numeric.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprDiv
//
template<typename T1, typename T2>
class ExprDiv<Symbolic, T1, T2> :
  public Expression<Symbolic<ExprDiv<Symbolic, T1, T2>>> {
public:
  using Type = ExprDiv<Symbolic, T1, T2>;
  static constexpr bool isNumeric = (T1::isNumeric && T2::isNumeric);

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprDiv(const T1 &lhs, const T2 &rhs);

  inline std::string as_str() const;
  inline hash_t hash() const;

  inline bool canEvaluate() const;

private:
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A / B");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_add_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A + (B / C)");
    apply_add_(~lhs, rhs.lhs_);
    apply_div_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_diff_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = diff(A / B)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_div_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A / (B / C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A * (B / C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_neg_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = -(A / B)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_pow_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = (A / B)^C");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_sub_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - (B / C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }
};

// ----------------------------------------------------------------------
// ExprDiv Constructor
//
template<typename T1, typename T2>
inline ExprDiv<Symbolic, T1, T2>::ExprDiv(const T1 &lhs, const T2 &rhs)
    : lhs_(lhs),
      rhs_(rhs) {}

// template<typename T1, typename T2>
// inline ExprDiv<Symbolic, T1, T2>::ExprDiv(ExprDiv<Symbolic, T1, T2> &m)
//     : lhs_(m.lhs_),
//       rhs_(m.rhs_) {}

// ----------------------------------------------------------------------
// ExprDiv Type Conversion Operator
//
// template<typename T1, typename T2>
// ExprDiv<Symbolic, T1, T2>::operator ExprDiv<Symbolic, T1, T2>::type() const {
//   result_type r;
//   apply_(r, *this);
//
//   return r;
// }

// ----------------------------------------------------------------------
// ExprDiv Member Function Definitions
//
template<typename T1, typename T2>
inline std::string ExprDiv<Symbolic, T1, T2>::as_str() const {
  return (~lhs_).as_str() + "/" + (~rhs_).as_str();
}

template<typename T1, typename T2>
inline hash_t ExprDiv<Symbolic, T1, T2>::hash() const {
  return lhs_.hash() ^ (rhs_.hash() << 1) ^ 250;
}

template<typename T1, typename T2>
inline bool ExprDiv<Symbolic, T1, T2>::canEvaluate() const {
  return (lhs_.canEvaluate() && rhs_.canEvaluate());
}

// ----------------------------------------------------------------------
// ExprDiv Operator
//
template<typename T1, typename T2>
inline auto operator/(const Symbolic<T1> &lhs, const Symbolic<T2> &rhs)
-> const ExprDiv<Symbolic, T1, T2> {
  return ExprDiv<Symbolic, T1, T2>(~lhs, ~rhs);
}

template<typename T1, typename T2>
inline auto operator/(const sym_number<T1> &lhs, const sym_number<T2> &rhs)
-> const sym_number<common_type_t<T1, T2>> {
  using ReturnType = sym_number<common_type_t<T1, T2>>;
  return ReturnType(lhs.real() / rhs.real());
}

// // ----------------------------------------------------------------------
// // ExprDiv Scalar Operator
// //
// template<typename T1, typename T2>
// inline auto
// operator*(const Symbolic<T1> &lhs, const T2 rhs)
// -> enable_if_scalar_t<T2, const ExprUnary<Symbolic, T1>> {
//   T1 tmp(~lhs);
//   return ExprUnary<Symbolic, T1>(tmp *= rhs);
// }
//
// template<typename T1, typename T2>
// inline auto
// operator*(const T1 lhs, const Symbolic<T2> &rhs)
// -> enable_if_scalar_t<T1, const ExprUnary<Symbolic, T2>> {
//   T2 tmp(~rhs);
//   return ExprUnary<Symbolic, T2>(tmp *= lhs);
// }

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_DIV_HPP
