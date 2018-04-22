clear, clc

syms m l k g
syms theta(t) u y

% m = 1;
% l = 10;
% b = 10;
% g = 9.8;

f1 = m*l^2*diff(theta, t, t) + k*l*diff(theta, t) + m*g*l*sin(theta) == u;
g1 = y == theta;

sys = eom2symss(f1, [theta, diff(theta)]);
sys.inputs = u;
sys.g(1) = theta;

% linsys = linearize(sys);
% 
% lsim(linsys, sym(0))

% syms s
% u = 10*exp(-1*s)/s + 2*exp(-2*s)/s - 10.5*exp(-3.5*s)/s;
% lsim(linsys, u);

% sys = symss;
% sys.states = {theta, diff(theta)};
% sys.inputs = T;
% 
% sys.f(1) = diff(theta);
% sys.f(2) = rhs(isolate(f1, diff(theta, 2)));
% 
% sys.g(1) = theta;
% 
% linsys = linearize(sys);
% 
% sys.A
% linsys.A
% 
% syms s
% u = exp(-1*s)/s - exp(-2*s)/s + exp(-3*s)/s - exp(-4*s)/s + 1/(s+1);
% lsim(linsys, u)


