#ifndef SYMCTRL_SYSTEMS_VISITORS_SUBS_HPP
#define SYMCTRL_SYSTEMS_VISITORS_SUBS_HPP

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/statespace.hpp>
#include <symctrl/systems/transferfunction.hpp>
#include <symctrl/systems/visitor.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// SubsVisitor
//
class SubsVisitor : public SystemVisitor<SubsVisitor> {
private:
  const symbolic_t key_, map_;

public:
  SubsVisitor(const symbolic_t key, const symbolic_t map);

  void visit(StateSpace &sys);
  void visit(TransferFunction &sys);

  template<typename DT>
  void visit(System<DT> &sys) {}
};

// ----------------------------------------------------------------------
// SubsVisitor Constructor
//
SubsVisitor::SubsVisitor(const symbolic_t key,
                         const symbolic_t map) :
                         key_(key),
                         map_(map) {
  //
}

// ----------------------------------------------------------------------
// subs
//
template<typename DT>
void subs(System<DT> &sys, const symbolic_t key, const symbolic_t map) {
  SubsVisitor s(key, map);
  sys.accept(s);
}

} // Controls

#endif // SYMCTRL_SYSTEMS_VISITORS_SUBS_HPP
