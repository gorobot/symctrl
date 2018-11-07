#ifndef SYMCTRL_MATRIX_SPARSE_BASE_HPP
#define SYMCTRL_MATRIX_SPARSE_BASE_HPP

namespace Controls {

// Forward declarations.
template<typename T> class CSRMatrix;
template<typename T> class DOKMatrix;
template<typename T> class COOMatrix;

// ----------------------------------------------------------------------
// Sparse Matrix Base
//
template<typename Derived>
class SparseMatrixBase : public MatrixBase<Derived> {
public:
  // typedef typename Derived::iterator iterator;

  virtual ~SparseMatrixBase();

  // size_t nrows() { return this->row_; }
  // size_t ncols() { return this->col_; }
  // size_t size() { return this->row_*this->col_; }

  virtual size_t nnz() const;

  // virtual iterator begin();
  // virtual iterator end();
};

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_SPARSE_BASE_HPP */
