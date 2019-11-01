#ifndef SYMCTRL_MATH_MATRIX_OPERATIONS_JACOBIAN_HPP
#define SYMCTRL_MATH_MATRIX_OPERATIONS_JACOBIAN_HPP

#include <vector>

#include <symengine/subs.h>
#include <symengine/symbol.h>

#include <symctrl/shims/default.hpp>
#include <symctrl/shims/symbolic.hpp>
#include <symctrl/math/matrix/dense/dense.hpp>
#include <symctrl/math/matrix/vector/vector.hpp>
#include <symctrl/math/matrix/type_traits/is_symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Jacobian
//
template<typename DT>
auto jacobian(const Matrix<DT> &f, const Matrix<DT> &v)
-> enable_if_symbolic_m_t<DT, SymbolicDense> {
  size_t n_ = (~f).size();
  size_t m_ = (~v).size();

  std::vector<symbolic_t> v_(n_*m_, default_value<symbolic_t>());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      if(SymEngine::is_a<SymEngine::Symbol>(*(~f)[j])) {
        auto t_ = SymEngine::rcp_static_cast<const SymEngine::Symbol>((~v)[j]);
        v_[i*m_ + j] = (~f)[i]->diff(t_);
      }
      else {
        auto t_ = SymEngine::symbol("t_");
        v_[i*m_ + j] = SymEngine::ssubs(
            SymEngine::ssubs((~f)[i], {{(~v)[j], t_}})->diff(t_),
            {{t_, (~v)[j]}}
          );
      }
    }
  }

  return SymbolicDense(n_, m_, v_);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_OPERATIONS_JACOBIAN_HPP
