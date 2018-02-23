%% Test of No Specified States to Symbolic Variable Class
clear, clc, close all

% syms y
% class(y)
% clear y
% 
% syms y(t)
% class(y)
% clear y

% syms y(t) a b u(t)
% f1 = a*diff(y) + b*y == u;
% formula(f1)
% symvar(f1)
% symfun(formula(f1))

% syms(formula(f1))

syms y(t) u(t) a1 a2 a3 b0 y1

S = syms

f1 = diff(y, 3) + a1*diff(y, 2) + a2*diff(y) + 3*y == b0*u;
g1 = y1 == y;

% metaclass(y)
[r, sigma] = subexpr(formula(f1))
% ch = children(f1)
% ch = children(ch)
% ch = subs(ch)

sv = symsv(f1, {g1})
