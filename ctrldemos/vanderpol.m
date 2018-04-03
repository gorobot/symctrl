%% Van der Pol Equation
% Van der Pol equation.
clear, clc, close all, reset(symengine)

syms x1 x2
sys = symss;
sys.states = [x1 x2];
sys.f(1) = -x2;
sys.f(2) = x1 - (x1^2 + 1)*x2;

savedemo('vanderpol', sys);
