# Python Bindings

## What is this?

The Python bindings are a Python extension module written in C++ that is
designed to implement the functionality of the Symbolic Controls Library. It
uses [SymEngine](https://github.com/symengine/symengine) as a symbolic backend,
making it inter-operable with [SymPy](http://www.sympy.org/en/index.html).

## Getting Started

Install the dependencies.

```shell
> pip install cython
> git clone https://github.com/symengine/symengine.py .
> python setup.py install
```

Build the Symbolic Controls Library.

```shell
> cmake -DBUILD_PYTHON=ON .
> make
> make install
```

Fro developers, it may be a good idea to use an out of source build.

```shell
> (cd build && cmake -DBUILD_PYTHON=on .. && make && make install)
```

It is also possible to install the python library from the `python` directory.

```shell
> python setup.py install
```

## Your First System

```python
import pyctrl
import sympy

sys = pyctrl.symss()

```

## For Developers

Use the Python/C API interface for specialized functions that are performance-oriented.

- `py_wrapper.hpp`
- `py_wrapper.cc`

Otherwise, use the Cython interface for C++ class member functions.

- `py_wrapper.pyx`

CMake is the preferred method for compiling Cython files into C++ and creating a shared library.

For this installation method, CMake compiles a shared C library and places the library in `site-packages` so that it can be imported as a python module. The
