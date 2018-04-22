%% Pendulum (Full)
% Pendulum equation.

syms m l g k
syms x1 x2 u
sys = symss;
sys.states = [x1 x2];
sys.inputs = u;
sys.f(1) = x2;
sys.f(2) = -(k*l*x2 - u + g*l*m*sin(x1))/(l^2*m);
sys.g(1) = x1;

savedemo('pendulum4', sys, {m, l, g, k});
