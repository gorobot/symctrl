%% Tunnel-Diode Circuit (Constants Defined)
% 

syms x1 x2 u

h(x1) = 17.76*x1 - 103.79*x1^2 + 229.62*x1^3 - 226.31*x1^4 + 83.72*x1^5;

sys = symss;
sys.states = [x1 x2];
sys.inputs = u;

sys.f(1) = (-h(x1) + x2)*0.5;
sys.f(2) = (-x1 - 1.5*x2 + 1.2)*0.2;

sys.g(1) = x1;

savedemo('tunneldiode', sys);

