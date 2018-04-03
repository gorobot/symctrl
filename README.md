# Symbolic Controls Toolbox

## What is this?
The Symbolic Controls Toolbox is a free (as in speech), open-source Matlab
toolbox designed to implement a wide array of functions and classes for working
with control systems using the symbolic toolbox in Matlab.

It is designed to address some of the limitations with the control systems toolbox currently available in Matlab and provide an interface for working with:

* Linear Systems (LTI & LTV)
* SISO & MIMO
* Non-linear Systems
* Hybrid Systems
* etc.

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
nlsim2(sys, [0 10], {[1 1]});
```

## Disclaimer
The authors of this toolbox have made every effort to ensure the toolbox functions work in the generalized case, but there is no assurance that the toolbox will work for every system.
