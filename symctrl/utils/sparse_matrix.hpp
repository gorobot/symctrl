// Sparse matrix implementation of a 3d sparse matrix.
//
// Uses an unordered map of 3-tuples for the index, and allows for a templated
// type as the value.
#ifndef MODELS_UTILS_SPARSE_MATRIX_HPP
#define MODELS_UTILS_SPARSE_MATRIX_HPP

#include <stddef.h>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Controls {

typedef std::tuple<std::size_t, std::size_t, std::size_t> sparse_key_t;

struct sparse_key_hash : public std::unary_function<sparse_key_t, std::size_t> {
  std::size_t operator()(const sparse_key_t& k) const {
    return std::get<0>(k) ^ std::get<1>(k) ^ std::get<2>(k);
  }
};

struct sparse_key_equal : public std::binary_function<sparse_key_t, sparse_key_t, bool> {
  bool operator()(const sparse_key_t& v0, const sparse_key_t& v1) const {
    return (
      std::get<0>(v0) == std::get<0>(v1) &&
      std::get<1>(v0) == std::get<1>(v1) &&
      std::get<2>(v0) == std::get<2>(v1)
    );
  }
};

template<typename T>
class SparseMatrix {
public:
  SparseMatrix();
  SparseMatrix(std::size_t n);
  SparseMatrix(std::size_t x, std::size_t y, std::size_t z);

  ~SparseMatrix();

  std::vector<std::size_t> size();

  T& operator[](std::size_t n);
  T& operator()(std::size_t x, std::size_t y, std::size_t z);

private:
  std::unordered_map<const sparse_key_t, T, sparse_key_hash, sparse_key_equal> data;

  std::size_t x_dim;
  std::size_t y_dim;
  std::size_t z_dim;
};

// Template definitions cannot be separated from implementations.
template<typename T>
SparseMatrix<T>::SparseMatrix() {}

template<typename T>
SparseMatrix<T>::SparseMatrix(std::size_t n) {
  x_dim = n;
  y_dim = n;
  z_dim = n;
}

template<typename T>
SparseMatrix<T>::SparseMatrix(std::size_t x, std::size_t y, std::size_t z) {
  x_dim = x;
  y_dim = y;
  z_dim = z;
}

template<typename T>
std::vector<std::size_t> SparseMatrix<T>::size() {
  std::vector<std::size_t> v = {x_dim, y_dim, z_dim};
  return v;
}

template<typename T>
SparseMatrix<T>::~SparseMatrix() {}

// Get by subscript.
template<typename T>
T& SparseMatrix<T>::operator[](std::size_t N) {
  std::size_t x = 0;
  std::size_t y = 0;
  std::size_t z = 0;
  // TODO: Convert N to index.
  sparse_key_t key = std::make_tuple(x, y, z);
  return data[key];
}

// Get by index.
template<typename T>
T& SparseMatrix<T>::operator()(std::size_t x, std::size_t y, std::size_t z) {
  sparse_key_t key = std::make_tuple(x, y, z);
  return data[key];
}

} // Controls

#endif /* end of include guard: MODELS_UTILS_SPARSE_MATRIX_HPP */
