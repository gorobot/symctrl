#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_UNARY_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_UNARY_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/unary.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
// #include <symctrl/math/symbolic/type_traits/is_numeric.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprUnary
//
template<typename T>
class ExprUnary<Symbolic, T>
    : public Expression<Symbolic<ExprUnary<Symbolic, T>>> {
public:
  using Type = ExprUnary<Symbolic, T>;
  static constexpr bool isNumeric = T::isNumeric;

private:
  const T m_;

public:
  explicit inline ExprUnary(const T &m);

  inline std::string as_str() const;
  inline hash_t hash() const;

  inline bool canEvaluate() const;

private:
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprUnary<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_add_(Symbolic<DT> &lhs, const ExprUnary<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_diff_(Symbolic<DT> &lhs, const ExprUnary<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_div_(Symbolic<DT> &lhs, const ExprUnary<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Symbolic<DT> &lhs, const ExprUnary<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_neg_(Symbolic<DT> &lhs, const ExprUnary<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_pow_(Symbolic<DT> &lhs, const ExprUnary<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_sub_(Symbolic<DT> &lhs, const ExprUnary<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }
};

// ----------------------------------------------------------------------
// ExprUnary Constructor
//
template<typename T>
inline ExprUnary<Symbolic, T>::ExprUnary(const T &m)
    : m_(m) {}

// ----------------------------------------------------------------------
// ExprUnary Member Function Definitions
//
template<typename T>
inline std::string ExprUnary<Symbolic, T>::as_str() const {
  return m_.as_str();
}

template<typename T>
inline hash_t ExprUnary<Symbolic, T>::hash() const {
  return m_.hash();
}

template<typename T>
inline bool ExprUnary<Symbolic, T>::canEvaluate() const {
  return m_.canEvaluate();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_UNARY_HPP
