#include "mdp.hpp"

namespace Controls {

MDP::MDP() {};
MDP::~MDP() {}

void MDP::set_num_states(const size_t arg) {
  num_states_ = arg;
}
size_t MDP::get_num_states() {
  return num_states_;
}

void MDP::set_num_inputs(const size_t arg) {
  num_inputs_ = arg;
}
size_t MDP::get_num_inputs() {
  return num_inputs_;
}

void MDP::set_probability(size_t u, size_t x, size_t xp, const double value) {
  // TODO: Ensure probability is not greater than 1.
  // TODO: Ensure probability of any one row is not greater than 1.

  probabilities_.at(u).at(std::make_tuple(x, xp)) = value;
}
double MDP::get_probability(size_t u, size_t x, size_t xp) {
  double ret;

  try {
    ret = probabilities_.at(u).at(std::make_tuple(x, xp));
    return ret;
  } catch(const std::out_of_range &e) {
    return 0;
  }
}
void MDP::set_reward(size_t u, size_t x, size_t xp, const double value) {
  rewards_.at(u).at(std::make_tuple(x, xp)) = value;
}
double MDP::get_reward(size_t u, size_t x, size_t xp) {
  double ret;

  try {
    ret = rewards_.at(u).at(std::make_tuple(x, xp));
    return ret;
  } catch(const std::out_of_range &e) {
    return 0;
  }
}

void MDP::set_gamma(const double arg) {
  gamma_ = arg;
}
double MDP::get_gamma() {
  return gamma_;
}

} // Controls
