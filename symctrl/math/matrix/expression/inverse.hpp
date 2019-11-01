#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_INVERSE_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_INVERSE_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/inverse.hpp>
#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprInverse
//
template<typename T>
class ExprInverse<Matrix, T> :
  public Expression<Matrix<ExprInverse<Matrix, T>>> {
public:
  using type = typename T::type;

  using result_type = result_type_t<T>;

private:
  const T &m_;

public:
  explicit inline ExprInverse(const T &m);

  operator type() const;

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline type operator[](const size_t pos);
  inline const type operator[](const size_t pos) const;

private:
  // A^-1
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprInverse<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = A^-1");
    apply_inverse_(~lhs, rhs.m_);
  }

  // A + B^-1
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprInverse<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = A + B^-1");
    T tmp(rhs.m_);
    apply_inverse_(tmp, rhs.m_);
    apply_add_(~lhs, tmp);
  }

  // A - B^-1
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprInverse<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = A - B^-1");
    T tmp(rhs.m_);
    apply_inverse_(tmp, rhs.m_);
    apply_sub_(~lhs, tmp);
  }

  // A * B^-1
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprInverse<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = A * B^-1");
    T tmp(rhs.m_);
    apply_inverse_(tmp, rhs.m_);
    apply_mul_(~lhs, tmp);
  }

  // (A^-1)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprInverse<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = (A^-1)^-1");
    apply_(~lhs, rhs.m_);
  }

  // (A^-1)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprInverse<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = (A^-1)^T");
    T tmp(rhs.m_);
    apply_transpose_(tmp, rhs.m_);
    apply_inverse_(~lhs, tmp);
  }
};

// ----------------------------------------------------------------------
// ExprInverse Constructor
//
template<typename T>
inline ExprInverse<Matrix, T>::ExprInverse(const T &m) :
                                   m_(m) {
  //
}

// ----------------------------------------------------------------------
// ExprInverse Type Conversion Operator
//
template<typename T>
ExprInverse<Matrix, T>::operator ExprInverse<Matrix, T>::type() const {
  result_type r;
  apply_inverse_(r, m_);

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprInverse Member Function Definitions
//
template<typename T>
inline size_t ExprInverse<Matrix, T>::size() const {
  return m_.size();
}

template<typename T>
inline size_t ExprInverse<Matrix, T>::capacity() const {
  return m_.capacity();
}

template<typename T>
inline bool ExprInverse<Matrix, T>::empty() const {
  return m_.empty();
}

template<typename T>
inline size_t ExprInverse<Matrix, T>::nrows() const {
  return m_.nrows();
}

template<typename T>
inline size_t ExprInverse<Matrix, T>::ncols() const {
  return m_.ncols();
}

template<typename T>
inline typename ExprInverse<Matrix, T>::type
ExprInverse<Matrix, T>::operator[](const size_t pos) {
  return m_[pos];
}

template<typename T>
inline const typename ExprInverse<Matrix, T>::type
ExprInverse<Matrix, T>::operator[](const size_t pos) const {
  return m_[pos];
}

template<typename T>
inline const ExprInverse<Matrix, T>
inverse(const Matrix<T> &m) {
  SYMCTRL_ASSERT(m.nrows() == m.ncols());

  return ExprInverse<Matrix, T>(~m);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_INVERSE_HPP
