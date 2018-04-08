%% Thermostat Demo System

% a - temperature cooling coeficient, a < 1
syms a

syms x1 u
sys = symss;
sys.states = x1;

sys.f = piecewise(x1 >= 20, -a*x1, x1 <= 22, -a*(x1 - 30));

savedemo('thermostat', sys, {a});
