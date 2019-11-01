#ifndef SYMCTRL_MATH_MATRIX_STATIC_VECTOR_HPP
#define SYMCTRL_MATH_MATRIX_STATIC_VECTOR_HPP

#include <algorithm>
#include <array>
#include <initializer_list>
#include <vector>

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/vector/vector.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// StaticVector
//
template<typename T, size_t N, size_t M = 1>
class StaticVector : public Matrix<StaticVector<T, N, M>> {
public:
  using type = T;

  using result_type = Vector<T>;

private:
  std::array<T, N*M> v_;

public:
  explicit inline StaticVector();
  explicit inline StaticVector(std::initializer_list<T> v);
  explicit inline StaticVector(const std::vector<T> &v);
  inline StaticVector(const Vector<T> &m);
  inline StaticVector(const StaticVector<T, N, M> &m);

  template<typename DT>
  inline StaticVector(const Matrix<DT> &m);

  inline StaticVector<T, N, M> &operator=(const T &rhs);
  inline StaticVector<T, N, M> &operator=(std::initializer_list<T> rhs);
  inline StaticVector<T, N, M> &operator=(const std::vector<T> &rhs);
  inline StaticVector<T, N, M> &operator=(const Vector<T> &rhs);
  inline StaticVector<T, N, M> &operator=(const StaticVector<T, N, M> &rhs);

  template<typename DT>
  inline StaticVector<T, N, M> &operator=(const Matrix<DT> &rhs);

  inline StaticVector<T, N, M> &operator+=(const T &rhs);
  inline StaticVector<T, N, M> &operator-=(const T &rhs);
  inline StaticVector<T, N, M> &operator*=(const T &rhs);
  inline StaticVector<T, N, M> &operator/=(const T &rhs);

  template<typename DT>
  inline StaticVector<T, N, M> &operator+=(const Matrix<DT> &rhs);
  template<typename DT>
  inline StaticVector<T, N, M> &operator-=(const Matrix<DT> &rhs);

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

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline typename std::array<T, N*M>::iterator begin();
  inline typename std::array<T, N*M>::iterator end();
  inline typename std::array<T, N*M>::const_iterator begin() const;
  inline typename std::array<T, N*M>::const_iterator end() const;
  inline typename std::array<T, N*M>::const_iterator cbegin() const;
  inline typename std::array<T, N*M>::const_iterator cend() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<T> as_vec() const;

  inline T &operator[](const size_t pos);
  inline const T &operator[](const size_t pos) const;

  inline T &operator()(const size_t row, const size_t col);
  inline const T &operator()(const size_t row, const size_t col) const;

  SYMCTRL_STATIC_ASSERT(N != 0 && M != 0,
    "StaticVector must have N != 0 && M != 0");
  SYMCTRL_STATIC_ASSERT(N == 1 || M == 1,
    "StaticVector must have N == 1 || M == 1");
};

// ----------------------------------------------------------------------
// StaticVector Constructor
//
template<typename T, size_t N, size_t M>
StaticVector<T, N, M>::StaticVector() : v_() {
  v_ = std::array<T, N*M>();
}

template<typename T, size_t N, size_t M>
StaticVector<T, N, M>::StaticVector(std::initializer_list<T> v) : v_() {
  SYMCTRL_ASSERT(v.size() == N*M);
  std::copy(v.begin(), v.end(), v_.begin());
}

template<typename T, size_t N, size_t M>
StaticVector<T, N, M>::StaticVector(const std::vector<T> &v) : v_() {
  SYMCTRL_ASSERT(v.size() == N*M);
  for(size_t i = 0; i < N*M; i++) {
    v_[i] = v[i];
  }
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M>::StaticVector(const Vector<T> &m) : v_() {
  SYMCTRL_ASSERT(N == (~m).nrows());
  SYMCTRL_ASSERT(M == (~m).ncols());
  for(size_t i = 0; i < N*M; i++) {
    v_[i] = (~m)[i];
  }
}

template<typename T, size_t N, size_t M>
StaticVector<T, N, M>::StaticVector(const StaticVector<T, N, M> &m) : v_() {
  for(size_t i = 0; i < N*M; i++) {
    v_[i] = (~m)[i];
  }
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline StaticVector<T, N, M>::StaticVector(const Matrix<DT> &m) : v_() {
  SYMCTRL_ASSERT(N == (~m).nrows());
  SYMCTRL_ASSERT(M == (~m).ncols());
  apply_(*this, ~m);
}

// ----------------------------------------------------------------------
// StaticVector Assignment Operator
//
template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator=(std::initializer_list<T> rhs) {
  SYMCTRL_ASSERT(rhs.size() == N*M);
  std::copy(rhs.begin(), rhs.end(), v_.begin());

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator=(const std::vector<T> &rhs) {
  SYMCTRL_ASSERT(rhs.size() == N*M);
  for(size_t i = 0; i < N*M; i++) {
    v_[i] = rhs[i];
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator=(const Vector<T> &rhs) {
  SYMCTRL_ASSERT(rhs.size() == N*M);
  apply_(*this, ~rhs);

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator=(const StaticVector<T, N, M> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator=(const Matrix<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// StaticVector Member Function Definitions
//
template<typename T, size_t N, size_t M>
inline size_t StaticVector<T, N, M>::size() const {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline size_t StaticVector<T, N, M>::capacity() const {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline bool StaticVector<T, N, M>::empty() const {
  return v_.empty();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::iterator
StaticVector<T, N, M>::begin() {
  return v_.begin();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::iterator
StaticVector<T, N, M>::end() {
  return v_.end();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::const_iterator
StaticVector<T, N, M>::begin() const {
  return v_.begin();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::const_iterator
StaticVector<T, N, M>::end() const {
  return v_.end();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::const_iterator
StaticVector<T, N, M>::cbegin() const {
  return v_.cbegin();
}

template<typename T, size_t N, size_t M>
inline typename std::array<T, N*M>::const_iterator
StaticVector<T, N, M>::cend() const {
  return v_.cend();
}

template<typename T, size_t N, size_t M>
inline size_t StaticVector<T, N, M>::nrows() const {
  return N;
}

template<typename T, size_t N, size_t M>
inline size_t StaticVector<T, N, M>::ncols() const {
  return M;
}

template<typename T, size_t N, size_t M>
inline std::vector<T> StaticVector<T, N, M>::as_vec() const {
  std::vector<T> v(v_.size());
  std::copy(v_.begin(), v_.end(), v.begin());
  return v;
}

template<typename T, size_t N, size_t M>
inline T &StaticVector<T, N, M>::operator[](const size_t pos) {
  return v_[pos];
}

template<typename T, size_t N, size_t M>
inline const T &StaticVector<T, N, M>::operator[](const size_t pos) const {
  return v_[pos];
}

template<typename T, size_t N, size_t M>
inline T &StaticVector<T, N, M>::operator()(const size_t row,
                                            const size_t col) {
  return v_[row*M + col];
}

template<typename T, size_t N, size_t M>
inline const T &StaticVector<T, N, M>::operator()(const size_t row,
                                                  const size_t col) const {
  return v_[row*M + col];
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_STATIC_VECTOR_HPP
