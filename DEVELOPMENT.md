# Development Notes

* [Design Decisions](#design-decisions)
* [C++ Library](#c++-library)
* [C Interface](#c-interface)
* [CMake](#cmake)
* [Directory Structure](#directory-structure)
* [Language Bindings](#language-bindings)
* [Visitor Pattern](#visitor-pattern)

## Design Decisions

In order to make the controls library cross-platform and language agnostic`*`, the library is written in C++, and a C interface is provided which allows for low-level language bindings.

`*` Meaning the library is compiled as a C shared library.

## C++ Library

The reason for writing the library in C++ is to interface directly with the [SymEngine](https://github.com/symengine/symengine) library. The backbone of the symbolic controls library is the ability to work with symbolic variables and to be able to perform symbolic algebra calculations. This functionality is important for working with nonlinear and hybrid systems.

## C Interface

Providing a C interface for C++ classes is a little tricky to grasp at first, but the basic premise is that every C++ member class function that is exposed in the API needs a C function equivalent.

```cpp
// c_wrapper.hpp
#ifndef C_WRAPPER_HPP
#define C_WRAPPER_HPP

extern "C" {

typedef struct StateSpace_C StateSpace_C;

StateSpace_C* statespace_new();
void statespace_free(StateSpace_C* obj);

}

#endif
```

```cpp
// c_wrapper.cc
#include "c_wrapper.hpp"
#include "state_space.hpp"

struct StateSpace_C {
  Controls::StateSpace m;
};

StateSpace_C* statespace_new() {
  return new StateSpace_C;
}

void statespace_free(StateSpace_C* obj) {
  delete obj;
}
```

Each class needs to have, at minimum, a dummy structure to hold the class instance, and a function to create a new structure and a function to delete it.

## CMake

CMake is used in order to build the library. The versatility of CMake allows us to provide a sufficiently complex build environment without the maintenance issues associated with a single Makefile.

## Directory Structure

The library is organized by module. Each module contains code relevant to a specific functionality available in the library. Each module can be thought of as a separate library.

On a basic level, the core C++ classes are contained in the [`models`](https://github.com/ajthor/symbolic-controls-toolbox/tree/master/models) directory, while the functionality which works with these models resides in the appropriate directories at the top level.

An example of the modular structure is given by the following directory structure.

```shell
top
├─ analysis
│  ├─ CMakeLists.txt
│  ├─ c_wrapper.hpp
│  ├─ c_wrapper.cc
│  ├─ ctrbf.hpp
│  └─ ctrbf.cc
├─ models
│  ├─ CMakeLists.txt
│  ├─ c_wrapper.hpp
│  ├─ c_wrapper.cc
│  ├─ state_space.hpp
│  └─ state_space.cc
└─ CMakeLists.txt
```

## Language Bindings

The two primary language bindings which are included in the toolbox are for Matlab and Python. This is a design decision to cater to the scientific computing community. Other bindings are possible, given that the library provides a C interface for working with the underlying C++ code.

The bindings are located in the `matlab` and `python` directories, and include instructions for building the appropriate toolboxes and libraries to use with the Symbolic Controls Toolbox.

In order to use the library with other languages, a wrapper should be created which encapsulates the desired functionality. See the `c_wrapper.cc` and `c_wrapper.hpp` files in the module directories for information on how to interface with the C language bindings.

```shell
top
├─ matlab
│  ├─ CMakeLists.txt
│  ├─ matlab_wrapper.hpp    # Matlab interface.
│  └─ matlab_wrapper.cc     # Wraps C bindings.
├─ python
│  ├─ CMakeLists.txt
│  ├─ python_wrapper.hpp    # Python interface.
│  └─ python_wrapper.cc     # Wraps C bindings.
├─ mainlib
│  ├─ CMakeLists.txt
│  ├─ c_wrapper.hpp         # C interface.
│  ├─ c_wrapper.cc          # Wraps C++ code.
│  └─ other code...
└─ CMakeLists.txt
```

Each language has its own bindings which encapsulate the C bindings. This means that each language should implement the same (or very similar) API.

```txt
    ┌─────┐    ┌─────────────┐    ┌────────────────────┐    ┌────────────┐
    │ C++ │ -> │  c_wrapper  │ -> │ <language>_wrapper │ -> │ <language> │
    └─────┘    └─────────────┘    └────────────────────┘    └────────────┘
```

## Visitor Pattern

Control models use the visitor pattern to define new behavior. 
