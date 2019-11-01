#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_MUL_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_MUL_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/mul.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
// #include <symctrl/math/symbolic/type_traits/is_numeric.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprMul
//
template<typename T1, typename T2>
class ExprMul<Symbolic, T1, T2> :
  public Expression<Symbolic<ExprMul<Symbolic, T1, T2>>> {
public:
  using Type = ExprMul<Symbolic, T1, T2>;
  static constexpr bool isNumeric = (T1::isNumeric && T2::isNumeric);

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprMul(const T1 &lhs, const T2 &rhs);

  inline std::string as_str() const;
  inline hash_t hash() const;

  inline bool canEvaluate() const;

private:
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprMul<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A * B");
    apply_(~lhs, rhs.lhs_);
    apply_mul_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_add_(Symbolic<DT> &lhs, const ExprMul<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A + (B * C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_diff_(Symbolic<DT> &lhs, const ExprMul<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = diff(A * B)");
    // Product rule.
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_div_(Symbolic<DT> &lhs, const ExprMul<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A / (B * C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Symbolic<DT> &lhs, const ExprMul<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A * (B * C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_neg_(Symbolic<DT> &lhs, const ExprMul<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = -(A * B)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_pow_(Symbolic<DT> &lhs, const ExprMul<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = (A * B)^C");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_sub_(Symbolic<DT> &lhs, const ExprMul<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - (B * C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }
};

// ----------------------------------------------------------------------
// ExprMul Constructor
//
template<typename T1, typename T2>
inline ExprMul<Symbolic, T1, T2>::ExprMul(const T1 &lhs, const T2 &rhs)
    : lhs_(lhs),
      rhs_(rhs) {}

// ----------------------------------------------------------------------
// ExprMul Member Function Definitions
//
template<typename T1, typename T2>
inline std::string ExprMul<Symbolic, T1, T2>::as_str() const {
  return (~lhs_).as_str() + "*" + (~rhs_).as_str();
}

template<typename T1, typename T2>
inline hash_t ExprMul<Symbolic, T1, T2>::hash() const {
  return lhs_.hash() ^ rhs_.hash() ^ 200;
}

template<typename T1, typename T2>
inline bool ExprMul<Symbolic, T1, T2>::canEvaluate() const {
  return (lhs_.canEvaluate() && rhs_.canEvaluate());
}

// ----------------------------------------------------------------------
// ExprMul Operator
//
template<typename T1, typename T2>
inline auto operator*(const Symbolic<T1> &lhs, const Symbolic<T2> &rhs)
-> const ExprMul<Symbolic, T1, T2> {
  return ExprMul<Symbolic, T1, T2>(~lhs, ~rhs);
}

template<typename T1, typename T2>
inline auto operator*(const sym_number<T1> &lhs, const sym_number<T2> &rhs)
-> const sym_number<common_type_t<T1, T2>> {
  using ReturnType = sym_number<common_type_t<T1, T2>>;
  return ReturnType(lhs.real() * rhs.real());
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_MUL_HPP
