#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_NEG_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_NEG_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/neg.hpp>
#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprNeg
//
template<typename T>
class ExprNeg<Matrix, T> :
  public Expression<Matrix<ExprNeg<Matrix, T>>> {
public:
  using type = typename T::type;

  using result_type = result_type_t<T>;

private:
  const T m_;

public:
  explicit inline ExprNeg(const T &m);

  inline ExprNeg(const ExprNeg<Matrix, T> &m);

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
  // -A
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprNeg<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = -A");
    apply_(~lhs, rhs.m_);
    ~lhs *= -1;
  }

  // A + -B
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprNeg<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = A + -B");
    apply_sub_(~lhs, rhs.m_);
  }

  // A - -B
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprNeg<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = A - -B");
    apply_add_(~lhs, rhs.m_);
  }

  // A * -B
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprNeg<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = A * -B");
    apply_mul_(~lhs, rhs.m_);
    ~lhs *= -1;
  }

  // (-A)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprNeg<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = (-A)^-1");
    apply_inverse_(~lhs, rhs.m_);
    ~lhs *= -1;
  }

  // (-A)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprNeg<Matrix, T> &rhs) {
    SYMCTRL_DEBUG("result = (-A)^T");
    apply_transpose_(~lhs, rhs.m_);
    ~lhs *= -1;
  }
};

// ----------------------------------------------------------------------
// ExprNeg Constructor
//
template<typename T>
inline ExprNeg<Matrix, T>::ExprNeg(const T &m) :
                           m_(m) {
  //
}

template<typename T>
inline ExprNeg<Matrix, T>::ExprNeg(const ExprNeg<Matrix, T> &m) :
                           m_(m.m_) {
  //
}

template<typename T>
inline const T ExprNeg<Matrix, T>::get_operand() {
  return m_;
}

// ----------------------------------------------------------------------
// ExprNeg Type Conversion Operator
//
template<typename T>
ExprNeg<Matrix, T>::operator ExprNeg<Matrix, T>::type() const {
  result_type r;
  apply_(r, m_);
  r *= -1;

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprNeg Member Function Definitions
//
template<typename T>
inline size_t ExprNeg<Matrix, T>::size() const {
  return m_.size();
}

template<typename T>
inline size_t ExprNeg<Matrix, T>::capacity() const {
  return m_.capacity();
}

template<typename T>
inline bool ExprNeg<Matrix, T>::empty() const {
  return m_.empty();
}

template<typename T>
inline size_t ExprNeg<Matrix, T>::nrows() const {
  return m_.nrows();
}

template<typename T>
inline size_t ExprNeg<Matrix, T>::ncols() const {
  return m_.ncols();
}

template<typename T>
inline typename ExprNeg<Matrix, T>::type
ExprNeg<Matrix, T>::operator[](const size_t pos) {
  return -m_[pos];
}

template<typename T>
inline const typename ExprNeg<Matrix, T>::type
ExprNeg<Matrix, T>::operator[](const size_t pos) const {
  return -m_[pos];
}

// ----------------------------------------------------------------------
// ExprNeg Operator
//
template<typename T>
inline const ExprNeg<Matrix, T>
operator-(const Matrix<T> &m) {
  return ExprNeg<Matrix, T>(~m);
}

template<typename T>
inline const T
operator-(const ExprNeg<Matrix, T> &m) {
  return m.get_operand();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_NEG_HPP
