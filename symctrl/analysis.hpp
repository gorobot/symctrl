#ifndef SYMCTRL_ANALYSIS_HPP
#define SYMCTRL_ANALYSIS_HPP

#include <symengine/matrix.h>

#include "state_space.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Controllability
//
void ctrb(StateSpace &obj, SymEngine::DenseMatrix &result);
void ctrb(SymEngine::DenseMatrix &A,
          SymEngine::DenseMatrix &B,
          SymEngine::DenseMatrix &result);

int ctrb_rank(StateSpace *obj);

bool is_controllable(SymEngine::DenseMatrix &Co);

// ----------------------------------------------------------------------
// Observability
//
void obsv(StateSpace &obj, SymEngine::DenseMatrix &result);
void obsv(SymEngine::DenseMatrix &A,
          SymEngine::DenseMatrix &C,
          SymEngine::DenseMatrix &result);

int obsv_rank(StateSpace *obj);

bool is_observable(SymEngine::DenseMatrix &Ob);

// ----------------------------------------------------------------------
// Linearization
//
void linearize(StateSpace &obj);
// void linearize(const SymEngine::vec_basic &eq);

} // Controls

#endif /* end of include guard: SYMCTRL_ANALYSIS_HPP */
