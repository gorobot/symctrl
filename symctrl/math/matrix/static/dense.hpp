#ifndef SYMCTRL_MATH_MATRIX_STATIC_DENSE_HPP
#define SYMCTRL_MATH_MATRIX_STATIC_DENSE_HPP

#include <algorithm>
#include <array>
#include <initializer_list>
#include <iomanip>
#include <type_traits>
#include <vector>

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/dense/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// StaticDense
//
template<typename T, size_t N, size_t M>
class StaticDense : public Matrix<StaticDense<T, N, M>> {
public:
  using type = T;

  using result_type = DenseMatrix<T>;

private:
  std::array<T, N*M> v_;

public:
  explicit inline StaticDense();
  explicit inline StaticDense(std::initializer_list<T> v);
  explicit inline StaticDense(const std::vector<T> &v);
  inline StaticDense(const DenseMatrix<T> &m);
  inline StaticDense(const StaticDense<T, N, M> &m);

  template<typename DT>
  inline StaticDense(const Matrix<DT> &m);

  inline StaticDense<T, N, M> &operator=(const T &rhs);
  inline StaticDense<T, N, M> &operator=(std::initializer_list<T> rhs);
  inline StaticDense<T, N, M> &operator=(const std::vector<T> &rhs);
  inline StaticDense<T, N, M> &operator=(const DenseMatrix<T> &rhs);
  inline StaticDense<T, N, M> &operator=(const StaticDense<T, N, M> &rhs);

  template<typename DT>
  inline StaticDense<T, N, M> &operator=(const Matrix<DT> &rhs);

  inline StaticDense<T, N, M> &operator+=(const T &rhs);
  inline StaticDense<T, N, M> &operator-=(const T &rhs);
  inline StaticDense<T, N, M> &operator*=(const T &rhs);
  inline StaticDense<T, N, M> &operator/=(const T &rhs);

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

  static inline constexpr size_t size();
  static inline constexpr size_t capacity();

  inline bool empty() const;

  inline typename std::array<T, N*M>::iterator begin();
  inline typename std::array<T, N*M>::iterator end();
  inline typename std::array<T, N*M>::const_iterator begin() const;
  inline typename std::array<T, N*M>::const_iterator end() const;
  inline typename std::array<T, N*M>::const_iterator cbegin() const;
  inline typename std::array<T, N*M>::const_iterator cend() const;

  static inline constexpr size_t nrows();
  static inline constexpr size_t ncols();

  inline std::vector<T> as_vec() const;

  inline T &operator[](const size_t pos);
  inline const T &operator[](const size_t pos) const;

  inline T &operator()(const size_t row, const size_t col);
  inline const T &operator()(const size_t row, const size_t col) const;

  SYMCTRL_STATIC_ASSERT(N != 0 && M != 0,
    "StaticDense must have N != 0 && M != 0");
};

