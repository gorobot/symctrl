#ifndef SYMCTRL_SHIMS_MAKE_UNIQUE_HPP
#define SYMCTRL_SHIMS_MAKE_UNIQUE_HPP

#include <memory>

namespace Controls {

// ----------------------------------------------------------------------
// make_unique
//
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

} // Controls

#endif // SYMCTRL_SHIMS_MAKE_UNIQUE_HPP
