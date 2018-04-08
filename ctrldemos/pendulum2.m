%% Pendulum 2 (No Constants)
% Pendulum equation.
clear, clc, close all, reset(symengine)

syms x1 x2 u
sys = symss;
sys.states = [x1 x2];
sys.inputs = u;
sys.f(1) = x2;
sys.f(2) = -sin(x1) - x2 + u;

savedemo('pendulum2', sys);
