#ifndef SYMCTRL_ASSERT_HPP
#define SYMCTRL_ASSERT_HPP

#include <cassert>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Assert Macro
//
#ifndef SYMCTRL_ASSERT
#define SYMCTRL_ASSERT(expr) assert((expr));
#endif

// ----------------------------------------------------------------------
// Static Assert Macro
//
#ifndef SYMCTRL_STATIC_ASSERT
#define SYMCTRL_STATIC_ASSERT(expr, msg) static_assert(expr, msg);
#endif

// ----------------------------------------------------------------------
// Debugging
//
// Uncomment this line to enable debugging.
#define SYMCTRL_DEBUG_OUT

#ifdef SYMCTRL_DEBUG_OUT
#define SYMCTRL_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define SYMCTRL_DEBUG(msg) // msg
#endif

} // Math
} // Controls

#endif // SYMCTRL_ASSERT_HPP
