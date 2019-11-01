#ifndef SYMCTRL_MATH_MATRIX_CONSTANT_CONSTANT_HPP
#define SYMCTRL_MATH_MATRIX_CONSTANT_CONSTANT_HPP

#include <vector>

#include <symctrl/math/matrix/dense/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ConstantMatrix
//
template< typename T,
          size_t N,
          size_t M,
          T C >
class ConstantMatrix
    : public Matrix<ConstantMatrix<T, N, M, C>> {
public:
  using type = T;

  using result_type = DenseMatrix<T>;

private:

public:
  ConstantMatrix();

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<T> as_vec() const;
  inline DenseMatrix<T> as_dense() const;

  inline T operator[](const size_t pos);
  inline const T operator[](const size_t pos) const;

  inline T operator()(const size_t row, const size_t col);
  inline const T operator()(const size_t row, const size_t col) const;
};

template<typename T,
         size_t N,
         size_t M,
         T C>
ConstantMatrix<T, N, M, C>::ConstantMatrix() {
  //
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline size_t ConstantMatrix<T, N, M, C>::size() const {
  return N*M;
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline size_t ConstantMatrix<T, N, M, C>::capacity() const {
  return 0;
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline bool ConstantMatrix<T, N, M, C>::empty() const {
  return false;
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline size_t ConstantMatrix<T, N, M, C>::nrows() const {
  return N;
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline size_t ConstantMatrix<T, N, M, C>::ncols() const {
  return M;
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline std::vector<T> ConstantMatrix<T, N, M, C>::as_vec() const {
  std::vector<T> v(N*M, C);

  return v;
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline DenseMatrix<T> ConstantMatrix<T, N, M, C>::as_dense() const {
  std::vector<T> v = (*this).as_vec();

  return DenseMatrix<T>(N, M, v);
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline T ConstantMatrix<T, N, M, C>::operator[](const size_t pos) {
  return C;
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline const T ConstantMatrix<T, N, M, C>::operator[](const size_t pos) const {
  return C;
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline T ConstantMatrix<T, N, M, C>::operator()(const size_t row,
                                                const size_t col) {
  return C;
}

template<typename T,
         size_t N,
         size_t M,
         T C>
inline const T ConstantMatrix<T, N, M, C>::operator()(const size_t row,
                                                      const size_t col) const {
  return C;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_CONSTANT_CONSTANT_HPP
