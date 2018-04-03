clear, clc

syms x u
sys = symss;
sys.states = x;
sys.inputs = u;
sys.f(1) = -x^3 + u*x^2;

V = x^2/2;

GV = gradient(V)

ISS = GV.*sys.f
