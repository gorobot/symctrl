%% Linearization Example
% Example showing linearization of a symbolic system of equations.

%% Define Symbolic Variables
% Define the symbolic variables used in the state space equations.
syms a b c d e f

%%
% The state variables are $x_1$ and $x_2$.
syms x1 x2

%% Define the State Space Model
% The state space model of our system is defined using the equations:
% 
% $$f_1(x) = ax_1 - bx_1x_2 - cx_1^2$$
% 
% $$f_2(x) = dx_2 - ex_1x_2 - fx_2^2$$

sys = symss;
sys.states = [x1 x2];
sys.f(1) = a*x1 - b*x1*x2 - c*x1^2;
sys.f(2) = d*x2 - e*x1*x2 - f*x2^2;

%%
% The state matrix of the system is given as:
sys.A

%% Linearize the System
% Linearize the system about the equilibrium point $f(x) = 0$.
linsys = linearize(sys);

%%
% The linearized state matrix becomes:
linsys.A
