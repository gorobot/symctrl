#ifndef SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP

#include <ostream>

#include <symctrl/assert.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Symbolic
//
template<typename DT>
class Symbolic {
public:
  inline DT &operator~();
  inline const DT &operator~() const;
};

// ----------------------------------------------------------------------
// Symbolic Member Function Definitions
//
template<typename DT>
inline DT &Symbolic<DT>::operator~() {
  return *static_cast<DT *>(this);
}

template<typename DT>
inline const DT &Symbolic<DT>::operator~() const {
  return *static_cast<const DT *>(this);
}

// ----------------------------------------------------------------------
// Ostream Operator
//
template<typename DT>
std::ostream &operator<<(std::ostream &os, const Symbolic<DT> &m) {
  os << (~m).as_str();
  return os;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
