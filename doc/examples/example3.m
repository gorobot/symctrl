clear, clc

syms C L R E
syms x1 x2 u
h(x1) = E/R - x1/R;

sys = symss;
sys.states = [x1 x2];
sys.inputs = u;

sys.f(1) = (-h(x1) + x2)/C;
sys.f(2) = (-x1 - R*x2 + u)/L;

linsys = linearize(sys);

sys.A
linsys.A

nlsim2(linsys|{C==0.1,L==0.1,R==10,u==0})
