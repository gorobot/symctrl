#ifndef SYMCTRL_MATRIX_SPARSE_DOK_HPP
#define SYMCTRL_MATRIX_SPARSE_DOK_HPP

#include <map>
#include <tuple>
#include <vector>

namespace Controls {

// ----------------------------------------------------------------------
// Sparse Matrix (DOK)
//
// Sparse matrix implementation using DOK (dictionary of keys) format.
//
// This class is used to construct a sparse matrix, but is not as efficient as
// the CSR matrix for operations. Large sparse matrices should be converted to
// CSR format before performing operations on them.
template<typename T>
class DOKMatrix : public SparseMatrixBase<DOKMatrix<T>> {
private:
  typedef elem_type T;

  typedef std::map<std::tuple<size_t, size_t>, T> dok_t;
  dok_t d_;

public:
  typedef typename dok_t::iterator iterator;

  DOKMatrix();
  DOKMatrix(const size_t row, const size_t col);
  DOKMatrix(const size_t row, const size_t col,
            std::vector<size_t> i, std::vector<size_t> j,
            std::vector<T> v);

  template<typename D>
  DOKMatrix(const SparseMatrixBase<D> &m);

  template<typename D>
  const SparseMatrixBase<D>& operator=(const SparseMatrixBase<D> &m);

  ~DOKMatrix() {}

  virtual T get(size_t i, size_t j) const;
  virtual T get(std::tuple<size_t, size_t> t) const;
  virtual void set(size_t i, size_t j, T v) const;
  virtual void set(std::tuple<size_t, size_t> t, T v) const;

  // // Matrix addition.
  // template<typename T1, typename T2>
  // const AddSparse<T1, T2>
  // operator+(const SparseMatrixBase<T1> &A, const SparseMatrixBase<T2> &B) {
  //   return AddSparse<T1, T2>(A.get_ref(), B.get_ref());
  // }
  //
  // // Matrix multiplication.
  // template<typename T1, typename T2>
  // const MulSparse<T1, T2>
  // operator+(const SparseMatrixBase<T1> &A, const SparseMatrixBase<T2> &B) {
  //   return MulSparse<T1, T2>(A.get_ref(), B.get_ref());
  // }

  // void add_scalar(T &c, DOKMatrix<T> &result) const;
  // void add_matrix(DOKMatrix<T> &m, DOKMatrix<T> &result) const;
  //
  // void mul_scalar(T &c, DOKMatrix<T> &result) const;
  // void mul_vector(std::vector<T> &v, DOKMatrix<T> &result) const;
  // void mul_matrix(DOKMatrix<T> &m, DOKMatrix<T> &result) const;

  virtual size_t nnz() const { return d_.size(); };

  iterator begin() { return d_.begin(); }
  iterator end() { return d_.end(); }
};

template<typename T>
T DOKMatrix<T>::get(size_t i, size_t j) const {
  DOKMatrix<T>::get(std::make_tuple(i, j));
}

template<typename T>
T DOKMatrix<T>::get(std::tuple<size_t, size_t> t) const {
  return d_[t];
}

template<typename T>
void DOKMatrix<T>::set(size_t i, size_t j, T v) const {
  DOKMatrix<T>::set(std::make_tuple(i, j), v);
}

template<typename T>
void DOKMatrix<T>::set(std::tuple<size_t, size_t> t, T v) const {
  d_[t] = v;
}

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_SPARSE_DOK_HPP */
