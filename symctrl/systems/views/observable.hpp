#ifndef SYMCTRL_SYSTEMS_VIEWS_OBSERVABLE_HPP
#define SYMCTRL_SYSTEMS_VIEWS_OBSERVABLE_HPP

#include <memory>

#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/systems/system.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// Observable Canonical Form View
//
// The transfer function defined by:
//
// Y(s)   b0*s^(n) + b1*s^(n-1) + ... + bn
// ---- = --------------------------------
// U(s)       s^(n) + a1*s^(n-1) + an
//
// Converts to the state space representation:
//
// .   |  0   0  -a3 |    | b3-a3*b0 |
// x = |  1   0  -a2 |x + | b2-a2*b0 |u
//     |  0   1  -a1 |    | b1-a1*b0 |
//
// y = |  0   0   1  |x + b0*u
template<typename DT>
class ObservableView {
private:
  System<DT> &ref_;

public:
  explicit inline ObservableView(System<DT> &sys);

  inline Math::SymbolicDense A() const;
  inline Math::SymbolicDense B() const;
  inline Math::SymbolicDense C() const;
  inline Math::SymbolicDense D() const;
};

// ----------------------------------------------------------------------
// ObservableView Constructor
//
template<typename DT>
inline ObservableView::ObservableView(System<DT> &sys) :
                                      ref_(sys) {
}

} // Controls

#endif // SYMCTRL_SYSTEMS_VIEWS_OBSERVABLE_HPP
