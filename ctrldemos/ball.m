%% Bouncing Ball
% The bouncing ball is a canonical hybrid switching model with 2 modes. The
% first mode is a continuous "flow" mode, where the ball is in free-fall. The
% second is a discontinuous "jump" mode, where the ball contacts the ground.
%
% Model:
%
%   Mode 1                  Mode 2
%    _______________         ___________________
%   |               |       |                   |
%   | dx1/dt = x2   | ----> | dx1/dt = -x1      |
%   | dx2/dt = -g   |       | dx2/dt = -k*x2    |
%   |               |       |                   |
%   | x1 >= 0       | <---- | x1 <= 0 & x2 <= 0 |
%   |_______________|       |___________________|
%
% Constants:
% g - gravitational acceleration
% k - damping coefficient

syms g k

syms x1 x2
sys = symhyss;
sys.states = [x1, x2];

sys.f(1, 1) = x2;
sys.f(1, 2) = -g;
sys.guard(1, 2) = x1 >= 0;

sys.f(2, 1) = -x1;
sys.f(2, 2) = -k*x2;
sys.guard(2, 1) = x1 <= 0 & x2 <= 0;
sys.guard(2, 2) = 0;

savedemo('ball', sys, {g, k});
