#ifndef SYMCTRL_MATRIX_DENSE_BASE_HPP
#define SYMCTRL_MATRIX_DENSE_BASE_HPP

#include <vector>

namespace Controls {

// ----------------------------------------------------------------------
// Dense Matrix Base
//
template<typename Derived>
class DenseMatrixBase : public MatrixBase<Derived> {
public:
  virtual ~DenseMatrixBase();

};

template<typename T>
class DenseMatrix : DenseMatrixBase<DenseMatrix<T>> {
private:
  typedef elem_type T;
  
  std::vector<T> v_;

public:
  typedef typename std::vector<T>::iterator iterator;

  DenseMatrix() {}
  ~DenseMatrix() {}

  iterator begin() { return v_.begin(); }
  iterator begin() { return v_.end(); }
};

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_DENSE_BASE_HPP */
