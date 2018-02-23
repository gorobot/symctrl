%% Test for Derivatives of Input
clear, clc, close all
syms y(t) u(t) a1 a2 a3 b0 b1 y1
f1 = diff(y, 3) + a1*diff(y, 2) + a2*diff(y) + a3*y == b0*diff(u) + b1*u;
g1 = y1 == y;

sv = symsv({f1}, {g1}, ...
    'states', {y, diff(y), diff(y, 2) - b0*u}, ...
    'inputs', {u}, ...
    'outputs', {y1})

sys = symss(sv);

sysC = canon(sys, 'type', 'c');

sysC.B
sysC.C
