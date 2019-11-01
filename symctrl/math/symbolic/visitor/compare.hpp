#ifndef SYMCTRL_MATH_SYMBOLIC_VISITOR_COMPARE_HPP
#define SYMCTRL_MATH_SYMBOLIC_VISITOR_COMPARE_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/visitor/visitor.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// CompareVisitor
//
template<typename RHS>
class CompareVisitor
    : public SymbolicVisitor<CompareVisitor<RHS>> {
private:
  const RHS &rhs_;

  bool result_;

public:
  CompareVisitor(const Symbolic<RHS> &rhs)
      : rhs_(~rhs) {}

  virtual void visit(const BaseSymbolic &m) {
    SYMCTRL_DEBUG("Inside the SystemVisitor for BaseSymbolic visit function.");
  }

  template<typename LHS>
  void visit(const Symbolic<LHS> &lhs) {
    SYMCTRL_DEBUG("Comparing two symbolics.");
    SYMCTRL_DEBUG((~lhs).hash());
    SYMCTRL_DEBUG((~rhs_).hash());
    result_ = (~lhs).hash() == (~rhs_).hash();
  }

  bool get_result() {
    return result_;
  }
};

// ----------------------------------------------------------------------
// Compare
//
template<typename DT>
inline bool compare(BaseSymbolic &lhs, const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("Inside the compare function.");
  CompareVisitor<DT> s(~rhs);
  lhs.accept(s);
  return s.get_result();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_VISITOR_COMPARE_HPP
