#ifndef SYMCTRL_CONTROL_MODEL_HPP
#define SYMCTRL_CONTROL_MODEL_HPP

namespace Controls {

enum ModelDataType {
  Continuous,
  Discrete
};

class ControlModel {
public:
  virtual ~ControlModel() {};
};

} // Controls

#endif /* end of include guard: SYMCTRL_CONTROL_MODEL_HPP */
