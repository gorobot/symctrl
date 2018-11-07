#ifndef SYMCTRL_MATRIX_SPARSE_CSR_HPP
#define SYMCTRL_MATRIX_SPARSE_CSR_HPP

#include <vector>

namespace Controls {

// ----------------------------------------------------------------------
// Sparse Matrix (CSR)
//
// Sparse matrix implementation using CSR format.
//
// This class is used to operate on a sparse matrix. It is not efficient to
// construct a CSR matrix incrementally, and more efficient to create a sparse
// matrix using the DOK format and then convert to CSR once all values are set.
template<typename T>
class CSRMatrix : public SparseMatrixBase<CSRMatrix<T>> {
private:
  typedef elem_type T;
  
  std::vector<T> i_;
  std::vector<T> j_;
  std::vector<T> v_;

public:
  typedef typename std::vector<T>::iterator iterator;

  CSRMatrix();
  CSRMatrix(const size_t row, const size_t col);
  CSRMatrix(const size_t row, const size_t col,
            std::vector<size_t> i, std::vector<size_t> j,
            std::vector<T> v);

  template<typename D>
  CSRMatrix(const SparseMatrixBase<D> &m);

  template<typename D>
  const SparseMatrixBase<D>& operator=(const SparseMatrixBase<D> &m);

  ~CSRMatrix() {}

  // void add_scalar(T &c, CSRMatrix<T> &result) const;
  // void add_matrix(CSRMatrix<T> &m, CSRMatrix<T> &result) const;
  //
  // void mul_scalar(T &c, CSRMatrix<T> &result) const;
  // void mul_vector(std::vector<T> &v, CSRMatrix<T> &result) const;
  // void mul_matrix(CSRMatrix<T> &m, CSRMatrix<T> &result) const;

  virtual size_t nnz() const { return v_.size(); };

  iterator begin() { return v_.begin(); }
  iterator end() { return v_.end(); }
};

template<typename T>
CSRMatrix<T>::CSRMatrix() {
  this->row_ = 0;
  this->col_ = 0;
}

template<typename T>
CSRMatrix<T>::CSRMatrix(const size_t row, const size_t col) {
  this->row_ = row;
  this->col_ = col;
}

// Fill a sparse matrix using vectors of indices (i, j) and values.
template<typename T>
CSRMatrix<T>::CSRMatrix(const size_t row, const size_t col,
                     std::vector<size_t> i, std::vector<size_t> j,
                     std::vector<T> v) {
  //
  this->row_ = row;
  this->col_ = col;

  size_t k = 0;
  size_t n = i.size();

  // TODO: Ensure indices and values are all the same size.
  if (i.size() != j.size()) {
    // error
  }

  for(k = 0; k < n; k++) {

  }
}

// template<typename T>
// void CSRMatrix<T>::add_scalar(T &c, CSRMatrix<T> &result) const {
//
// };

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_SPARSE_CSR_HPP */
