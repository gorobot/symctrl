#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <functional>
#include <memory>

#include <symctrl/assert.hpp>
#include <symctrl/shims/hash.hpp>

using Controls::hash_t;
using Controls::hash_string;

// Uncomment this line to enable debugging.
#define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

// class TypeID {
// public:
//   using type = TypeID();
//
// private:
//   type* id;
//
// public:
//   TypeID(type* id)
//       : id{id} {}
//
// private:
//   // template<typename T>
//   // friend TypeID GetTypeId();
//
//   // template<typename T>
//   // inline const T& casting_function(const Concept &m) {
//   //
//   // }
// };

template<typename T>
class Number {
public:
  T value_;
};

// template<typename T1, typename T2>
// void add(T1 &lhs, T2 &rhs) {
//
// }

class Object {
private:
  class Concept;
  template<typename T> class Model;

  using TypeID = void*;

  // template<TypeID ID>
  // struct recover;

  struct recover {
    decltype(auto) operator()(Concept &m);
  };

  using RecoverType = recover;

  template<typename T>
  static TypeID GetTypeID() {
    struct subRecover : public recover {
      decltype(auto) operator()(Concept &m) {
        return static_cast<Model<T>&>(m);
      }
    };
    static subRecover placeHolder;
    return (reinterpret_cast<TypeID>(&placeHolder));
  }

  class Concept {
  private:
    TypeID id_;
  public:
    Concept(TypeID id) : id_(id) {}
    virtual ~Concept() = default;

    inline TypeID getID() { return id_; }
  };

  template<typename T>
  class Model : public Concept {
  private:
    T data_;

  public:
    Model(T data)
        : Concept(GetTypeID<T>()),
          data_(data) {}
  };

  template<typename DT>
  friend inline void add(DT &lhs, Object &rhs) {

  }

  std::shared_ptr<const Concept> ptr_;

public:
  template<typename T>
  Object(T data) {
    using namespace std::placeholders;
    std::shared_ptr<Model<T>> p = std::make_shared<Model<T>>(data);

    // auto bf = std::bind(&add, std::placeholders::_1, data);

    // recover<GetTypeID<T>()>::operator() = [&](Concept&m) -> auto {
    //   return static_cast<Object::Model<T>&>(m);
    // };
    // auto id = p->getID();
    // auto casted = reinterpret_cast<RecoverType*>(id);
    // auto sth = casted->operator()(*p);

    // int a = 1;
    // auto id = reinterpret_cast<void*>(&a);
    // auto casted = reinterpret_cast<int*>(id);
    // std::cout << *casted << '\n';
    // decltype(*casted)::show;

    ptr_ = p;
  }

  template<typename T>
  void do_a_thing(T parameter) {

  }
};

TEST_CASE("playground1", "[playground]") {
  Object a(Number<int>{2});
  Object b(Number<int>{5});
  Object c("hello");

  add(a, b);


  // auto bf = std::bind(say_something<const char *>, "hello");
  // bf();

  // a.do_a_thing("hello");
  // b.do_a_thing();
  // c.do_a_thing();
}


// template<typename T>
// T recover() {
//   std::cout << "inside recovery function" << '\n';
//   return T();
// }
//
// class recovery_ftor {
// private:
//   template<typename T>
//   recovery_ftor(T functor) {
//     // type::show;
//     std::cout << functor() << '\n';
//   }
//
// public:
//   template<typename T>
//   friend recovery_ftor get_recovery();
// };
//
// template<typename T>
// recovery_ftor get_recovery() {
//   return recovery_ftor(&recover<T>);
// }
//

struct Concept {

};

template<typename T>
class Model : public Concept {
public:
  T data_;
  Model(T data) : data_(data) {}
};

class Something {
public:
  Concept data_;

  template<typename T>
  Something(T data)
      : data_(Model<T>(data)) {}

};

TEST_CASE("playground2", "[playground]") {
  Something a(Number<int>{2});
  Something b(Number<int>{5});
  // Object c("hello");

  // add(a, b);


  // auto bf = std::bind(say_something<const char *>, "hello");
  // bf();

  // a.do_a_thing("hello");
  // b.do_a_thing();
  // c.do_a_thing();
}
