#ifndef SYMCTRL_MATH_MATRIX_CONSTANT_IDENTITY_HPP
#define SYMCTRL_MATH_MATRIX_CONSTANT_IDENTITY_HPP

#include <vector>

#include <symctrl/math/matrix/dense/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Identity
//
template<typename T,
         size_t N,
         size_t M = N>
class Identity
    : public Matrix<Identity<T, N, M>> {
public:
  using type = T;

  using result_type = DenseMatrix<T>;

private:

public:
  Identity();

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
         size_t M>
Identity<T, N, M>::Identity() {
  //
}

template<typename T,
         size_t N,
         size_t M>
inline size_t Identity<T, N, M>::size() const {
  return N*M;
}

template<typename T,
         size_t N,
         size_t M>
inline size_t Identity<T, N, M>::capacity() const {
  return 0;
}

template<typename T,
         size_t N,
         size_t M>
inline bool Identity<T, N, M>::empty() const {
  return false;
}

template<typename T,
         size_t N,
         size_t M>
inline size_t Identity<T, N, M>::nrows() const {
  return N;
}

template<typename T,
         size_t N,
         size_t M>
inline size_t Identity<T, N, M>::ncols() const {
  return M;
}

template<typename T,
         size_t N,
         size_t M>
inline std::vector<T> Identity<T, N, M>::as_vec() const {
  std::vector<T> v(N*M, T(0));
  for(size_t i = 0; i < std::min(N, M); i++) {
    v[i*M + i] = T(1);
  }

  return v;
}

template<typename T,
         size_t N,
         size_t M>
inline DenseMatrix<T> Identity<T, N, M>::as_dense() const {
  std::vector<T> v = (*this).as_vec();

  return DenseMatrix<T>(N, M, v);
}

template<typename T,
         size_t N,
         size_t M>
inline T Identity<T, N, M>::operator[](const size_t pos) {
  return (pos%(M + 1) == 0) ? T(1) : T(0);
}

template<typename T,
         size_t N,
         size_t M>
inline const T Identity<T, N, M>::operator[](const size_t pos) const {
  return (pos%(M + 1) == 0) ? T(1) : T(0);
}

template<typename T,
         size_t N,
         size_t M>
inline T Identity<T, N, M>::operator()(const size_t row,
                                       const size_t col) {
  return (row == col) ? T(1) : T(0);
}

template<typename T,
         size_t N,
         size_t M>
inline const T Identity<T, N, M>::operator()(const size_t row,
                                             const size_t col) const {
  return (row == col) ? T(1) : T(0);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_CONSTANT_IDENTITY_HPP
