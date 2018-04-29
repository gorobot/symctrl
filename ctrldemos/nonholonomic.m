%% Nonholonomic Differential Drive System
% Nonholonomic differential drive system, with constants.
%
% d - the distance between the wheels.
syms x1 x2 x3 u1 u2 d

sys = symss;
sys.states = [x1, x2, x3];
sys.inputs = [u1, u2];

sys.f(1) = (u1 + u2)*cos(x3)/2;
sys.f(2) = (u1 + u2)*sin(x3)/2;
sys.f(3) = (u2 - u1)/d;

sys.g(1) = x1;
sys.g(2) = x2;
sys.g(3) = x3;

savedemo('nonholonomic', sys, {d});
