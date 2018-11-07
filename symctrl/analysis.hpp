#ifndef SYMCTRL_ANALYSIS_HPP
#define SYMCTRL_ANALYSIS_HPP

#include <symengine/matrix.h>

#include "state_space.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Matrix Exponential
//
void expm(StateSpace &obj);

// ----------------------------------------------------------------------
// Controllability
//
void ctrb(StateSpace &obj, SymEngine::DenseMatrix &result);
void ctrb(SymEngine::DenseMatrix &A,
          SymEngine::DenseMatrix &B,
          SymEngine::DenseMatrix &result);

// TODO: Implement rank revealing function.
size_t ctrb_rank(StateSpace *obj);
size_t ctrb_rank(SymEngine::DenseMatrix &C);

bool is_controllable(SymEngine::DenseMatrix &Co);

// ----------------------------------------------------------------------
// Observability
//
void obsv(StateSpace &obj, SymEngine::DenseMatrix &result);
void obsv(SymEngine::DenseMatrix &A,
          SymEngine::DenseMatrix &C,
          SymEngine::DenseMatrix &result);

// TODO: Implement rank revealing function.
size_t obsv_rank(StateSpace *obj);
size_t obsv_rank(SymEngine::DenseMatrix &C);

bool is_observable(SymEngine::DenseMatrix &Ob);

} // Controls

#endif /* end of include guard: SYMCTRL_ANALYSIS_HPP */
