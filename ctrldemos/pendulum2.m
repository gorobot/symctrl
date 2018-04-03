%% Pendulum 2 (No Constants)
% Pendulum equation.
clear, clc, close all, reset(symengine)

syms x1 x2
sys = symss;
sys.states = [x1 x2];
sys.f(1) = x2;
sys.f(2) = -sin(x1) - x2;

savedemo('pendulum2', sys);
