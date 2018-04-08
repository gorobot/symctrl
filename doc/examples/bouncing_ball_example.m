%% Bouncing Ball Example
% Example showing response of a hybrid system of a bouncing ball.

syms x1 x2 u
g = -9.8;
sys = symss;
sys.states = [x1, x2];
sys.inputs = u;
f1 = [x2; g];
f2 = [-x1; -0.8*x2];
sys.g(1) = x1;

sys.f = piecewise(x1 >= 0, f1, x1 <= 0 & x2 <= 0, f2);


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
