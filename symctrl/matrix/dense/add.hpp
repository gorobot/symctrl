#ifndef SYMCTRL_MATRIX_DENSE_ADD_HPP
#define SYMCTRL_MATRIX_DENSE_ADD_HPP

namespace Controls {

// ----------------------------------------------------------------------
// Dense Matrix Addition
//
template<typename T1, typename T2>
class AddDense : public DenseMatrixBase<AddDense<T1, T2>> {
public:
  const T1 &A_;
  const T2 &B_;

  AddDense(const T1 &A, const T1 &B) : A_(A), B_(B) {}
};

template<typename T1, typename T2>
const AddDense<T1, T2>
operator+(const DenseMatrixBase<T1> &A, const DenseMatrixBase<T2> &B) {
  return AddDense<T1, T2>(A.get_ref(), B.get_ref());
}

// template<typename T1, typename T2>
// const AddDense<T1, T2>
// operator+(const DenseMatrixBase<T1> &A, const SparseMatrixBase<T2> &B) {
//   return AddDense<T1, T2>(A.get_ref(), B.get_ref());
// }

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_DENSE_ADD_HPP */
