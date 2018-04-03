%% Mass Spring Damper 2
% Mass, spring, damper system, two frictionless masses.

% References:
% Antsaklis, Panos J., and Anthony N. Michel. A linear systems primer.
% Vol. 1. Boston: Birkhäuser, 2007.

syms M1 B B1 K K1 M2 B2 K2
syms u1 u2
syms x1 x2 x3 x4

sys = symss;
sys.states = [x1 x2 x3 x4];
sys.inputs = [u1 u2];

sys.f(1) = x2;
sys.f(2) = -(B*x2 - u1 - B*x4 + B1*x2 + K*x1 - K*x3 + K1*x1)/M1;
sys.f(3) = x4;
sys.f(4) = -(u2 + B*x4 - B1*x2 + B2*x4 - K*x1 + K*x3 + K2*x3)/M2;

sys.g(1) = x1;

savedemo('massspring2', sys, {M1, B, B1, K, K1, M2, B2, K2});
