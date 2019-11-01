#ifndef SYMCTRL_SYSTEMS_SYSTEM_HPP
#define SYMCTRL_SYSTEMS_SYSTEM_HPP

namespace Controls {

class Visitor;

// ----------------------------------------------------------------------
// BaseSystem Class
//
class BaseSystem {
public:
  virtual ~BaseSystem() {}
};

// ----------------------------------------------------------------------
// System Class
//
template<typename DT>
class System : BaseSystem {
public:
  inline DT &operator~() {
    return *static_cast<DT *>(this);
  }
  inline const DT &operator~() const {
    return *static_cast<const DT *>(this);
  }

  inline void accept(Visitor &visitor);
};

// ----------------------------------------------------------------------
// System Member Function Definitions
//
template<typename DT>
inline void System<DT>::accept(Visitor &visitor) {
  (*this).operator~().accept(visitor);
}

} // Controls

#endif // SYMCTRL_SYSTEMS_SYSTEM_HPP
