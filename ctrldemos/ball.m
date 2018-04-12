%% Bouncing Ball Demo System
% 

% g - gravitational acceleration
% k - damping coefficient
syms g k

syms x1 x2
sys = symhyss;
sys.states = [x1, x2];

sys.f(1, 1) = x2;
sys.f(1, 2) = g;
sys.cond(1) = x1 >= 0;

sys.f(2, 1) = -x1;
sys.f(2, 2) = -k*x2;
sys.cond(2) = x1 <= 0 & x2 <= 0;

% sys.f = piecewise(x1 >= 0, f1, x1 <= 0 & x2 <= 0, f2);

savedemo('ball', sys, {g, k});
