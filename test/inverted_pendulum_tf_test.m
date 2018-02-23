%% Test of Symbolic Transfer Function Class
clear, clc, close all
syms m l b g
syms theta(t) T(t) y

f1 = m*l^2*diff(theta, t, t) + b*l*diff(theta, t) + m*g*l*sin(theta) == T;
g1 = y == theta;


vars = {T, theta};


syms s
teqn = laplace(f1);

cond = length(vars);
for k = 1:numel(vars)
    el = vars{k};
    cond(k) = el(0) == 0;
end

teqn = isolate(teqn, laplace(vars(2), t, s))
% coeffs(rhs(teqn), s, 'All')




% syms Y
% teqn = subs(teqn, laplace(vars

% states = {theta, diff(theta, t)};
% inputs = {T};
% outputs = {y};
% 
% sv = symsv({f1}, {g1}, ...
%     'states', states, ...
%     'inputs', inputs, ...
%     'outputs', outputs);
% 
% sv.linearize({T == 9.8});
% 
% sys = symss(sv);
% 
% G = symtf(sys)

