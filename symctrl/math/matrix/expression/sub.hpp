#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_SUB_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_SUB_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/sub.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/expression/unary.hpp>
#include <symctrl/type_traits/is_scalar.hpp>
#include <symctrl/math/matrix/type_traits/is_expr.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprSub
//
template<typename T1, typename T2>
class ExprSub<Matrix, T1, T2> :
  public Expression<Matrix<ExprSub<Matrix, T1, T2>>> {
public:
  using type = typename T1::type;

  using result_type = result_type_t<T1>;

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprSub(const T1 &lhs, const T2 &rhs);

  inline ExprSub(const ExprSub<Matrix, T1, T2> &m);

  operator type() const;

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline type operator[](const size_t pos);
  inline const type operator[](const size_t pos) const;

private:
  // A - B
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprSub<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - B");
    if(!is_expr_m<T1>::value && equal(~lhs, rhs.lhs_)) {
      apply_sub_(~lhs, rhs.rhs_);
    }
    else if(!is_expr_m<T2>::value && equal(~lhs, rhs.rhs_)) {
      apply_sub_(~lhs, rhs.lhs_);
    }
    else {
      apply_(~lhs, rhs.lhs_);
      apply_sub_(~lhs, rhs.rhs_);
    }
  }

  // A + (B - C)
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprSub<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A + (B - C)");
    apply_add_(~lhs, rhs.lhs_);
    apply_sub_(~lhs, rhs.rhs_);
  }

  // A - (B - C)
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprSub<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - (B - C)");
    apply_sub_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  // A * (B - C)
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprSub<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A * (B - C)");
    T1 tmp(rhs.lhs_);
    apply_sub_(tmp, rhs.rhs_);
    apply_mul_(~lhs, tmp);
  }

  // (A - B)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprSub<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = (A - B)^-1");
    T1 tmp(rhs.lhs_);
    apply_sub_(tmp, rhs.rhs_);
    apply_inverse_(~lhs, tmp);
  }

  // (A - B)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprSub<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = (A - B)^T");
    T1 tmp(rhs.lhs_);
    apply_sub_(tmp, rhs.rhs_);
    apply_transpose_(~lhs, tmp);
  }
};

// ----------------------------------------------------------------------
// ExprSub Constructor
//
template<typename T1, typename T2>
inline ExprSub<Matrix, T1, T2>::ExprSub(const T1 &lhs,
                                const T2 &rhs) :
                                lhs_(lhs),
                                rhs_(rhs) {
  //
}

template<typename T1, typename T2>
inline ExprSub<Matrix, T1, T2>::ExprSub(const ExprSub<Matrix, T1, T2> &m) :
                                lhs_(m.lhs_),
                                rhs_(m.rhs_) {
  //
}

// ----------------------------------------------------------------------
// ExprSub Type Conversion Operator
//
template<typename T1, typename T2>
ExprSub<Matrix, T1, T2>::operator ExprSub<Matrix, T1, T2>::type() const {
  result_type r;
  apply_(r, *this);

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprSub Member Function Definitions
//
template<typename T1, typename T2>
inline size_t ExprSub<Matrix, T1, T2>::size() const {
  return lhs_.size();
}

template<typename T1, typename T2>
inline size_t ExprSub<Matrix, T1, T2>::capacity() const {
  return lhs_.capacity();
}

template<typename T1, typename T2>
inline bool ExprSub<Matrix, T1, T2>::empty() const {
  return lhs_.empty();
}

template<typename T1, typename T2>
inline size_t ExprSub<Matrix, T1, T2>::nrows() const {
  return lhs_.nrows();
}

template<typename T1, typename T2>
inline size_t ExprSub<Matrix, T1, T2>::ncols() const {
  return lhs_.ncols();
}

template<typename T1, typename T2>
inline typename ExprSub<Matrix, T1, T2>::type
ExprSub<Matrix, T1, T2>::operator[](const size_t pos) {
  return lhs_[pos] - rhs_[pos];
}

template<typename T1, typename T2>
inline const typename ExprSub<Matrix, T1, T2>::type
ExprSub<Matrix, T1, T2>::operator[](const size_t pos) const {
  return lhs_[pos] - rhs_[pos];
}

// ----------------------------------------------------------------------
// ExprSub Operator
//
template<typename T1, typename T2>
inline const ExprSub<Matrix, T1, T2>
operator-(const Matrix<T1> &lhs, const Matrix<T2> &rhs) {
  return ExprSub<Matrix, T1, T2>(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// ExprSub Scalar Operator
//
template<typename T1, typename T2>
inline auto
operator-(const Matrix<T1> &lhs, const T2 rhs)
-> enable_if_scalar_t<T2, const ExprUnary<Matrix, T1>> {
  T1 tmp(~lhs);
  return ExprUnary<Matrix, T1>(tmp -= rhs);
}

template<typename T1, typename T2>
inline auto
operator-(const T1 lhs, const Matrix<T2> &rhs)
-> enable_if_scalar_t<T1, const ExprUnary<Matrix, T2>> {
  T2 tmp(~rhs);
  tmp *= -1;
  return ExprUnary<Matrix, T2>(tmp += lhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_SUB_HPP
