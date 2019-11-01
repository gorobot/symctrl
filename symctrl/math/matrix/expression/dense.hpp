#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_DENSE_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_DENSE_HPP

#include <vector>

#include <symctrl/math/matrix/dense/dense.hpp>
#include <symctrl/math/matrix/expression/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// DenseMatrix Expressions
//
template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator+=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator-=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator*=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] *= rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator/=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] /= rhs;
  }

  return *this;
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply(const Matrix<DT> &rhs) {
  n_ = (~rhs).nrows();
  m_ = (~rhs).ncols();
  v_ = (~rhs).as_vec();
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_add(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(n_ == (~rhs).nrows());
  SYMCTRL_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] += (~rhs)[i*m_ + j];
    }
  }
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_sub(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(n_ == (~rhs).nrows());
  SYMCTRL_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] -= (~rhs)[i*m_ + j];
    }
  }
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_mul(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(n_ == (~rhs).ncols());

  std::vector<T> t_(n_*(~rhs).ncols(), 0);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {

      for(size_t k = 0; k < m_; k++) {
        t_[i*(~rhs).ncols() + j] += v_[i*m_ + k] * (~rhs)[k*(~rhs).ncols() + j];
      }
    }
  }

  m_ = (~rhs).ncols();
  v_ = t_;
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_inverse(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT((~rhs).nrows() == (~rhs).ncols());
  SYMCTRL_ASSERT(v_.size() == (~rhs).size());

  std::vector<T> t_((~rhs).size());

  for(size_t i = 0; i < (~rhs).nrows(); i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {
      t_[j*(~rhs).nrows() + i] = (~rhs)[i*(~rhs).ncols() + j];
    }
  }

  size_t tmp = (~rhs).nrows();
  n_ = (~rhs).ncols();
  m_ = tmp;
  v_ = t_;
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_transpose(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(v_.size() == (~rhs).size());

  std::vector<T> t_((~rhs).size());

  for(size_t i = 0; i < (~rhs).nrows(); i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {
      t_[j*(~rhs).nrows() + i] = (~rhs)[i*(~rhs).ncols() + j];
    }
  }

  size_t tmp = (~rhs).nrows();
  n_ = (~rhs).ncols();
  m_ = tmp;
  v_ = t_;
}

// ----------------------------------------------------------------------
// DenseMatrix Equal
//
template<typename T>
inline bool equal(const DenseMatrix<T> &lhs, const DenseMatrix<T> &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).nrows(); i++) {
    for(size_t j = 0; j < (~lhs).ncols(); j++) {
      if(!equal((~lhs)(i, j), (~rhs)(i, j)))
        return false;
    }
  }

  return true;
}

template<typename T, typename DT>
inline bool equal(const DenseMatrix<T> &lhs, const Matrix<DT> &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).size(); i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_DENSE_HPP
