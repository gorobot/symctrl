%% Tunnel-Diode Circuit Demo
clear, clc, close all, reset(symengine)

syms C L E R y
syms iC(t) vC(t) iL(t) vL(t) iR(t) h(vC)

f1 = C*diff(vC) == -h(vC) + iL;
f2 = L*diff(iL) == -vC - R*iL + E;

g1 = y == -h(vC);

% [rF, rV, T] = reduceRedundancies({f1, f2}, [vC, iL])

savedemo('tunnel_diode', ...
    'Variables', {C, L, R}, ...
    'StateEquations', {f1, f2}, ...
    'OutputEquations', {g1}, ...
    'States', {vC, iL}, ...
    'Inputs', {E}, ...
    'Outputs', {y});
