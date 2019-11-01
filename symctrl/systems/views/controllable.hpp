#ifndef SYMCTRL_SYSTEMS_VIEWS_CONTROLLABLE_HPP
#define SYMCTRL_SYSTEMS_VIEWS_CONTROLLABLE_HPP

#include <memory>

#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/systems/system.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// Controllable Canonical Form View
//
// The transfer function defined by:
//
// Y(s)   b0*s^(n) + b1*s^(n-1) + ... + bn
// ---- = --------------------------------
// U(s)       s^(n) + a1*s^(n-1) + an
//
// Converts to the state space representation:
//
// .   |  0   1   0  |    | 0 |
// x = |  0   0   1  |x + | 0 |u
//     | -a3 -a2 -a1 |    | 1 |
//
// y = | b3-a3*b0 b2-a2*b0 b1-a1*b0 |x + b0*u
template<typename DT>
class ControllableView {
private:
  System<DT> &ref_;

public:
  explicit inline ControllableView(System<DT> &sys);

  inline Math::SymbolicDense A() const;
  inline Math::SymbolicDense B() const;
  inline Math::SymbolicDense C() const;
  inline Math::SymbolicDense D() const;
};

// ----------------------------------------------------------------------
// ControllableView Constructor
//
template<typename DT>
inline ControllableView::ControllableView(System<DT> &sys) :
                                          ref_(sys) {
}

} // Controls

#endif // SYMCTRL_SYSTEMS_VIEWS_CONTROLLABLE_HPP
