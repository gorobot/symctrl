#ifndef SYMCTRL_MATH_SYMBOLIC_VISITOR_VISITOR_HPP
#define SYMCTRL_MATH_SYMBOLIC_VISITOR_VISITOR_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/number/number.hpp>
#include <symctrl/math/symbolic/variable/variable.hpp>
#include <symctrl/math/symbolic/sym/sym.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BaseSymbolicVisitor
//
class BaseSymbolicVisitor {
public:
  virtual ~BaseSymbolicVisitor() {}

  virtual void visit(const BaseSymbolic &m) = 0;
  // virtual void visit(const BaseSymbolic &m) {
  //   SYMCTRL_DEBUG("Inside the BaseSymbolicVisitor visit function.");
  // }
  // template<typename DT>
  // void visit(const Symbolic<DT> &m);
};

// ----------------------------------------------------------------------
// SymbolicVisitor
//
template<typename Derived, typename Base = BaseSymbolicVisitor>
// template<typename DT>
class SymbolicVisitor
    : public Base {
private:

public:
  // virtual ~SymbolicVisitor() {};

  virtual void visit(const BaseSymbolic &m) {
    SYMCTRL_DEBUG("Inside the SystemVisitor for BaseSymbolic visit function.");
  }

  template<typename DT>
  void visit(const Symbolic<DT> &m) {
    SYMCTRL_DEBUG("Inside the SymbolicVisitor visit function.");
    static_cast<Derived &>(*this).visit(m);
  }
};

// ----------------------------------------------------------------------
// Accept Declarations
//
// template<typename DT>
// void Symbolic<DT>::accept(BaseSymbolicVisitor &visitor) {
//   SYMCTRL_DEBUG("Inside the accept function.");
//   visitor.visit(*this);
// }
// template<typename DT>
// void Symbolic<DT>::accept(BaseSymbolicVisitor &visitor) const {
//   SYMCTRL_DEBUG("Inside the (const) accept function.");
//   visitor.visit(*this);
// }

// template<typename T>
// void Number<T>::accept(SymbolicVisitor &visitor) {
//   visitor.visit(*this);
// }
//
// void Variable::accept(SymbolicVisitor &visitor) {
//   visitor.visit(*this);
// }

// void sym_t::accept(SymbolicVisitor &visitor) {
//   // ptr_->accept(visitor);
//   // visitor.visit(*ptr_);
// }

template<typename DT>
void Symbolic<DT>::accept(BaseSymbolicVisitor &visitor) {
  SYMCTRL_DEBUG("Inside the accept function.");
  visitor.visit(*static_cast<const DT *>(this));
}

template<typename DT>
void Symbolic<DT>::accept(BaseSymbolicVisitor &visitor) const {
  SYMCTRL_DEBUG("Inside the (const) accept function.");
  visitor.visit(*static_cast<const DT *>(this));
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_VISITOR_VISITOR_HPP
