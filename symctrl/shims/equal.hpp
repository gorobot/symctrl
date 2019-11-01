#ifndef SYMCTRL_SHIMS_EQUAL_HPP
#define SYMCTRL_SHIMS_EQUAL_HPP

#include <symengine/basic.h>

#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// equal
//
inline bool equal(const symbolic_t lhs, const symbolic_t rhs) {
  return SymEngine::eq(*lhs, *rhs);
}

inline bool operator==(const symbolic_t lhs, const symbolic_t rhs) {
  return equal(lhs, rhs);
}

} // Controls

#endif // SYMCTRL_SHIMS_EQUAL_HPP
