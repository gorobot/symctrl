# Symbolic Controls Toolbox

## What is this?
The Symbolic Controls Toolbox is a free (as in speech), open-source Matlab
toolbox designed to implement a wide array of functions and classes for working
with control systems using the symbolic toolbox in Matlab.

It is designed to address some of the limitations with the control systems
toolbox currently available in Matlab and provide an interface for working with:

* Linear Systems (LTI & LTV)
* Discrete Systems
* SISO & MIMO
* Nonlinear Systems
* Hybrid Systems
* etc.

New [releases](https://github.com/ajthor/symbolic-controls-toolbox/releases) are kept in the GitHub repository.

New (untested) code is found in the [development branch](https://github.com/ajthor/symbolic-controls-toolbox/tree/development).

## Getting Started
1. Download the toolbox from the GitHub repository.
1. Install the toolbox.
1. Enjoy!

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
Several demonstration systems are provided to get started using the toolbox,
including:

* pendulum equations
* mass-spring systems
* quadrotor dynamics
* etc.

The demo systems are located in the `ctrldemos` folder.

The complete list of working demos can be found using:
```matlab
help ctrldemo
```

Load a demo system using the following command.
Be sure to replace `<system>` with the name of a demo system.
```matlab
sys = ctrldemo('<system>');
```

## Examples
Several example scripts are provided in the `doc/examples` directory. Be sure
to check the examples and demonstrations for tips on using functions and
systems provided with the toolbox.

## Testing
Run the `runAllTests.m` script from the parent directory to run all unit tests
in the `test` directory. Use this to ensure that the toolbox is working as
expected before you begin.

Use `runtests` to run specific tests in the `test` directory.

## Disclaimer
The authors of this toolbox have made every effort to ensure the toolbox
functions work in the generalized case, but there is no assurance that the
toolbox will work for every system.