// ----------------------------------------------------------------------
// StaticDense Constructor
//
template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>::StaticDense() : v_() {
  v_ = std::array<T, N*M>();
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>::StaticDense(std::initializer_list<T> v) : v_() {
  SYMCTRL_ASSERT(v.size() == N*M);
  std::copy(v.begin(), v.end(), v_.begin());
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>::StaticDense(const std::vector<T> &v) : v_() {
  SYMCTRL_ASSERT(v.size() == N*M);
  for(size_t i = 0; i < N*M; i++) {
    v_[i] = v[i];
  }
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>::StaticDense(const DenseMatrix<T> &m) : v_() {
  SYMCTRL_ASSERT(N == (~m).nrows());
  SYMCTRL_ASSERT(M == (~m).ncols());
  for(size_t i = 0; i < N*M; i++) {
    v_[i] = (~m)[i];
  }
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>::StaticDense(const StaticDense<T, N, M> &m) : v_() {
  for(size_t i = 0; i < N*M; i++) {
    v_[i] = (~m)[i];
  }
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline StaticDense<T, N, M>::StaticDense(const Matrix<DT> &m) : v_() {
  SYMCTRL_ASSERT(N == (~m).nrows());
  SYMCTRL_ASSERT(M == (~m).ncols());
  apply_(*this, ~m);
}

// ----------------------------------------------------------------------
// StaticDense Assignment Operator
//
template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>&
StaticDense<T, N, M>::operator=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>&
StaticDense<T, N, M>::operator=(std::initializer_list<T> rhs) {
  SYMCTRL_ASSERT(rhs.size() == N*M);
  std::copy(rhs.begin(), rhs.end(), v_.begin());

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>&
StaticDense<T, N, M>::operator=(const std::vector<T> &rhs) {
  SYMCTRL_ASSERT(rhs.size() == N*M);
  for(size_t i = 0; i < N*M; i++) {
    v_[i] = rhs[i];
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>&
StaticDense<T, N, M>::operator=(const DenseMatrix<T> &rhs) {
  SYMCTRL_ASSERT((~rhs).nrows() == N);
  SYMCTRL_ASSERT((~rhs).ncols() == M);
  apply_(*this, ~rhs);

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M>&
StaticDense<T, N, M>::operator=(const StaticDense<T, N, M> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline StaticDense<T, N, M>&
StaticDense<T, N, M>::operator=(const Matrix<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// StaticDense Member Function Definitions
//
template<typename T, size_t N, size_t M>
inline constexpr size_t StaticDense<T, N, M>::size() {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline constexpr size_t StaticDense<T, N, M>::capacity() {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline bool StaticDense<T, N, M>::empty() const {
  return v_.empty();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::iterator
StaticDense<T, N, M>::begin() {
  return v_.begin();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::iterator
StaticDense<T, N, M>::end() {
  return v_.end();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::const_iterator
StaticDense<T, N, M>::begin() const {
  return v_.begin();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::const_iterator
StaticDense<T, N, M>::end() const {
  return v_.end();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::const_iterator
StaticDense<T, N, M>::cbegin() const {
  return v_.cbegin();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::const_iterator
StaticDense<T, N, M>::cend() const {
  return v_.cend();
}

template<typename T, size_t N, size_t M>
inline constexpr size_t StaticDense<T, N, M>::nrows() {
  return N;
}

template<typename T, size_t N, size_t M>
inline constexpr size_t StaticDense<T, N, M>::ncols() {
  return M;
}

template<typename T, size_t N, size_t M>
inline std::vector<T> StaticDense<T, N, M>::as_vec() const {
  std::vector<T> v(v_.size());
  std::copy(v_.begin(), v_.end(), v.begin());
  return v;
}

template<typename T, size_t N, size_t M>
inline T &StaticDense<T, N, M>::operator[](const size_t pos) {
  return v_[pos];
}

template<typename T, size_t N, size_t M>
inline const T &StaticDense<T, N, M>::operator[](const size_t pos) const {
  return v_[pos];
}

template<typename T, size_t N, size_t M>
inline T &StaticDense<T, N, M>::operator()(const size_t row,
                                           const size_t col) {
  return v_[row*M + col];
}

template<typename T, size_t N, size_t M>
inline const T &StaticDense<T, N, M>::operator()(const size_t row,
                                                 const size_t col) const {
  return v_[row*M + col];
}

// ----------------------------------------------------------------------
// Stream Output
//
// template<typename T, size_t N, size_t M>
// inline auto operator<<(std::ostream& os, const StaticDense<T, N, M> &m)
// -> typename std::enable_if<std::is_scalar<T>::value, std::ostream&>::type {
//   typename std::vector<const T>::iterator result;
//   result = std::max_element((~m).begin(), (~m).end());
//   int width = std::to_string(*result).length();
//
//   for(size_t i = 0; i < (~m).nrows(); i++) {
//     os << "| ";
//     for(size_t j = 0; j < (~m).ncols(); j++) {
//       os << std::setw(width) << (~m)[i*(~m).ncols() + j] << " ";
//     }
//
//     if(i == 0) {
//       os << "| [" << (~m).nrows() << " x " << (~m).ncols() << "]" << '\n';
//     }
//     else {
//       os << "|" << '\n';
//     }
//   }
//   return os;
// }

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_STATIC_DENSE_HPP
