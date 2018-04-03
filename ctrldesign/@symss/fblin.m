function [v, gamma, alpha] = fblin(sys)
%FBLIN Summary of this function goes here
%   Detailed explanation goes here

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'full', 'numinputs', 1}));
parse(p, sys);

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

while true
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
gamma = LgLfh{end};
alpha = -Lfh{end}/gamma;

v = gamma\(sys.inputs - alpha);

end

