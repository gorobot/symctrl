#ifndef SYMCTRL_MATH_SYMBOLIC_RECOVER_HPP
#define SYMCTRL_MATH_SYMBOLIC_RECOVER_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// TypeID
//
// class TypeID {
//   using type = TypeID();
//
// private:
//   type* id;
//
//   TypeID(type* id)
//       : id{id} {}
//
// public:
//   template<typename T>
//   friend TypeID GetTypeId();
//
//   bool operator==(TypeID m) const {
//     return id == m.id;
//   }
//   bool operator!=(TypeID m) const {
//     return id != m.id;
//   }
// };
//
// template<typename T>
// TypeID GetTypeId() {
//   return &GetTypeId<T>;
// }

// using TypeID = void*;
using TypeID = size_t;

template<typename T>
static const TypeID GetTypeID() {
  static uint32_t placeHolder;
  return (reinterpret_cast<TypeID>(&placeHolder));
}

// template<typename T>
// constexpr TypeID CGetTypeID() { return &CGetTypeID<T>(); }

// ----------------------------------------------------------------------
// Recover
//
// template<TypeID ID_>
// void Recover();
//
// template<>
// void Recover<GetTypeID<int>()>() {
//
// }
//
// template<>
// void Recover<1>() {
//
// }
// template<typename T>
// decltype(auto) recover(std::shared_ptr<void> m) {
//   return *std::static_pointer_cast<T>(m);
// }

struct recover_info;
struct recovery_ftor;

struct recovery_ftor {
  decltype(auto) operator()(std::shared_ptr<void>);
};

struct recover_info {
  // decltype(auto) recovery_fn(std::shared_ptr<void>);
  recovery_ftor ftor;

  template<typename T>
  static recover_info& get();
};

template<typename T>
recover_info& recover_info::get() {
  static recover_info info;
  return info;
}

// decltype(auto) recover_info::get<int>().recovery_fn(std::shared_ptr<void> m) {
//   return *std::static_pointer_cast<int>(m);
// }

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_RECOVER_HPP
