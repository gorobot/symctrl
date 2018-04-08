%% Bouncing Ball Demo System
% 

% g - gravitational acceleration
% k - damping coefficient
syms g k

syms x1 x2
sys = symss;
sys.states = [x1, x2];

f1 = [ x2; g];
f2 = [-x1; -k*x2];

sys.f = piecewise(x1 >= 0, f1, x1 <= 0 & x2 <= 0, f2);

savedemo('ball', sys, {g, k});
