%% Pendulum (No Friction)
% Pendulum equation.

syms x1 x2
sys = symss;
sys.states = [x1 x2];
sys.f(1) = x2;
sys.f(2) = -sin(x1);

savedemo('pendulum', sys);
