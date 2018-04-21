%% Bouncing Ball Example
% Example showing response of a hybrid system of a bouncing ball.

%% Define the System Dynamics
% Define the system dynamics. These include the dynamics for each mode, as
% well as the switching (guard) conditions.
sys = ctrldemo('ball');
sys = subs(sys, [g, k], [9.81, 0.8]);

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
