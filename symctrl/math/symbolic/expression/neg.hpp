#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_NEG_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_NEG_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/neg.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprNeg
//
template<typename T>
class ExprNeg<Symbolic, T>
    : public Expression<Symbolic<ExprNeg<Symbolic, T>>> {
public:
  using Type = ExprNeg<Symbolic, T>;
  static constexpr bool isNumeric = T::isNumeric;

private:
  const T m_;

public:
  explicit inline ExprNeg(const T &m);

  inline std::string as_str() const;
  inline hash_t hash() const;

  inline bool canEvaluate() const;

private:
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprNeg<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = -A");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_add_(Symbolic<DT> &lhs, const ExprNeg<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A + -B");
    apply_sub_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_diff_(Symbolic<DT> &lhs, const ExprNeg<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = diff(-A)");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_div_(Symbolic<DT> &lhs, const ExprNeg<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A / -B");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Symbolic<DT> &lhs, const ExprNeg<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A * -B");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_neg_(Symbolic<DT> &lhs, const ExprNeg<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = -(-B)");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_pow_(Symbolic<DT> &lhs, const ExprNeg<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A^(-B)");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_sub_(Symbolic<DT> &lhs, const ExprNeg<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A - -B");
    apply_add_(~lhs, rhs.m_);
  }
};

// ----------------------------------------------------------------------
// ExprNeg Constructor
//
template<typename T>
inline ExprNeg<Symbolic, T>::ExprNeg(const T &m)
    : m_(m) {}

// ----------------------------------------------------------------------
// ExprNeg Member Function Definitions
//
template<typename T>
inline std::string ExprNeg<Symbolic, T>::as_str() const {
  return "-" + m_.as_str();
}

template<typename T>
inline hash_t ExprNeg<Symbolic, T>::hash() const {
  return m_.hash() ^ 50;
}

template<typename T>
inline bool ExprNeg<Symbolic, T>::canEvaluate() const {
  return m_.canEvaluate();
}

// ----------------------------------------------------------------------
// ExprNeg Negation Operator
//
template<typename T>
inline auto operator-(const Symbolic<T> &m)
-> const ExprNeg<Symbolic, T> {
  return ExprNeg<Symbolic, T>(~m);
}

template<typename T>
inline auto operator-(const sym_number<T> &m)
-> const sym_number<T> {
  using ReturnType = sym_number<T>;
  return ReturnType(-1*m.real());
}

template<typename T>
inline const T operator-(const ExprNeg<Symbolic, T> &m) {
  return m.get_operand();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_NEG_HPP
