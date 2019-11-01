#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_MUL_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_MUL_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/mul.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/expression/unary.hpp>
#include <symctrl/type_traits/is_scalar.hpp>
#include <symctrl/math/matrix/type_traits/is_expr.hpp>
#include <symctrl/math/matrix/type_traits/is_static.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprMul
//
template<typename T1, typename T2>
class ExprMul<Matrix, T1, T2> : public Expression<Matrix<ExprMul<Matrix, T1, T2>>> {
public:
  using type = typename T1::type;

  using result_type = result_type_t<T1>;

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprMul(const T1 &lhs, const T2 &rhs);

  inline ExprMul(const ExprMul<Matrix, T1, T2> &m);

  operator type() const;

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline type operator[](const size_t pos);
  inline const type operator[](const size_t pos) const;

private:
  // A * B (non-static)
  template<typename DT>
  friend inline auto
  apply_(Matrix<DT> &lhs, const ExprMul<Matrix, T1, T2> &rhs)
  -> disable_if_static_t<DT> {
    SYMCTRL_DEBUG("result = A * B");
    if(!is_expr_m<T1>::value && equal(~lhs, rhs.lhs_)) {
      apply_mul_(~lhs, rhs.rhs_);
    }
    else if(!is_expr_m<T2>::value && equal(~lhs, rhs.rhs_)) {
      apply_(~lhs, rhs.lhs_);
      apply_mul_(~lhs, rhs.rhs_);
    }
    else {
      apply_(~lhs, rhs.lhs_);
      apply_mul_(~lhs, rhs.rhs_);
    }
  }

  // A * B (static)
  template<typename DT>
  friend inline auto
  apply_(Matrix<DT> &lhs, const ExprMul<Matrix, T1, T2> &rhs)
  -> enable_if_static_t<DT> {
    SYMCTRL_DEBUG("result = A * B");
    result_type tmp(rhs.lhs_);
    apply_mul_(tmp, rhs.rhs_);
    apply_(~lhs, tmp);
  }

  // A + (B * C)
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprMul<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A + (B * C)");
    result_type tmp(rhs.lhs_);
    apply_mul_(tmp, rhs.rhs_);
    apply_add_(~lhs, tmp);
  }

  // A - (B * C)
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprMul<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - (B * C)");
    result_type tmp(rhs.lhs_);
    apply_mul_(tmp, rhs.rhs_);
    apply_sub_(~lhs, tmp);
  }

  // A * (B * C)
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprMul<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A * (B * C)");
    result_type tmp(rhs.lhs_);
    apply_mul_(tmp, rhs.rhs_);
    apply_mul_(~lhs, tmp);
  }

  // (A * B)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprMul<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = (A * B)^-1");
    result_type tmp(rhs.lhs_);
    apply_mul_(tmp, rhs.rhs_);
    apply_inverse_(~lhs, tmp);
  }

  // (A * B)^T = B^T * A^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprMul<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = (A * B)^T");
    result_type tmp(rhs.lhs_);
    apply_mul_(tmp, rhs.rhs_);
    apply_transpose_(~lhs, tmp);
  }
};

// ----------------------------------------------------------------------
// ExprMul Constructor
//
template<typename T1, typename T2>
inline ExprMul<Matrix, T1, T2>::ExprMul(const T1 &lhs,
                                const T2 &rhs) :
                                lhs_(lhs),
                                rhs_(rhs) {
  //
}

template<typename T1, typename T2>
inline ExprMul<Matrix, T1, T2>::ExprMul(const ExprMul<Matrix, T1, T2> &m) :
                                lhs_(m.lhs_),
                                rhs_(m.rhs_) {
  //
}

// ----------------------------------------------------------------------
// ExprMul Type Conversion Operator
//
template<typename T1, typename T2>
ExprMul<Matrix, T1, T2>::operator ExprMul<Matrix, T1, T2>::type() const {
  result_type r;
  apply_(r, *this);

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprMul Member Function Definitions
//
template<typename T1, typename T2>
inline size_t ExprMul<Matrix, T1, T2>::size() const {
  return lhs_.size();
}

template<typename T1, typename T2>
inline size_t ExprMul<Matrix, T1, T2>::capacity() const {
  return lhs_.capacity();
}

template<typename T1, typename T2>
inline bool ExprMul<Matrix, T1, T2>::empty() const {
  return lhs_.empty();
}

template<typename T1, typename T2>
inline size_t ExprMul<Matrix, T1, T2>::nrows() const {
  return lhs_.nrows();
}

template<typename T1, typename T2>
inline size_t ExprMul<Matrix, T1, T2>::ncols() const {
  return rhs_.ncols();
}

template<typename T1, typename T2>
inline typename ExprMul<Matrix, T1, T2>::type
ExprMul<Matrix, T1, T2>::operator[](const size_t pos) {
  size_t row = lhs_.nrows();
  size_t col = rhs_.ncols();
  size_t i = pos%col;
  size_t j = pos - 1;

  ExprMul<Matrix, T1, T2>::type result = 0;
  for(size_t k = 0; k < rhs_.nrows(); k++) {
    result += lhs_[i*col + k] * rhs_[k*col + j];
  }
  return result;
}

template<typename T1, typename T2>
inline const typename ExprMul<Matrix, T1, T2>::type
ExprMul<Matrix, T1, T2>::operator[](const size_t pos) const {
  size_t row = lhs_.nrows();
  size_t col = rhs_.ncols();
  size_t i = pos%col;
  size_t j = pos - 1;

  ExprMul<Matrix, T1, T2>::type result = 0;
  for(size_t k = 0; k < rhs_.nrows(); k++) {
    result += lhs_[i*col + k] * rhs_[k*col + j];
  }
  return result;
}

// ----------------------------------------------------------------------
// ExprMul Operator
//
template<typename T1, typename T2>
inline const ExprMul<Matrix, T1, T2>
operator*(const Matrix<T1> &lhs, const Matrix<T2> &rhs) {
  return ExprMul<Matrix, T1, T2>(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// ExprMul Multiply Scalar Operator
//
template<typename T1, typename T2>
inline auto
operator*(const Matrix<T1> &lhs, const T2 rhs)
-> enable_if_scalar_t<T2, const ExprUnary<Matrix, T1>> {
  T1 tmp(~lhs);
  return ExprUnary<Matrix, T1>(tmp *= rhs);
}

template<typename T1, typename T2>
inline auto
operator*(const T1 lhs, const Matrix<T2> &rhs)
-> enable_if_scalar_t<T1, const ExprUnary<Matrix, T2>> {
  T2 tmp(~rhs);
  return ExprUnary<Matrix, T2>(tmp *= lhs);
}

// ----------------------------------------------------------------------
// ExprMul Divide Scalar Operator
//
template<typename T1, typename T2>
inline auto
operator/(const Matrix<T1> &lhs, const T2 rhs)
-> enable_if_scalar_t<T2, const ExprUnary<Matrix, T1>> {
  T1 tmp(~lhs);
  return ExprUnary<Matrix, T1>(tmp /= rhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_MUL_HPP
