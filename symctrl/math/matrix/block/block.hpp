#ifndef SYMCTRL_MATH_MATRIX_BLOCK_BLOCK_HPP
#define SYMCTRL_MATH_MATRIX_BLOCK_BLOCK_HPP

#include <vector>

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/dense/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BlockMatrix
//
template< typename T,                                  // Element type.
          template<typename> class MT = DenseMatrix >  // Matrix type.
class BlockMatrix
    : public Matrix<BlockMatrix<T, MT>> {
public:
  using type           = MT<T>;
  using vector_type    = std::vector<MT<T>>;
  using iterator       = typename vector_type::iterator;
  using const_iterator = typename vector_type::const_iterator;

  using result_type = BlockMatrix<T, MT>;

private:
  size_t n_;
  size_t m_;

  std::vector<size_t> nn_;
  std::vector<size_t> mm_;

  vector_type v_;

public:
  explicit inline BlockMatrix();
  explicit inline BlockMatrix(const size_t N, const size_t M);
  explicit inline BlockMatrix(const size_t N, const size_t M, const vector_type v);

  inline BlockMatrix(const BlockMatrix &m);

  template<typename DT>
  inline BlockMatrix(const Matrix<DT> &m);

  inline BlockMatrix &operator=(const T &rhs);
  inline BlockMatrix &operator=(const type &rhs);
  inline BlockMatrix &operator=(const BlockMatrix &rhs);

  template<typename DT>
  inline BlockMatrix &operator=(const Matrix<DT> &rhs);

  inline BlockMatrix &operator+=(const T &rhs);
  inline BlockMatrix &operator-=(const T &rhs);
  inline BlockMatrix &operator*=(const T &rhs);
  inline BlockMatrix &operator/=(const T &rhs);

  template<typename DT>
  inline void apply(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_add(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_sub(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_mul(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_inverse(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_transpose(const Matrix<DT> &rhs);

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline iterator begin();
  inline iterator end();
  inline const_iterator begin() const;
  inline const_iterator end() const;
  inline const_iterator cbegin() const;
  inline const_iterator cend() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline vector_type as_vec() const;
  inline type as_dense() const;

  inline type &operator[](const size_t pos);
  inline const type &operator[](const size_t pos) const;

  inline type &operator()(const size_t row, const size_t col);
  inline const type &operator()(const size_t row, const size_t col) const;
};

// ----------------------------------------------------------------------
// BlockMatrix Constructor
//
template< typename T,
          template<typename> class MT >
inline BlockMatrix<T, MT>::BlockMatrix()
    : n_(0),
      m_(0) {
  //
  v_ = std::vector<MT<T>>(0);
}

template< typename T,
          template<typename> class MT >
inline BlockMatrix<T, MT>::BlockMatrix(const size_t n, const size_t m)
    : n_(n),
      m_(m) {
  //
  v_ = std::vector<MT<T>>(n * m, MT<T>());
}

template< typename T,
          template<typename> class MT >
inline BlockMatrix<T, MT>::BlockMatrix(const size_t n,
                                       const size_t m,
                                       const std::vector<MT<T>> v)
    : n_(n),
      m_(m),
      v_(v) {
  //
  size_t row_size, col_size;

  // Assert row sizes are consistent.
  for(size_t i = 0; i < n_; i++) {
    row_size = v_[i*m_].nrows();

    for(size_t j = 0; j < m_; j++) {
      SYMCTRL_ASSERT(v_[i*m_ + j].nrows() == row_size);
    }
  }

  // Assert column sizes are consistent.
  for(size_t j = 0; j < m_; j++) {
    col_size = v_[j].ncols();

    for(size_t i = 0; i < n_; i++) {
      SYMCTRL_ASSERT(v_[i*m_ + j].ncols() == col_size);
    }
  }

  for(size_t i = 0; i < v.size(); i++) {
    apply_(~(v_[i]), ~(v[i]));
  }
}

template< typename T,
          template<typename> class MT >
inline BlockMatrix<T, MT>::BlockMatrix(const BlockMatrix<T, MT> &m)
    : n_(m.n_),
      m_(m.m_),
      v_(m.v_) {
  //
}

// ----------------------------------------------------------------------
// BlockMatrix Assignment Operator
//
template< typename T,
          template<typename> class MT >
inline auto BlockMatrix<T, MT>::operator=(const T &rhs)
-> BlockMatrix<T, MT>& {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = rhs;
  }

  return *this;
}

template< typename T,
          template<typename> class MT >
inline auto BlockMatrix<T, MT>::operator=(const MT<T> &rhs)
-> BlockMatrix<T, MT>& {
  for(size_t i = 0; i < v_.size(); i++) {
    apply_(~(v_[i]), ~rhs);
  }

  return *this;
}

template< typename T,
          template<typename> class MT >
inline auto BlockMatrix<T, MT>::operator=(const BlockMatrix<T, MT> &rhs)
-> BlockMatrix<T, MT>& {
  n_ = rhs.n_;
  m_ = rhs.m_;
  v_ = rhs.v_;

  return *this;
}

template< typename T,
          template<typename> class MT >
template<typename DT>
inline auto BlockMatrix<T, MT>::operator=(const Matrix<DT> &rhs)
-> BlockMatrix<T, MT>& {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// BlockMatrix Member Function Definitions
//
template<typename T, template<typename> class MT>
inline size_t BlockMatrix<T, MT>::size() const {
  return v_.size();
}
template<typename T, template<typename> class MT>
inline size_t BlockMatrix<T, MT>::capacity() const {
  return v_.capacity();
}

template<typename T, template<typename> class MT>
inline bool BlockMatrix<T, MT>::empty() const {
  return v_.empty();
}

template<typename T, template<typename> class MT>
inline typename BlockMatrix<T, MT>::iterator
BlockMatrix<T, MT>::begin() {
  return v_.begin();
}

template<typename T, template<typename> class MT>
inline typename BlockMatrix<T, MT>::iterator
BlockMatrix<T, MT>::end() {
  return v_.begin();
}

template<typename T, template<typename> class MT>
inline typename BlockMatrix<T, MT>::const_iterator
BlockMatrix<T, MT>::begin() const {
  return v_.begin();
}

template<typename T, template<typename> class MT>
inline typename BlockMatrix<T, MT>::const_iterator
BlockMatrix<T, MT>::end() const {
  return v_.begin();
}

template<typename T, template<typename> class MT>
inline typename BlockMatrix<T, MT>::const_iterator
BlockMatrix<T, MT>::cbegin() const {
  return v_.begin();
}

template<typename T, template<typename> class MT>
inline typename BlockMatrix<T, MT>::const_iterator
BlockMatrix<T, MT>::cend() const {
  return v_.begin();
}

template<typename T, template<typename> class MT>
inline size_t BlockMatrix<T, MT>::nrows() const {
  return n_;
}
template<typename T, template<typename> class MT>
inline size_t BlockMatrix<T, MT>::ncols() const {
  return m_;
}

template<typename T, template<typename> class MT>
inline typename BlockMatrix<T, MT>::vector_type
BlockMatrix<T, MT>::as_vec() const {
  return v_;
}

template<typename T, template<typename> class MT>
inline MT<T> BlockMatrix<T, MT>::as_dense() const {
  size_t nn_, mm_;
  size_t cn_ = 0;
  size_t cm_ = 0;
  size_t tn_ = 0;
  size_t tm_ = 0;
  size_t ts_ = 0;

  for (size_t i = 0; i < n_; i++) {
    tn_ += v_[i*m_].nrows();
  }

  for (size_t j = 0; j < m_; j++) {
    tm_ += v_[j].ncols();
  }

  for (size_t i = 0; i < v_.size(); i++) {
    ts_ += v_[i].size();
  }

  std::vector<T> t_(ts_);

  for(size_t i = 0; i < n_; i++) {
    nn_ = v_[i*m_].nrows();

    for(size_t ii = 0; ii < nn_; ii++) {

      for(size_t j = 0; j < m_; j++) {
        mm_ = v_[i*m_ + j].ncols();

        for(size_t jj = 0; jj < mm_; jj++) {
          t_[(cn_ + ii)*tm_ + cm_ + jj] = v_[i*m_ + j](ii, jj);
        }
        cm_ += mm_;
      }
      cm_ = 0;
    }
    cn_ += nn_;
  }

  return DenseMatrix<T>(tn_, tm_, t_);
}

template<typename T, template<typename> class MT>
inline MT<T> &BlockMatrix<T, MT>::operator[](const size_t pos) {
  return v_[pos];
}

template<typename T, template<typename> class MT>
inline const MT<T> &BlockMatrix<T, MT>::operator[](const size_t pos) const {
  return v_[pos];
}

template<typename T, template<typename> class MT>
inline MT<T>&
BlockMatrix<T, MT>::operator()(const size_t row, const size_t col) {
  return v_[row*m_ + col];
}

template<typename T, template<typename> class MT>
inline const MT<T>&
BlockMatrix<T, MT>::operator()(const size_t row, const size_t col) const {
  return v_[row*m_ + col];
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_BLOCK_BLOCK_HPP
