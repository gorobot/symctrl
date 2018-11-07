#ifndef SYMCTRL_MATRIX_NETWORK_HPP
#define SYMCTRL_MATRIX_NETWORK_HPP

#include <vector>

#include "graph.hpp"

namespace Controls {

class HopfieldNetwork {
private:
  AdjacencyMatrix w_;
  std::vector<int> s_;
  std::vector<double> threshold_;

public:
  HopfieldNetwork(AdjacencyMatrix &w,
                  std::vector<int> &s,
                  std::vector<double> &t) : w_(w), s_(s), threshold_(t) {}
  ~HopfieldNetwork() {}

  void AsynchronousUpdate();
  void AsynchronousUpdate(size_t s);

  void SynchronousUpdate();

  virtual double energy();
};

class RBM {

};

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_NETWORK_HPP */
