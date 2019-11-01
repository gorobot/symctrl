#ifndef SYMCTRL_SYSTEMS_HYBRID_DTSHS_HPP
#define SYMCTRL_SYSTEMS_HYBRID_DTSHS_HPP

#include <map>
#include <tuple>
#include <vector>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>
#include <symengine/sets.h>

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/functor/functor.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {

class DTSHS : public System<DTSHS> {
private:
  // SetType discrete_state_space_;
  // SetType input_space_;
  //
  // std::map<std::vector<double>, SetType> n_;

  TransitionFunction *discrete_transition_kernel_;
  TransitionFunction *continuous_transition_kernel_;
  TransitionFunction *reset_transition_kernel_;

public:
  
  inline void accept(Visitor &visitor);
};

} // Controls

#endif // SYMCTRL_SYSTEMS_HYBRID_DTSHS_HPP
