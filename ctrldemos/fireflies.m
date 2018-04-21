%% Firefly Synchronization
% The firefly synchronization demo for N fireflies is a hybrid system
% showing a biological example of fireflies synchronizing their flashing.
% 
% When one firefly flashes, the other fireflies jump to a higher energy,
% eventually synchronizing their flashes. 
% 
% Model:
% 
%   Mode 1                  Mode 2
%    ___________         ________________________
%   |           |       |                        |
%   | dx/dt = 1 | ----> | dx/dt = (1 + epsilon)x |
%   |           |       |                        |
%   | x < 0     | <---- | x >= 1                 |
%   |___________|       |________________________|
% 
% Constants:
% epsilon - synchronization threshold

syms epsilon

N = 10;

x = sym('x', [N, 1]);

sys = symhyss;
sys.states = x;

sys.cond(1, 1) = 1;
sys.cond(1, 2) = 1;
sys.cond(2, 1) = 1;

for k = 1:N
    sys.f(1, k) = 1;
    sys.cond(1, 2) = x(k) < 1 & sys.cond(1, 2);

    sys.f(2, k) = (1 + epsilon).*x(k) - (1 + epsilon).*x(k)*heaviside((1 + epsilon).*x(k) - 1);
    sys.cond(2, 1) = x(k) >= 1 & sys.cond(2, 1);
end

savedemo('fireflies', sys, {epsilon});
