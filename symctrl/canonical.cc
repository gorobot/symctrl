#include "canonical.hpp"

namespace Controls {

virtual void ControllableFormVisitor::visit(StateSpace &m) {
  // Compute new form.
  // size_t i;
  //
  // // f = A*x + B*u
  // M = SymEngine::DenseMatrix(n, 1);
  // R = SymEngine::DenseMatrix(n, 1);
  // A.mul_matrix(x, M);
  // B.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // fv = M.as_vec_basic();
  // for(i = 0; i < fv.size(); i++) {
  //   obj.set_f(i, fv[i]);
  // }
  //
  // // g = C*x + D*u
  // M = SymEngine::DenseMatrix(p, 1);
  // R = SymEngine::DenseMatrix(p, 1);
  // C.mul_matrix(x, M);
  // D.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // gv = M.as_vec_basic();
  // for(i = 0; i < gv.size(); i++) {
  //   obj.set_g(i, gv[i]);
  // }
}

virtual void ObservableFormVisitor::visit(StateSpace &m) {
  // Compute new form.
  // size_t i;
  //
  // // f = A*x + B*u
  // M = SymEngine::DenseMatrix(n, 1);
  // R = SymEngine::DenseMatrix(n, 1);
  // A.mul_matrix(x, M);
  // B.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // fv = M.as_vec_basic();
  // for(i = 0; i < fv.size(); i++) {
  //   obj.set_f(i, fv[i]);
  // }
  //
  // // g = C*x + D*u
  // M = SymEngine::DenseMatrix(p, 1);
  // R = SymEngine::DenseMatrix(p, 1);
  // C.mul_matrix(x, M);
  // D.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // gv = M.as_vec_basic();
  // for(i = 0; i < gv.size(); i++) {
  //   obj.set_g(i, gv[i]);
  // }
}

virtual void JordanFormVisitor::visit(StateSpace &m) {
  // Compute new form.
  // size_t i;
  //
  // // f = A*x + B*u
  // M = SymEngine::DenseMatrix(n, 1);
  // R = SymEngine::DenseMatrix(n, 1);
  // A.mul_matrix(x, M);
  // B.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // fv = M.as_vec_basic();
  // for(i = 0; i < fv.size(); i++) {
  //   obj.set_f(i, fv[i]);
  // }
  //
  // // g = C*x + D*u
  // M = SymEngine::DenseMatrix(p, 1);
  // R = SymEngine::DenseMatrix(p, 1);
  // C.mul_matrix(x, M);
  // D.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // gv = M.as_vec_basic();
  // for(i = 0; i < gv.size(); i++) {
  //   obj.set_g(i, gv[i]);
  // }
}

} // Controls
