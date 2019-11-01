#ifndef SYMCTRL_SHIMS_PARSE_HPP
#define SYMCTRL_SHIMS_PARSE_HPP

#include <string>

#include <symengine/parser.h>

#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// parse
//
template<typename T>
inline symbolic_t parse(const T m) {
  return m;
}

template<>
inline symbolic_t parse(const std::string m) {
  return SymEngine::parse(m);
}

template<>
inline symbolic_t parse(const char *m) {
  return SymEngine::parse(m);
}

} // Controls

#endif // SYMCTRL_SHIMS_PARSE_HPP
