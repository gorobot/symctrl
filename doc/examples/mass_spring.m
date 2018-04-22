%% State Space Representation of Mass/Spring/Damper System
% Set up a symbolic state space model for a mass/spring damper system.

%% Set up the Symbolic Variables
% Define the symbolic constants and state variables for the equations of
% motion. 
% 
% Note that if we have derivatives in the equations of motion, we need to
% define the state variables as symbolic functions. Use `(t)` after the
% variable name to do this.
syms M1 B B1 K K1 fo1(t) M2 B2 K2 fo2(t) t y
syms y1(t) y2(t)

%%
% Define the equations of motion as symbolic expressions. 
f1 = M1*diff(y1, t, t) + (B + B1)*diff(y1, t) + (K + K1)*y1 - B*diff(y2, t) - K*y2 == fo1;
f2 = M2*diff(y2, t, t) + (B + B2)*diff(y2, t) + (K + K2)*y2 - B1*diff(y1, t) - K*y1 == -fo2;

g = y == y1;

states = {y1, diff(y1, t), y2, diff(y2, t)};
inputs = {fo1, fo2};
outputs = {y};

%%
% Create a symbolic state variable object from the equations of motion.
sv = symsv({f1, f2}, {g}, ...
    'states', states, ...
    'inputs', inputs, ...
    'outputs', outputs);

%% Analyze Symbolic State Variables
% We can view the state variables by accessing the properties of the |sv|
% object.
% 
% * |sv.x|
% * |sv.Dx|
% * |sv.u|
% * |sv.y|
% 
% For example:
sv.x

%%
% The state variable object also computes the derivatives of the state
% variables.
sv.Dx

%% Compute the State Space & Transfer Function
% We can convert the state variables to a state space representation using
% |symss(sv)|.
sys = symss(sv);

sys.A

%%
% Similarly, we can also convert to a transfer function using |symtf(sys)|.
G = symtf(sys)
