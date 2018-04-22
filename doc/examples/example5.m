clear,clc

syms R C L s t
syms vC iL v(t)

R = 10;
C = 0.01;
L = 0.1;

sys = symss;
sys.states = [vC iL];
sys.inputs = v(t);

sys.f(1) = -(1/(R*C))*vC + (1/C)*iL;
sys.f(2) = -(1/L)*vC + (1/L)*v(t);

sys.g(1) = (1/R)*vC;

linsys = linearize(sys);

u = exp(-1*s)/s - exp(-2*s)/s + exp(-3*s)/s - exp(-4*s)/s + 20/(s+1000);
lsim(linsys, u);
