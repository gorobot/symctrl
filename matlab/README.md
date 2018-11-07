# Matlab Bindings

The Matlab bindings provide an interface to the Symbolic Controls Library in a
convenient Matlab toolbox that is designed to leverage the functionality and
performance of the underlying C++ code.

It uses [SymEngine](https://github.com/symengine/symengine) as a symbolic backend, and uses an inter-operability layer to convert between the Symbolic Toolbox in Matlab and [SymEngine](https://github.com/symengine/symengine) on the backend.

## Getting Started
1. [Download](https://github.com/ajthor/symbolic-controls-toolbox/releases) the toolbox from the GitHub repository.
1. Build the symbolic controls library.
1. Install the toolbox.
1. Enjoy!

### Build From Source

Once the Symbolic Controls Library is installed, run CMake with the following flag set in order to install the Matlab wrappers.

```shell
> cmake -DBUILD_MATLAB=ON .
> make
> make install
```

Note that you may need to build and install the main library first, without the `-DBUILD_MATLAB=ON` flag set in order for this to work. If you get errors while building from source with the flag set, try building without it first.

The toolbox is automatically installed to the user path when you run this command. Check your user path in Matlab by running the `userpath` command before you install the files.

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

## Using the Toolbox

The toolbox includes a `startup.m` and `finish.m` script which are automatically run when you open and close Matlab. The scripts load and unload the library each time you run Matlab. This is done to clear variables in the workspace that require memory to be freed, and to ensure that the library is loaded properly. However, if you need to load the library manually, use the `loadmatctrl.m` script located in the toolbox folder.

## Demo Systems

The complete list of working demos can be found using:
```matlab
help ctrldemo
```

Load a demo system using the following command.
Be sure to replace `<system>` with the name of a demo system.
```matlab
sys = ctrldemo('<system>');
```

## For Developers

Use the Matlab `calllib` function to interface with C wrapper functions. All
wrapper functions should use basic C types listed in the Matlab documentation.

* `matlab_wrapper.hpp`
* `matlab_wrapper.cc`

The generated toolbox should be a stand-alone distribution. CMake is the
preferred method for compiling and installing the C wrappers into a shared
library.

For testing, it may be easier to use matlab from the command-line in order to
deal with any errors that may arise while debugging.

```shell
> matlab -nosplash -nojvm -nodesktop -nodisplay -r '<script>, pause(1), quit'
```

Note that an extra pause is added at the end of the script before exiting. This
is often necessary to prevent some errors.
