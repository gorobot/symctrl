#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_UNARY_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_UNARY_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/unary.hpp>
#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprUnary
//
template<typename T>
class ExprUnary<Matrix, T> :
  public Expression<Matrix<ExprUnary<Matrix, T>>> {
public:
  using type = typename T::type;

  using result_type = result_type_t<T>;

private:
  const T m_;

public:
  explicit inline ExprUnary(const T &m);

  inline ExprUnary(const ExprUnary<Matrix, T> &m);

  inline const T get_operand();

  operator type() const;

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline type operator[](const size_t pos);
  inline const type operator[](const size_t pos) const;

private:
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprUnary<Matrix, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprUnary<Matrix, T> &rhs) {
    apply_add_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprUnary<Matrix, T> &rhs) {
    apply_sub_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprUnary<Matrix, T> &rhs) {
    apply_mul_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprUnary<Matrix, T> &rhs) {
    apply_inverse_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprUnary<Matrix, T> &rhs) {
    apply_transpose_(~lhs, rhs.m_);
  }
};

// ----------------------------------------------------------------------
// ExprUnary Constructor
//
template<typename T>
inline ExprUnary<Matrix, T>::ExprUnary(const T &m) :
                               m_(m) {
  //
}

template<typename T>
inline ExprUnary<Matrix, T>::ExprUnary(const ExprUnary<Matrix, T> &m) :
                               m_(m.m_) {
  //
}

template<typename T>
inline const T ExprUnary<Matrix, T>::get_operand() {
  return m_;
}

// ----------------------------------------------------------------------
// ExprUnary Type Conversion Operator
//
template<typename T>
ExprUnary<Matrix, T>::operator ExprUnary<Matrix, T>::type() const {
  result_type r;
  apply_(r, *this);

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprUnary Member Function Definitions
//
template<typename T>
inline size_t ExprUnary<Matrix, T>::size() const {
  return m_.size();
}

template<typename T>
inline size_t ExprUnary<Matrix, T>::capacity() const {
  return m_.capacity();
}

template<typename T>
inline bool ExprUnary<Matrix, T>::empty() const {
  return m_.empty();
}

template<typename T>
inline size_t ExprUnary<Matrix, T>::nrows() const {
  return m_.nrows();
}

template<typename T>
inline size_t ExprUnary<Matrix, T>::ncols() const {
  return m_.ncols();
}

template<typename T>
inline typename ExprUnary<Matrix, T>::type
ExprUnary<Matrix, T>::operator[](const size_t pos) {
  return m_[pos];
}

template<typename T>
inline const typename ExprUnary<Matrix, T>::type
ExprUnary<Matrix, T>::operator[](const size_t pos) const {
  return m_[pos];
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_UNARY_HPP
