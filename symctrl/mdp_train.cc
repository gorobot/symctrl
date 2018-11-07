// References:
// Poole, David L., and Alan K. Mackworth. Artificial Intelligence: foundations
// of computational agents. Cambridge University Press, 2010.
//
// Russell, Stuart J., and Peter Norvig. Artificial intelligence: a modern
// approach. Malaysia; Pearson Education Limited,, 2016.

#include <random>

#include "mdp_train.hpp"

namespace Controls {

void MDPTrainVisitor::init_random_policy(MDP &m) {
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_real_distribution<> uniform_dist(0.0, 1.0);

  size_t i, j;
  size_t nu = m.get_num_inputs();
  size_t nx = m.get_num_states();
  double sum;

  // Size the policy matrix. (X, A) matrix.
  policy_ = mdp_policy_t(nx, std::vector<double>(nu));

  // For each row of the matrix, create a uniform distribution of probabilities.
  for(i = 0; i < nx; i++) {
    // Generate {a} random numbers.
    for(j = 0; j < nu; j++) {
       policy_[i][j] = uniform_dist(gen);
    }

    // Compute the sum.
    sum = std::accumulate(policy_[i].begin(), policy_[i].end(), 0.0);

    // Divide random numbers by sum.
    for(j = 0; j < nu; j++) {
      policy_[i][j] /= sum;
    }
  }
}

void PolicyIterationVisitor::visit(MDP &m) {

}

void ValueIterationVisitor::visit(MDP &m) {
  size_t i, j, k, n;
  size_t nu = m.get_num_inputs();
  size_t nx = m.get_num_states();

  init_random_policy(m);

  // There is better sparse matrix multiplication for CSR format.
  // Precompute P*R. (X, U)
  std::vector<double> tmp = std::vector<double>(nx);
  mdp_policy_t PR = mdp_policy_t(nx, std::vector<double>(nu));

  #pragma omp parallel for
  for(k = 0; k < nu; k++) {

    // for(const auto &p : obj->m.probabilities_.at(u)) {
    //   (*r)[k] = std::get<0>(p.first);
    //   (*c)[k] = std::get<1>(p.first);
    //   (*v)[k] = p.second;
    // }

    // for(i = 0; i < nx; i++) { // row
    //   for(j = 0; j < nx; j++) { // col
    //     // Zeroize
    //     PR[i][j] = 0.0;
    //
    //     for(n = 0; n < nx; n++) {
    //       PR[i][j] += m.probabilities_[k][std::make_tuple(i, n)]
    //                 * m.rewards_[k][std::make_tuple(n, j)];
    //     }
    //   }
    // }
  }

}

} // Controls
