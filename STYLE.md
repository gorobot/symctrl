# Style Guide for Symbolic Controls Toolbox

**#1 RULE: MAKE CODE READABLE**
This rule overrules any subsequent rule in the document. Readability is
subjective, but users should be able to follow the function's process easily.

## General

* Use the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).
* Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html), except for stylistic changes as noted below.

## C++

* [Formatting](#formatting)
  * [Long Function Declarations](#long-function-declaration̨s)

## Formatting

### Long Function Declarations

For long parameter lists that do not fit within the 80-column limit, wrap the
parameters onto seprate lines, but align the parameter lists by the opening
parentheses.
```cpp
template<typename T, typename U>
inline void SomeLongFunctionName(const SomeReallyLongParamater<T> &a,
                                 const SomeOtherReallyLongParamaterName<U> &b) {
  // Code goes here.
}
```

If the template list is hard to read as a single line, wrap the template
parameter list onto separate lines, but align by the opening angle bracket.
```cpp
template<typename T,
         typename U,
         template<typename> class DT>
inline void SomeLongFunctionName(const SomeReallyLongParamaterName<T> &a,
                                 const SomeOtherReallyLongParamaterName<U> &b,
                                 const DT<T> AnotherParameter &m) {
  // Code goes here.
}
```

For long class constructor declarations, classes with inheritance, and for
constructors with long initializer lists, wrap the initializer list and function
name onto a new line indented by (4) spaces. Align the initializer list by the
first character.
```cpp
inline void SomeClass::SomeClass(const SomeReallyLongParamaterName<T> &a,
                                 const SomeOtherReallyLongParamaterName<U> &b,
                                 const DT<T> AnotherParameter &m)
    : variable_(value),
      anotherVariable(value2) {
  // Code goes here.
}
```
```cpp
template<typename T,
         typename U>
class SomeClass
    : public SomeParentClass<T>,
      public AnotherParentClass<U> {
public:
  // Code goes here.
}
```
```cpp
template<typename T,
         typename U,
         template<typename> class DT>
inline void
    SomeClass::SomeClass(const SomeReallyLongParamaterName<T> &a,
                         const SomeOtherReallyLongParamaterName<U> &b,
                         const DT<T> AnotherParameter &m)
    : variable_(value),
      anotherVariable(value2) {
  // Code goes here.
}
```

For extra long function or constructor declarations, or for functions using SFINAE or trailing return types, wrap the SFINAE expression onto a new line so that the SFINAE expression is aligned with the initializer list, i.e. (3) spaces.
```cpp
template<typename T,
         typename U,
         template<typename> class DT>
inline auto
    SomeClass::operator=(const SomeReallyLongParamaterName<T> &a,
                         const SomeOtherReallyLongParamaterName<U> &b,
                         const DT<T> AnotherParameter &m)
    : variable_(value),
      anotherVariable(value2)
   -> typename std::enable_if<SomeLongSfinaeExpression<T, U>::value &&
                              SomeOtherLongSfinaeExpression<T, U>::value
                              ReturnValueType>::type {
  // Code goes here.
}
```
