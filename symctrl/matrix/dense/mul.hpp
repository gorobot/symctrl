#ifndef SYMCTRL_MATRIX_DENSE_MUL_HPP
#define SYMCTRL_MATRIX_DENSE_MUL_HPP

namespace Controls {

// ----------------------------------------------------------------------
// Dense Matrix Multiplication
//
template<typename T1, typename T2>
class MulDense : public DenseMatrixBase<MulDense<T1, T2>> {
public:
  const T1 &A_;
  const T2 &B_;

  MulDense(const T1 &A, const T1 &B) : A_(A), B_(B) {}
};

template<typename T1, typename T2>
const MulDense<T1, T2>
operator*(const DenseMatrixBase<T1> &A, const DenseMatrixBase<T2> &B) {
  return MulDense<T1, T2>(A.get_ref(), B.get_ref());
}

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_DENSE_MUL_HPP */
