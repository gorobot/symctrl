#ifndef SYMCTRL_MATRIX_MATRIX_HPP
#define SYMCTRL_MATRIX_MATRIX_HPP

namespace Controls {

template<typename Derived>
class MatrixBase {
public:
  const Derived& derived() {
    return *static_cast<Derived*>(this);
  }

  const Derived& const_derived() const {
    return *static_cast<Derived*>(const_cast<MatrixBase*>(this));
  }
};

// class Matrix : public MatrixBase<Matrix> {
// private:
//   size_t row_;
//   size_t col_;
//
// public:
//
//   virtual ~Matrix();
//
//   size_t nrows() const { return row_; }
//   size_t ncols() const { return col_; }
//   size_t size() const { return nrows()*ncols(); }
//
// };

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_MATRIX_HPP */
