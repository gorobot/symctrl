%% Firefly Synchronization Example
% Example showing firefly synchronization for 10 fireflies.

%% Define a Hybrid State-Space Model
syms epsilon

%%
% Set the number of fireflies to model. Each firefly is represented by a
% single state variable.
N = 10;

x = sym('x', [N, 1]);

sys = symhyss;
sys.states = x;

%%
% Set the continuous state. 
sys.cond(1, 1) = 1;

%%
% Define the modes and the guard conditions.
sys.cond(1, 2) = 1;
sys.cond(2, 1) = 1;

for k = 1:N
    sys.f(1, k) = 1;
    sys.cond(1, 2) = x(k) < 1 & sys.cond(1, 2);

    sys.f(2, k) = (1 + epsilon).*x(k) - (1 + epsilon).*x(k)*heaviside((1 + epsilon).*x(k) - 1);
    sys.cond(2, 1) = x(k) >= 1 & sys.cond(2, 1);
end

%% Simulate the System
x0 = rand(N, 1);
tspan = [0 5];

%%
% Set the system constants.
sys = subs(sys, epsilon, 0.2);

%%
% Run the hybrid system simulator.
hysim(sys, 0, tspan, {x0})
