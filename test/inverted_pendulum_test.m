%% Test of Symbolic Variable Class
clear, clc, close all
syms m l b g
syms theta(t) T y

f1 = m*l^2*diff(theta, t, t) + b*l*diff(theta, t) + m*g*l*sin(theta) == T;
g1 = y == theta;

states = {theta, diff(theta, t)};
inputs = {T};
outputs = {y};

sv = symsv({f1}, {g1}, ...
    'states', states, ...
    'inputs', inputs, ...
    'outputs', outputs);

sv.linearize({T == 9.8});

sys = symss(sv);

G = symtf(sys)

