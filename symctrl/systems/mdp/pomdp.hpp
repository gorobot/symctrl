#ifndef SYMCTRL_SYSTEMS_MDP_POMDP_HPP
#define SYMCTRL_SYSTEMS_MDP_POMDP_HPP

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/functor/functor.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// POMDP
//
class POMDP : public System<POMDP> {
private:
  TransitionFunction *observation_kernel_;

public:
  // POMDP(SetType state_space,
  //       SetType input_space,
  //       TransitionFunction *T,
  //       CostFunction *R,
  //       TransitionFunction *Ob,
  //       const double gamma) :
  //       MDP{state_space, input_space, T, R, gamma},
  //       observation_kernel_(Ob) {}

  // ~POMDP() {}

  inline void accept(Visitor &visitor);
};

} // Controls

#endif // SYMCTRL_SYSTEMS_MDP_POMDP_HPP
