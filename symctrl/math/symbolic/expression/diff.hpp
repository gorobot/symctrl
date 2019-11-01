#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_DIFF_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_DIFF_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/diff.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprDiff
//
template<typename T>
class ExprDiff<Symbolic, T>
    : public Expression<Symbolic<ExprDiff<Symbolic, T>>> {
public:
  using Type = ExprDiff<Symbolic, T>;
  static constexpr bool isNumeric = T::isNumeric;

private:
  const T m_;

public:
  explicit inline ExprDiff(const T &m);

  inline std::string as_str() const;
  inline hash_t hash() const;

  inline bool canEvaluate() const;

private:
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprDiff<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = diff(A)");
    apply_diff_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_add_(Symbolic<DT> &lhs, const ExprDiff<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A + diff(B)");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_diff_(Symbolic<DT> &lhs, const ExprDiff<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = diff(diff(A))");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_div_(Symbolic<DT> &lhs, const ExprDiff<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A / diff(B)");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Symbolic<DT> &lhs, const ExprDiff<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A * diff(B)");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_neg_(Symbolic<DT> &lhs, const ExprDiff<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = -diff(A)");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_pow_(Symbolic<DT> &lhs, const ExprDiff<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A^diff(B)");
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_sub_(Symbolic<DT> &lhs, const ExprDiff<Symbolic, T> &rhs) {
    SYMCTRL_DEBUG("result = A - diff(B)");
    apply_(~lhs, rhs.m_);
  }
};

// ----------------------------------------------------------------------
// ExprDiff Constructor
//
template<typename T>
inline ExprDiff<Symbolic, T>::ExprDiff(const T &m)
    : m_(m) {}

// ----------------------------------------------------------------------
// ExprDiff Member Function Definitions
//
template<typename T>
inline std::string ExprDiff<Symbolic, T>::as_str() const {
  return "d" + m_.as_str();
}

template<typename T>
inline hash_t ExprDiff<Symbolic, T>::hash() const {
  return m_.hash() ^ 300;
}

template<typename T>
inline bool ExprDiff<Symbolic, T>::canEvaluate() const {
  return m_.canEvaluate();
}

// ----------------------------------------------------------------------
// ExprDiff Operator
//
template<typename DT>
inline auto diff(const Symbolic<DT> &m)
-> const ExprDiff<Symbolic, DT> {
  return ExprDiff<Symbolic, DT>(~m);
}

template<typename T>
inline auto diff(const sym_number<T> &m)
-> const sym_number<T> {
  using ReturnType = sym_number<T>;
  return ReturnType(0);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_DIFF_HPP
