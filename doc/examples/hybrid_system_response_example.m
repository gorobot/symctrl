%% Hybrid System Response Example
% Example showing hybrid system response for a thermostat. 

%% Define the Hybrid System Model
% Define the system model with hybrid dynamics.
syms x u
sys = symss;
sys.states = x;
sys.inputs = u;

a = 0.008;
sys.f = piecewise(x >= 20, -a*x, x <= 22, -a*(x - 30));

sys.g(1) = x;

%% Simulate the System
tspan = [0 120];
ic = {15, 20, 25};

hysim(sys, sym(0), tspan, ic);

