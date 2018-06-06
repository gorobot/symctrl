# Symbolic Controls Library

## What is this?
The Symbolic Controls Library is a free (as in speech), open-source library
written in C++ designed to implement a wide array of functions and classes for
working with control systems.

It is designed to address some of the limitations with the numerous control
systems toolboxes currently available and provide an interface for working with:

* Linear Systems
* Nonlinear Systems
* Hybrid Systems
* MDP
* etc.

The Symbolic Controls Library uses [SymEngine](https://github.com/symengine/symengine) as a symbolic backend, which is a pure C++ symbolic backend for [SymPy](http://www.sympy.org/en/roadmap.html). Instructions for [installing SymEngine](https://github.com/symengine/symengine#installation) can be found on the project's GitHub page.

New (untested) code is found in the [development branch](https://github.com/ajthor/symbolic-controls-toolbox/tree/development).

New [releases](https://github.com/ajthor/symbolic-controls-toolbox/releases) are kept in the GitHub repository.

Thin wrappers are provided for working with the library in other languages. While the library is written in C++, the C language wrappers included in the library allow it to be used from other languages as well. Wrappers for Python and Matlab are included in the library and installable using CMake.

## Getting Started
1. Download the library from the GitHub repository.
1. Install the dependencies.
1. Install the library using CMake.
1. Enjoy!

```shell
> cmake .
> make
> make install
```

## Your First System
```matlab
% Define symbolic variables.
syms x1 x2

% Create a symbolic state space model.
sys = symss;
sys.states = [x1 x2];

% Define state equations.
sys.f(1) = x2;
sys.f(2) = -sin(x1) - x2;

sys.g(1) = x1;

% Simulate the system.
nlsim2(sys, 0, [0 10], {[1 1]});
```

## Demonstration Systems
Several demonstration systems are provided to get started using the library,
including:

* pendulum equations
* mass-spring systems
* quadrotor dynamics
* etc.

The demo systems are located in the `demos` folder.

## Examples
Several examples are provided in the `doc/examples` directory. Be sure
to check the examples and demonstrations for tips on using functions and
systems provided with the library.
