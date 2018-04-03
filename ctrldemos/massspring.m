%% Spring-Mass-Damper Demo
% Mass, spring, damper system, single frictionless mass.
clear, clc, close all, reset(symengine)

syms M C K B
syms x1 x2 u

sys = symss;
sys.states = [x1 x2];
sys.inputs = u;

sys.f(1) = x2;
sys.f(2) = (-K*x1 - C*x2)/M + B*u/M;

sys.g(1) = x1;

savedemo('massspring', sys, {M, C, K, B});
