#ifndef SYMCTRL_MATRIX_GRAPH_HPP
#define SYMCTRL_MATRIX_GRAPH_HPP

#include <set>
#include <vector>

namespace Controls {

// Graph Theory

class AdjacencyMatrix {
private:
  SparseMatrixBase m_;

public:
  AdjacencyMatrix(size_t row, size_t col) : row_(row), col_(col) {}
  AdjacencyMatrix(size_t row,
                  size_t col,
                  std::vector<double> v) : row_(row), col_(col), v_(v) {}
  AdjacencyMatrix(SparseMatrixBase &m) : m_(m) {}
  ~AdjacencyMatrix() {}

};

class BipartiteGraph {
private:
  SparseMatrixBase m_;
public:
  BipartiteGraph(SparseMatrixBase &m) : m_(m) {}
  ~BipartiteGraph() {}
};

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_GRAPH_HPP */
