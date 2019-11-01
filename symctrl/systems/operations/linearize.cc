#include <vector>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/subs.h>

#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/vector.hpp>
#include <symctrl/math/matrix/expression.hpp>
#include <symctrl/math/matrix/type_traits/is_symbolic.hpp>
// #include <symctrl/systems/statespace/statespace.hpp>
#include <symctrl/systems/operations/linearize.hpp>
#include <symctrl/shims/default.hpp>
#include <symctrl/type_traits/is_symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// linearize
//
// template<typename T>
// T &linearize(T &f, const SymbolicVector &x)
// -> enable_if_symbolic_t<T> {
//   size_t n_ = x.size();
//   SymEngine::map_basic_basic d;
//
//   for(size_t i = 0; i < n_; i++) {
//     d[(~x)[i]] = default_value<symbolic_t>();
//   }
//
//   return SymEngine::ssubs((~f), d);
// }
//
// template<typename T>
// T &linearize(T &f, const SymbolicVector &x)
// -> enable_if_symbolic_m_t<T> {
//   size_t n_ = x.size();
//   SymEngine::map_basic_basic d;
//
//   for(size_t i = 0; i < n_; i++) {
//     d[(~x)[i]] = default_value<symbolic_t>();
//   }
//
//   for(size_t i = 0; i < A.nrows(); i++) {
//     (~f)[i] = SymEngine::ssubs((~f)[i], d);
//   }
//
//   return f;
// }

// Substitute x and u for 0 in A, B, C, D.
StateSpace linearize(const StateSpace &sys) {
  size_t n = sys.state_variables.size();
  size_t m = sys.input_variables.size();
  size_t p = sys.output_equations.size();

  SymEngine::map_basic_basic d;
  Math::SymbolicDense A = sys.A();
  Math::SymbolicDense B = sys.B();
  Math::SymbolicDense C = sys.C();
  Math::SymbolicDense D = sys.D();

  for(size_t i = 0; i < n; i++) {
    d[sys.state_variables[i]] = default_value<symbolic_t>();
  }

  for(size_t i = 0; i < m; i++) {
    d[sys.input_variables[i]] = default_value<symbolic_t>();
  }

  for(size_t i = 0; i < A.nrows(); i++) {
    for(size_t j = 0; j < A.ncols(); j++) {
      A(i, j) = SymEngine::ssubs(A(i, j), d);
    }
  }
  for(size_t i = 0; i < B.nrows(); i++) {
    for(size_t j = 0; j < B.ncols(); j++) {
      B(i, j) = SymEngine::ssubs(B(i, j), d);
    }
  }
  for(size_t i = 0; i < C.nrows(); i++) {
    for(size_t j = 0; j < C.ncols(); j++) {
      C(i, j) = SymEngine::ssubs(C(i, j), d);
    }
  }
  for(size_t i = 0; i < D.nrows(); i++) {
    for(size_t j = 0; j < D.ncols(); j++) {
      D(i, j) = SymEngine::ssubs(D(i, j), d);
    }
  }

  return StateSpace(sys.state_variables,
                    sys.input_variables,
                    A*sys.state_variables + B*sys.input_variables,
                    C*sys.state_variables + D*sys.input_variables);
}

} // Controls
