%% Pendulum (With Constants)
% Pendulum equation.

syms m l g k
syms x1 x2
sys = symss;
sys.states = [x1 x2];
sys.f(1) = x2;
sys.f(2) = -g*sin(x1)/l - k*x2/m;

savedemo('pendulum3', sys, {m, l, g, k});
