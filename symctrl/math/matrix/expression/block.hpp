#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_BLOCK_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_BLOCK_HPP

#include <vector>

#include <symctrl/math/matrix/block/block.hpp>
#include <symctrl/math/matrix/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BlockMatrix Expressions
//
template<typename T, template<typename> class MT>
inline BlockMatrix<T, MT> &BlockMatrix<T, MT>::operator+=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T, template<typename> class MT>
inline BlockMatrix<T, MT> &BlockMatrix<T, MT>::operator-=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T, template<typename> class MT>
inline BlockMatrix<T, MT> &BlockMatrix<T, MT>::operator*=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] *= rhs;
  }

  return *this;
}

template<typename T, template<typename> class MT>
inline BlockMatrix<T, MT> &BlockMatrix<T, MT>::operator/=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] /= rhs;
  }

  return *this;
}

template<typename T, template<typename> class MT>
template<typename DT>
inline void BlockMatrix<T, MT>::apply(const Matrix<DT> &rhs) {
  n_ = (~rhs).nrows();
  m_ = (~rhs).ncols();
  v_ = (~rhs).as_vec();
}

template<typename T, template<typename> class MT>
template<typename DT>
inline void BlockMatrix<T, MT>::apply_add(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(n_ == (~rhs).nrows());
  SYMCTRL_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      SYMCTRL_ASSERT(v_[i*m_ + j].nrows() == (~rhs)[i*m_ + j].nrows());
      SYMCTRL_ASSERT(v_[i*m_ + j].ncols() == (~rhs)[i*m_ + j].ncols());

      v_[i*m_ + j].apply_add((~rhs)[i*m_ + j]);
    }
  }
}

template<typename T, template<typename> class MT>
template<typename DT>
inline void BlockMatrix<T, MT>::apply_sub(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(n_ == (~rhs).nrows());
  SYMCTRL_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      SYMCTRL_ASSERT(v_[i*m_ + j].nrows() == (~rhs)[i*m_ + j].nrows());
      SYMCTRL_ASSERT(v_[i*m_ + j].ncols() == (~rhs)[i*m_ + j].ncols());

      v_[i*m_ + j].apply_sub((~rhs)[i*m_ + j]);
    }
  }
}

template<typename T, template<typename> class MT>
template<typename DT>
inline void BlockMatrix<T, MT>::apply_mul(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(m_ == (~rhs).nrows());

  std::vector<MT<T>> t_(n_*(~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {

      for(size_t k = 0; k < m_; k++) {
        t_[i*(~rhs).ncols() + j] +=
          v_[i*m_ + k].apply_mul((~rhs)[k*(~rhs).ncols() + j]);
      }
    }
  }

  m_ = (~rhs).ncols();
  v_ = t_;
}

template<typename T, template<typename> class MT>
template<typename DT>
inline void BlockMatrix<T, MT>::apply_inverse(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT((~rhs).nrows() == (~rhs).ncols());

}

template<typename T, template<typename> class MT>
template<typename DT>
inline void BlockMatrix<T, MT>::apply_transpose(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(v_.size() == (~rhs).size());

  std::vector<MT<T>> t_((~rhs).size());

  for(size_t i = 0; i < (~rhs).nrows(); i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {
      t_[j*(~rhs).nrows() + i].apply_transpose((~rhs)[i*(~rhs).ncols() + j]);
    }
  }

  size_t tmp = (~rhs).nrows();
  n_ = (~rhs).ncols();
  m_ = tmp;
  v_ = t_;
}

// ----------------------------------------------------------------------
// BlockMatrix Equal
//
template<typename T, template<typename> class MT>
inline bool equal(const BlockMatrix<T, MT> &lhs, const BlockMatrix<T, MT> &rhs) {
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

template<typename T, template<typename> class MT, typename DT>
inline bool equal(const BlockMatrix<T, MT> &lhs, const Matrix<DT> &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  DenseMatrix<T> tmp = (~lhs).as_dense();

  for(size_t i = 0; i < (~lhs).size(); i++) {
    if(!equal((~rhs)[i], (~tmp)[i]))
      return false;
  }

  return true;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_BLOCK_HPP
