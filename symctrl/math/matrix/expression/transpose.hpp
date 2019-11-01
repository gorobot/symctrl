#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_TRANSPOSE_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_TRANSPOSE_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprTranspose
//
template<typename M>
class ExprTranspose : public Expression<Matrix<ExprTranspose<M>>> {
public:
  using type = typename M::type;

  using result_type = result_type_t<M>;

private:
  const M m_;

public:
  explicit inline ExprTranspose(const M &m);

  operator type() const;

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline type operator[](const size_t pos);
  inline const type operator[](const size_t pos) const;

private:
  // A^T
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    SYMCTRL_DEBUG("result = A^T");
    apply_transpose_(~lhs, rhs.m_);
  }

  // A + B^T
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    SYMCTRL_DEBUG("result = A + B^T");
    result_type tmp(rhs.m_);
    apply_transpose_(tmp, rhs.m_);
    apply_add_(~lhs, tmp);
  }

  // A * B^T
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    SYMCTRL_DEBUG("result = A * B^T");
    result_type tmp(rhs.m_);
    apply_transpose_(tmp, rhs.m_);
    apply_mul_(~lhs, tmp);
  }

  // (A^T)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    SYMCTRL_DEBUG("result = (A^T)^T");
    apply_(~lhs, rhs.m_);
  }

  // (A^T)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    SYMCTRL_DEBUG("result = (A^T)^-1");
    apply_inverse_(~lhs, rhs.m_);
  }
};

// ----------------------------------------------------------------------
// ExprTranspose Constructor
//
template<typename M>
inline ExprTranspose<M>::ExprTranspose(const M &m) :
                                       m_(m) {
  //
}

// ----------------------------------------------------------------------
// ExprTranspose Type Conversion Operator
//
template<typename M>
ExprTranspose<M>::operator ExprTranspose<M>::type() const {
  result_type r;
  apply_(r, *this);

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprTranspose Member Function Definitions
//
template<typename M>
inline size_t ExprTranspose<M>::size() const {
  return m_.size();
}

template<typename M>
inline size_t ExprTranspose<M>::capacity() const {
  return m_.capacity();
}

template<typename M>
inline bool ExprTranspose<M>::empty() const {
  return m_.empty();
}

template<typename M>
inline size_t ExprTranspose<M>::nrows() const {
  return m_.ncols();
}

template<typename M>
inline size_t ExprTranspose<M>::ncols() const {
  return m_.nrows();
}

template<typename M>
inline typename ExprTranspose<M>::type
ExprTranspose<M>::operator[](const size_t pos) {
  size_t row = m_.nrows();
  size_t col = m_.ncols();
  size_t i = pos%col;
  size_t j = pos - 1;
  return m_[i + row*j];
}

template<typename M>
inline const typename ExprTranspose<M>::type
ExprTranspose<M>::operator[](const size_t pos) const {
  size_t row = m_.nrows();
  size_t col = m_.ncols();
  size_t i = pos%col;
  size_t j = pos - 1;
  return m_[i + row*j];
}

template<typename M>
inline const ExprTranspose<M>
transpose(const Matrix<M> &m) {
  return ExprTranspose<M>(~m);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_TRANSPOSE_HPP
