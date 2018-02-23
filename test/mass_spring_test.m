%% Dual Mass Spring Test
clear all, clc, close all

syms M1 B B1 K K1 M2 B2 K2 t y positive
syms fo1(t) fo2(t)
syms y1(t) y2(t)

f1 = M1*diff(y1, t, t) + (B + B1)*diff(y1, t) + (K + K1)*y1 - B*diff(y2, t) - K*y2 == fo1;
f2 = M2*diff(y2, t, t) + (B + B2)*diff(y2, t) + (K + K2)*y2 - B1*diff(y1, t) - K*y1 == -fo2;

g1 = y == y1 + y2;

% findstates({f1, f2})

states = {y1, diff(y1, t), y2, diff(y2, t)};
inputs = {fo1, fo2};
outputs = {y};

sv = symsv({f1, f2}, {g1}, ...
    'states', states, ...
    'inputs', inputs, ...
    'outputs', outputs);

% assume(y1(t) == 0)
% assumeAlso(y2(t) == 0)
% assumeAlso(fo1(t) == 0)
% assumeAlso(fo2(t) == 0)
% assumptions.'

% eqx = eqpt(sv);
% sv.Dx
% 
% nsv = simplify(sv, 'Steps', 10, 'Clear', false);
% 
% nsv.Dx
% 
% nsv = linearize(sv, { ...
%     y1 == 0, ...
%     fo1 == 0 ...
%     });
% 
% nsv.Dx
% 
% assumptions.'

% sys = symss(sv);
% 
% f_1 = sv.f{4};
% f_2 = sys.f{4};
% simplify(f_1 - f_2, 10)

% 
% sys.A
% sys.B
% sys.C
% sys.D
% 
% sys2 = symss(nsv);
% [iscontrollable(sys2), isobservable(sys2)]
% 
% sys.A
% sys.B
% sys.C
% sys.D
% % 
% % G = symtf(sys);
% 
% % [T, rhp, lhp] = rhtable(G)
% 
% % Co = ctrb(sys)
% 
% % [A, B, C, D] = kd(sys)
% 
% % Jsys = canon(sys, 'Form', 'j')
% % 
% % Jsys.A
% % Jsys.B
% % Jsys.C
% % Jsys.D
