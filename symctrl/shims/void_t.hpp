#ifndef SYMCTRL_SHIMS_VOID_T_HPP
#define SYMCTRL_SHIMS_VOID_T_HPP

namespace Controls {

template<typename ...Ts>
struct make_void {
  typedef void type;
};

template<typename ...Ts>
using void_t = typename make_void<Ts...>::type;

} // Controls

#endif // SYMCTRL_SHIMS_VOID_T_HPP
