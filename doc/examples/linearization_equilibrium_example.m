%% Linearization About An Equilibrium Point
% Example showing linearization of a system about an equilibrium point.

%% Define Symbolic Variables
% Define the state variables, input variables, and any constants.
syms r(t) diff(r) theta(t) diff(theta) u1 u2
syms k

%% Define the State Space Model
% The state space model is defined by the equations:
% 
% $$f_1(t, x) = \dot{r}$$
% 
% $$f_2(t, x) = r \theta^2 - \frac{k}{r^2} + u_1$$
% 
% $$f_3(t, x) = \dot{\theta}$$
% 
% $$f_4(t, x) = \frac{-2\dot{r}\dot{\theta}}{r} + \frac{u_2}{r}$$

sys = symss;
sys.states = [r(t) diff(r) theta(t) diff(theta)];
sys.inputs = [u1 u2];

sys.f(1) = diff(r);
sys.f(2) = r(t)*diff(theta)^2 - (k/r(t)^2) + u1;
sys.f(3) = diff(theta);
sys.f(4) = -((2*diff(r)*diff(theta))/r(t)) + (u2/r(t));

%% Linearize the System
% Linearize the system about a given equilibrium point.
% 
% $$x = \left[ r(0), 0, \theta(0), \sqrt{k/r(0)^3} \right]$$
linsys = linearize(sys, [r(0), 0, theta(0), (k/r(0)^3)^(1/2)]);

%%
% The state matrix becomes:
linsys.A

%%
% While the input matrix becomes:
linsys.B
