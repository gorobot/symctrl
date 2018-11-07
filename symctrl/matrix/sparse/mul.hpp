#ifndef SYMCTRL_MATRIX_SPARSE_MUL_HPP
#define SYMCTRL_MATRIX_SPARSE_MUL_HPP

namespace Controls {

// ----------------------------------------------------------------------
// Sparse Matrix Multiplication
//
template<typename T1, typename T2>
class MulSparse : public SparseMatrixBase<MulSparse<T1, T2>> {
public:
  const T1 &A_;
  const T2 &B_;

  MulSparse(const T1 &A, const T1 &B) : A_(A), B_(B) {}
};

template<typename T1, typename T2>
const MulSparse<T1, T2>
operator*(const SparseMatrixBase<T1> &A, const SparseMatrixBase<T2> &B) {
  return MulSparse<T1, T2>(A.get_ref(), B.get_ref());
}

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_SPARSE_MUL_HPP */
