#ifndef SYMCTRL_CONTROLLERS_GAIN_GAIN_HPP
#define SYMCTRL_CONTROLLERS_GAIN_GAIN_HPP

namespace Controls {

// ----------------------------------------------------------------------
// GainController
//
class GainController : public Controller<GainController> {
public:
  inline void apply(StateSpace &sys);
};

} // Controls

#endif // SYMCTRL_CONTROLLERS_GAIN_GAIN_HPP
