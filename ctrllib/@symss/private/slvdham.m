function P = slvdham(H, varargin)
%SLVDHAM Solves the discrete ARE using the Hamiltonian method.
%   Detailed explanation goes here

p = inputParser;
addRequired(p, 'H', @(H) issymplectic(H));
addParameter(p, 'exact', false);
parse(p, H, varargin{:});

% Compute the Schur decomposition.
if p.Results.exact
    [U, S] = schurs(H);
    [U, ~] = ordschurs(U, S, 'udi');
else
    [U, S] = schur(double(H));
    [U, ~] = ordschur(U, S, 'udi');
end

U = mat2cell(U, size(H)/2, size(H)/2);

cs = warning('off', 'all');

% Compute the solution to the algebraic Riccati equation.
P = U{2, 1}/U{1, 1};

% Compute the inverse using the Moore-Penrose pseudoinverse if the
% inverse does not exist.
if any(isinf(P))
    P = U{2, 1}*pinv(U{1, 1});
end

if ~p.Results.exact
    P = sym(P);
end

warning(cs);

end

