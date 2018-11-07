#ifndef SYMCTRL_MATH_LIE_HPP
#define SYMCTRL_MATH_LIE_HPP

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>
#include <symengine/mul.h>

namespace Controls {

// L = (df/dx)*h
void lie_derivative(SymEngine::RCP<const SymEngine::Basic> &f,
                    SymEngine::vec_basic &x,
                    SymEngine::RCP<const SymEngine::Basic> &h, Symengine::vec_basic &result) {
  //
  size_t n = x.size();

  result = SymEngine::vec_basic(n);

  #pragma omp parallel for
  for(i = 0; i < n; i++) {
    // TODO: Ensure all elements of x are symbols.
    if (SymEngine::is_a<SymEngine::Symbol>(*(x[i]))) {
      const SymEngine::RCP<const SymEngine::Symbol> x_ = SymEngine::rcp_static_cast<const SymEngine::Symbol>(x[i]);

      result[i] = SymEngine::mul(f->diff(x_), h);
    }
  }
}

} // Controls

#endif /* end of include guard: SYMCTRL_MATH_LIE_HPP */
