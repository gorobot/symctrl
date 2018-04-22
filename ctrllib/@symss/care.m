function [P, K] = care(sys, varargin)
%CARE Solve the continuous algebraic Riccati equation.
%
%   P = CARE(sys) solves the continuous algebraic Riccati equation for
%   a symbolic state-space model and returns the solution P.
%
%   P = CARE(sys, Q, R) solves the continuous algebraic Riccati equation
%   using the matrices Q and R. If omitted, Q defaults to I, and R defaults
%   to I.
%
%   [P, K] = CARE(sys, ...) solves the continuous algebraic Riccati
%   equation and returns the gain matrix, K.

%   References:
%   Arnold, William F., and Alan J. Laub. "Generalized eigenproblem
%   algorithms and software for algebraic Riccati equations." Proceedings
%   of the IEEE 72.12 (1984): 1746-1754.

p = inputParser;
[A, B] = sys.getabcd();
validateMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, ...
                       {'square', 'nonnegative', 'size', size(A)});
addRequired(p, 'sys');
addOptional(p, 'Q', eye(size(A)));
addOptional(p, 'R', eye(size(A)));
addParameter(p, 'exact', false);
parse(p, sys, varargin{:});

exact = p.Results.exact;

Q = p.Results.Q;
if ~issymmetric(Q)
    error('Q must be symmetric.');
end

R = p.Results.R;
if ~issymmetric(R)
    error('R must be symmetric.');
end

Ri = inv(R);

% Form the Hamiltonian.
H = [A, -B*Ri*B.'; -Q, -A.'];

if ~isempty(symvar(H))
    exact = true;
end

% Solve the continuous algebraic Riccati equation using the Hamiltonian.
P = slvham(H, 'exact', exact);

% Compute the gain matrix, K.
K = Ri*B.'*P;

end
