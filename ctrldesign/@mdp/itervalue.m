function varargout = itervalue(m, H, varargin)
%ITERVALUE Summary of this function goes here
%   Detailed explanation goes here

% References:
% Poole, David L., and Alan K. Mackworth. Artificial Intelligence: foundations
% of computational agents. Cambridge University Press, 2010.
%
% Russell, Stuart J., and Peter Norvig. Artificial intelligence: a modern
% approach. Malaysia; Pearson Education Limited,, 2016.

p = inputParser;
addRequired(p, 'm');
addRequired(p, 'H');
addParameter(p, 'AbsTol', 1E-9);
parse(p, m, H, varargin{:});

tol = p.Results.AbsTol;

nX = numel(m.X);
nU = numel(m.U);

P = m.P;
R = m.R;

k = 0;

g = m.gamma;

% Precompute P*R
PR = zeros(nX, nU);
for a = 1:nU
    PR(:, a) = sum(P(:, :, a).*R(:, :, a), 2);
end

V0 = zeros([nX, 1]);
Vi = V0;

while true
    Q = zeros(size(PR));
    for a = 1:nU
        Q(:, a) = PR(:, a) + P(:, :, a)*g*V0;
    end

    [Vi, idx] = max(Q, [], 2);

    if all(abs(Vi - V0) < tol)
        break;
    elseif k >= H
        break;
    else
        k = k + 1;
    end

    V0 = Vi;
end

policy = zeros([nX, nU]);
for k = 1:numel(idx)
    policy(k, idx(k)) = 1;
end

if nargout ~= 0
    varargout{1} = Vi;
    varargout{2} = policy;
    varargout{3} = reshape(idx, size(m.X));
else
    m.policy = policy;
end

end
