function T = normalform(sys)
%NORMALFORM Summary of this function goes here
%   Detailed explanation goes here

validatesystem(sys, {'full', 'numinputs', 1});
if ~iscontrollable(sys)
    error('System is not controllable.');
end

n = numel(sys.states);

% Lie derivative.
L = @(f, h) gradient(f, sys.states).'*h;

% Find f(x) and g(x).
for k = 1:numel(sys.f)
    C = coeffs(sys.f(k), sys.inputs, 'All');
    if numel(C) == 2
        f{k} = C(2);
        g{k} = C(1);
    else
        f{k} = C;
        g{k} = 0;
    end
end

f = cell2sym(f).';
g = cell2sym(g).';

rho = 1;
Lfh{1} = sys.g;
% psi{1} = genvarname('PSI', sym2cell([symvar(sys.f), symvar(sys.g)]));
% psi{1} = sym(genvarname('PSI', arrayfun(@(x) {char(x)}, ...
%                                         [symvar(sys.f), symvar(sys.g)])));
% D{1} = sys.g;
while true
    D{rho} = Lfh{rho};
    Lfh{rho + 1} = L(Lfh{rho}, f);
    LgLfh{rho} = L(Lfh{rho}, g);
    
    C = coeffs(Lfh{rho + 1} + LgLfh{rho}*sys.inputs, sys.inputs, 'All');
    %      + LgLfh{rdeg + 1}*sys.inputs
    rho = rho + 1;
    
    if numel(C) > 1
        break;
    end
end

% Compute relative degree.
rdeg = rho - 1;

% Compute gamma and alpha.
gamm = LgLfh{end};
alph = -Lfh{end}/gamm;

nd = numel(D);
Ac = [zeros(nd - 1, 1), eye(nd - 1); zeros(1, nd)];
Bc = [zeros(nd - 1, 1); 1];
Cc = [1, zeros(1, nd - 1)];
D = cell2sym(D).';

T = sys;
T.f = Ac*D + Bc*gamm*(T.inputs - alph);
T.g = Cc*D;

if n - rdeg > 0
    warning('The system has a relative degree less than n. ');
    warning(['Attempting to find a diffeomorphism for T(x). ', ...
             'This functionality is experimental.']);
    % Find phi.
    syms x
    phi = symfun('phi(x)', x);
    gphi = arrayfun(@(x) diff(phi(x)), sys.states);
    eqn = gphi.'*g;
    dvar = intersect(symvar(eqn), sys.states);
    
    for k = 1:numel(dvar)
        eqn = int(eqn, dvar(k));
    end
    
    % Find the coefficients of phi.
    eqn2 = subs(eqn, phi, sym('PHI'));
    C = coeffs(eqn2, sym('PHI'));
    
    T.f = [C; T.f];
end

end

