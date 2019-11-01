#ifndef SYMCTRL_MATH_MATRIX_MATRIX_HPP
#define SYMCTRL_MATH_MATRIX_MATRIX_HPP

#include <iomanip>
#include <ostream>
#include <type_traits>
#include <vector>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Matrix
//
template<typename DT>
class Matrix {
public:
  inline DT &operator~() {
    return *static_cast<DT *>(this);
  }
  inline const DT &operator~() const {
    return *static_cast<const DT *>(this);
  }
};

// ----------------------------------------------------------------------
// Matrix DT Functions
//
template<typename DT>
size_t size(Matrix<DT> &m) {
  return (~m).size();
}

template<typename DT>
size_t capacity(Matrix<DT> &m) {
  return (~m).capacity();
}

template<typename DT>
bool empty(Matrix<DT> &m) {
  return (~m).empty();
}

template<typename DT>
size_t nrows(Matrix<DT> &m) {
  return (~m).nrows();
}

template<typename DT>
size_t ncols(Matrix<DT> &m) {
  return (~m).ncols();
}

// ----------------------------------------------------------------------
// Stream Output
//
// template<template<typename> class DT, typename T>
// inline auto operator<<(std::ostream& os, const Matrix<DT<T>> &m)
// -> typename std::enable_if<std::is_scalar<T>::value, std::ostream&>::type {
//   for(size_t i = 0; i < (~m).nrows(); i++) {
//     os << "| ";
//     for(size_t j = 0; j < (~m).ncols(); j++) {
//       os << std::setw(12) << (~m)[i*(~m).ncols() + j] << " ";
//     }
//     os << "|" << '\n';
//   }
//   return os;
// }


} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_MATRIX_HPP
