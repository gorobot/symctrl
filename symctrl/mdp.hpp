#ifndef SYMCTRL_MDP_HPP
#define SYMCTRL_MDP_HPP

#include <map>
#include <tuple>
#include <vector>

#include "control_model.hpp"

namespace Controls {

class MDP : public ControlModel {
public:
  MDP();
  ~MDP();

  void set_num_states(const std::size_t arg);
  std::size_t get_num_states();

  void set_num_inputs(const std::size_t arg);
  std::size_t get_num_inputs();

  void set_probability(size_t u, size_t x, size_t xp, const double value);
  double get_probability(size_t u, size_t x, size_t xp);

  void set_reward(size_t u, size_t x, size_t xp, const double value);
  double get_reward(size_t u, size_t x, size_t xp);

  void set_gamma(const double arg);
  double get_gamma();

private:
  std::size_t num_states_;
  std::size_t num_inputs_;

  std::vector<std::map<std::tuple<unsigned, unsigned>, double>> probabilities_;
  std::vector<std::map<std::tuple<unsigned, unsigned>, double>> rewards_;

  // SparseMatrix<double> probabilities_ = SparseMatrix<double>();
  // SparseMatrix<double> rewards_ = SparseMatrix<double>();

  double gamma_;
};

} // Controls

#endif /* end of include guard: SYMCTRL_MDP_HPP */
