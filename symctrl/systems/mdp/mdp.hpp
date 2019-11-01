#ifndef SYMCTRL_SYSTEMS_MDP_MDP_HPP
#define SYMCTRL_SYSTEMS_MDP_MDP_HPP

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/functor/functor.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// MDP
//
class MDP : public System<MDP> {
private:
  // SetType state_space_;
  // SetType input_space_;

  TransitionFunction *transition_kernel_;
  CostFunction *cost_function_;

  double gamma_;

public:
  // MDP(SetType state_space,
  //     SetType input_space,
  //     TransitionFunction *T,
  //     CostFunction *R,
  //     const double gamma) :
  //     state_space_(state_space),
  //     input_space_(input_space),
  //     transition_kernel_(T),
  //     cost_function_(R),
  //     gamma_(gamma) {}

  // ~MDP() {}

  // size_t n_states() const { return nstates_; }
  // size_t n_inputs() const { return ninputs_; }
  //
  // void set_transition_function(TransitionFunction *T);
  // TransitionFunction *get_transition_function();
  //
  // void set_cost_function(CostFunction &R);
  // CostFunction &get_cost_function();
  //
  // void set_gamma(const double arg) {
  //   gamma_ = (arg > 0 ? (arg < 1 ? arg : 1) : 0);
  // }
  // double get_gamma() { return gamma_; }

  inline void accept(Visitor &visitor);
};

} // Controls

#endif // SYMCTRL_SYSTEMS_MDP_MDP_HPP
