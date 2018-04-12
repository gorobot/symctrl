%% Bouncing Ball Example
% Example showing response of a hybrid system of a bouncing ball.

g = -9.8;

%% Define the System Dynamics
% Define the system dynamics. These include the dynamics for each mode, as
% well as the switching (guard) conditions.
syms x1 x2 u
sys = symhyss;
sys.states = [x1, x2];

sys.f(1, 1) = x2;
sys.f(1, 2) = g;
sys.cond(1, 2) = x1 >= 0;

sys.f(2, 1) = -x1;
sys.f(2, 2) = -0.8*x2;
sys.cond(2, 1) = x1 <= 0 & x2 <= 0;

%% Simulate the System
tspan = [0 10];
ic = {[5, 5]};

[t, y] = hysim(sys, sym(0), tspan, ic);

t = t{:};
y = y{:};

%% Plot the Position Response
plot(t, y(:, 1))

%% Plot the Velocity Response
plot(t, y(:, 2))

%% Plot the Position vs. Velocity Response
plot(y(:, 1), y(:, 2))
