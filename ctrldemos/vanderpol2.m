%% Van der Pol Equation (Reverse Time)
% Van der Pol equation in reverse time.

syms x1 x2
sys = symss;
sys.states = [x1 x2];
sys.f(1) = -x2;
sys.f(2) = x1 + (x1^2 - 1)*x2;

savedemo('vanderpol2', sys);
