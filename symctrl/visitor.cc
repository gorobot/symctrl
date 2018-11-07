#include "visitor.hpp"

namespace Controls {

void MDP::accept(MDPVisitor &visitor) {
  visitor.visit(*this);
}

void StateSpace::accept(SystemVisitor &visitor) {
  visitor.visit(*this);
}

void TransferFunction::accept(SystemVisitor &visitor) {
  visitor.visit(*this);
}

} // Controls
