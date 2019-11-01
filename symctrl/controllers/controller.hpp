#ifndef SYMCTRL_CONTROLLERS_CONTROLLER_HPP
#define SYMCTRL_CONTROLLERS_CONTROLLER_HPP

#include <vector>

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/statespace/statespace.hpp>
#include <symctrl/systems/transferfunction/transferfunction.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// BaseController
//
class BaseController {
public:
  virtual ~BaseController() {}
};

// ----------------------------------------------------------------------
// Controller Class
//
template<typename DT>
class Controller : public BaseController {
public:
  inline DT &operator~() {
    return *static_cast<DT *>(this);
  }
  inline const DT &operator~() const {
    return *static_cast<const DT *>(this);
  }

  inline void accept(Visitor &visitor);
};

// ----------------------------------------------------------------------
// Controller Member Function Definitions
//
template<typename DT>
inline void Controller<DT>::accept(Visitor &visitor) {
  (*this).operator~().accept(visitor);
}

// ----------------------------------------------------------------------
// apply
//
template<typename DT, typename CT>
inline void apply_(System<DT> &lhs, const Controller<CT> &rhs) {
  (~lhs).apply_(~rhs);
}

// ----------------------------------------------------------------------
// StateSpace apply_
//
template<typename CT>
inline void StateSpace::apply_(Controller<CT> &controller) {
  controller.apply(*this);
}

// ----------------------------------------------------------------------
// TransferFunction apply_
//
template<typename CT>
inline void TransferFunction::apply_(Controller<CT> &controller) {
  controller.apply(*this);
}

} // Controls

#endif // SYMCTRL_CONTROLLERS_CONTROLLER_HPP
