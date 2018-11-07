#ifndef SYMCTRL_VISITOR_HPP
#define SYMCTRL_VISITOR_HPP

#include "mdp.hpp"
#include "state_space.hpp"
#include "transfer_function.hpp"

namespace Controls {

class Visitor {
public:
  virtual ~Visitor() {}

  virtual void visit(StateSpace &m) = 0;
  virtual void visit(MDP &m) = 0;
  virtual void visit(TransferFunction &m) = 0;
};

class MDPVisitor {
public:
  virtual ~MDPVisitor() {}

  virtual void visit(MDP &m) = 0;
};

class SystemVisitor {
public:
  virtual ~SystemVisitor() {}

  virtual void visit(StateSpace &m) = 0;
  virtual void visit(TransferFunction &m) = 0;
};

class StateSpaceVisitor : public Visitor {
public:
  virtual void visit(StateSpace &m) = 0;
};

class TransferFunctionVisitor : public Visitor {
public:
  virtual void visit(TransferFunction &m) = 0;
};

} // Controls

#endif /* end of include guard: SYMCTRL_VISITOR_HPP */
