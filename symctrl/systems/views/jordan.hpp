#ifndef SYMCTRL_SYSTEMS_VIEWS_JORDAN_HPP
#define SYMCTRL_SYSTEMS_VIEWS_JORDAN_HPP

#include <memory>

#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/systems/system.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// Jordan Canonical Form View
//
template<typename DT>
class JordanView {
private:
  System<DT> &ref_;

public:
  explicit inline JordanView(System<DT> &sys);

  inline Math::SymbolicDense A() const;
  inline Math::SymbolicDense B() const;
  inline Math::SymbolicDense C() const;
  inline Math::SymbolicDense D() const;
};

// ----------------------------------------------------------------------
// JordanView Constructor
//
template<typename DT>
inline JordanView::JordanView(System<DT> &sys) :
                              ref_(sys) {
}

} // Controls

#endif // SYMCTRL_SYSTEMS_VIEWS_JORDAN_HPP
