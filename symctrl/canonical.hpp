#ifndef SYMCTRL_CANONICAL_HPP
#define SYMCTRL_CANONICAL_HPP

#include "visitor.hpp"

namespace Controls {

void ctrb_form(StateSpace &m);
void obsv_form(StateSpace &m);
void jordan_form(StateSpace &m);

// class SomeVisitor : public Visitor {
// private:
//
// public:
//   SomeVisitor() {}
//   ~SomeVisitor() {}
//
//   virtual void visit(SomeClass &m);
// };

// Controllable Canonical Form
class ControllableFormVisitor : public StateSpaceVisitor {
private:

public:
  SomeVisitor() {}
  ~SomeVisitor() {}

  virtual void visit(StateSpace &m);
};

// Observable Canonical Form
class ObservableFormVisitor : public StateSpaceVisitor {
private:

public:
  SomeVisitor() {}
  ~SomeVisitor() {}

  virtual void visit(StateSpace &m);
};

// Jordan Canonical Form
class JordanFormVisitor : public StateSpaceVisitor {
private:

public:
  SomeVisitor() {}
  ~SomeVisitor() {}

  virtual void visit(StateSpace &m);
};


void ctrb_form(StateSpace &m) {
  ControllableFormVisitor s;
  m.accept(s);
}

void obsv_form(StateSpace &m) {
  ObservableFormVisitor s;
  m.accept(s);
}

void jordan_form(StateSpace &m) {
  JordanFormVisitor s;
  m.accept(s);
}

} // Controls

#endif /* end of include guard: SYMCTRL_CANONICAL_HPP */
