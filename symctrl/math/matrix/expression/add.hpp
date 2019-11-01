#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_ADD_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_ADD_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/add.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/expression/unary.hpp>
#include <symctrl/type_traits/is_scalar.hpp>
#include <symctrl/math/matrix/type_traits/is_expr.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprAdd
//
template< typename T1,   // First operand type.
          typename T2 >  // Second operand type.
class ExprAdd<Matrix, T1, T2>
    : public Expression<Matrix<ExprAdd<Matrix, T1, T2>>> {
public:
  using type = typename T1::type;

  using result_type = result_type_t<T1>;

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprAdd(const T1 &lhs, const T2 &rhs);

  inline ExprAdd(const ExprAdd<Matrix, T1, T2> &m);

  operator type() const;

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline type operator[](const size_t pos);
  inline const type operator[](const size_t pos) const;

private:
  // A + B
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprAdd<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A + B");
    if(!is_expr_m<T1>::value && equal(~lhs, rhs.lhs_)) {
      apply_add_(~lhs, rhs.rhs_);
    }
    else if(!is_expr_m<T2>::value && equal(~lhs, rhs.rhs_)) {
      apply_add_(~lhs, rhs.lhs_);
    }
    else {
      apply_(~lhs, rhs.lhs_);
      apply_add_(~lhs, rhs.rhs_);
    }
  }

  // A + (B + C)
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprAdd<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A + (B + C)");
    apply_add_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  // A - (B + C)
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprAdd<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - (B + C)");
    apply_sub_(~lhs, rhs.lhs_);
    apply_sub_(~lhs, rhs.rhs_);
  }

  // A * (B + C)
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprAdd<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A * (B + C)");
    result_type tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_mul_(~lhs, tmp);
  }

  // (A + B)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprAdd<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = (A + B)^-1");
    result_type tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_inverse_(~lhs, tmp);
  }

  // (A + B)^T = A^T + B^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprAdd<Matrix, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = (A + B)^T");
    result_type tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_transpose_(~lhs, tmp);
  }
};

// ----------------------------------------------------------------------
// ExprAdd Constructor
//
template<typename T1, typename T2>
inline ExprAdd<Matrix, T1, T2>::ExprAdd(const T1 &lhs, const T2 &rhs)
    : lhs_(lhs),
      rhs_(rhs) {}

template<typename T1, typename T2>
inline ExprAdd<Matrix, T1, T2>::ExprAdd(const ExprAdd<Matrix, T1, T2> &m)
    : lhs_(m.lhs_),
      rhs_(m.rhs_) {}

// ----------------------------------------------------------------------
// ExprAdd Type Conversion Operator
//
template<typename T1, typename T2>
ExprAdd<Matrix, T1, T2>::operator ExprAdd<Matrix, T1, T2>::type() const {
  result_type r;
  apply_(r, *this);

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprAdd Member Function Definitions
//
template<typename T1, typename T2>
inline size_t ExprAdd<Matrix, T1, T2>::size() const {
  return lhs_.size();
}

template<typename T1, typename T2>
inline size_t ExprAdd<Matrix, T1, T2>::capacity() const {
  return lhs_.capacity();
}

template<typename T1, typename T2>
inline bool ExprAdd<Matrix, T1, T2>::empty() const {
  return lhs_.empty();
}

template<typename T1, typename T2>
inline size_t ExprAdd<Matrix, T1, T2>::nrows() const {
  return lhs_.nrows();
}

template<typename T1, typename T2>
inline size_t ExprAdd<Matrix, T1, T2>::ncols() const {
  return lhs_.ncols();
}

template<typename T1, typename T2>
inline auto ExprAdd<Matrix, T1, T2>::operator[](const size_t pos)
-> typename ExprAdd<Matrix, T1, T2>::type {
  return lhs_[pos] + rhs_[pos];
}

template<typename T1, typename T2>
inline auto ExprAdd<Matrix, T1, T2>::operator[](const size_t pos) const
-> const typename ExprAdd<Matrix, T1, T2>::type {
  return lhs_[pos] + rhs_[pos];
}

// ----------------------------------------------------------------------
// ExprAdd Operator
//
template<typename T1, typename T2>
inline auto operator+(const Matrix<T1> &lhs, const Matrix<T2> &rhs)
-> const ExprAdd<Matrix, T1, T2> {
  return ExprAdd<Matrix, T1, T2>(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// ExprAdd Scalar Operator
//
template< typename T1,   // Matrix type.
          typename T2 >  // Scalar type.
inline auto operator+(const Matrix<T1> &lhs, const T2 rhs)
-> enable_if_scalar_t<T2, const ExprUnary<Matrix, T1>> {
  T1 tmp(~lhs);
  return ExprUnary<Matrix, T1>(tmp += rhs);
}

template< typename T1,   // Scalar type.
          typename T2 >  // Matrix type.
inline auto operator+(const T1 lhs, const Matrix<T2> &rhs)
-> enable_if_scalar_t<T1, const ExprUnary<Matrix, T2>> {
  T2 tmp(~rhs);
  return ExprUnary<Matrix, T2>(tmp += lhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_ADD_HPP
