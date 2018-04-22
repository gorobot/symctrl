%% Hybrid System Response Example
% Example showing hybrid system response for a thermostat. 

%% Define the Hybrid System Model
% Define the system model with hybrid dynamics.
syms x
sys = symhyss;
sys.states = x;

a = 0.008;

%%
% The first index when defining system dynamics corresponds to a mode,
% while the second index corresponds to a state equation in the current
% dynamics. I.e.
%                              .
%   sys.f(2, 3) corresponds to x3 = f3(t, x, u) in state 2.
% 
%   sys.cond(1, 2) corresponds to the guard condition for the system
%   switching from mode 1 to mode 2.
sys.f(1, 1) = -a*x;
sys.guard(1, 2) = x >= 20;

sys.f(2, 1) = -a*(x - 30);
sys.guard(2, 1) = x <= 22;

%% Simulate the System
% Define the time span and the initial conditions. 
tspan = [0 120];
ic = {15, 20, 25};

%%
% Simulate the hybrid system using the initial conditions.
hysim(sys, sym(0), tspan, ic);

