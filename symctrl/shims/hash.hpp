#ifndef SYMCTRL_SHIMS_HASH_HPP
#define SYMCTRL_SHIMS_HASH_HPP

#include <functional>
#include <string>

namespace Controls {

// ----------------------------------------------------------------------
// hash_t
//
using hash_t = size_t;

// ----------------------------------------------------------------------
// hash
//
template<typename T>
using hash_f = std::hash<T>;

// ----------------------------------------------------------------------
// hash_string
//
using hash_string = std::hash<std::string>;

} // Controls

#endif // SYMCTRL_SHIMS_HASH_HPP
