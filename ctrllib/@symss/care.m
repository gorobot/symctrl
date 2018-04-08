function [P, K] = care(sys, varargin)
%CARE Solve the continuous algebraic Riccati equation.
%   
%   P = CARE(sys) solves the continuous algebraic Riccati equation for
%   a symbolic state-space model and returns the solution P.
% 
%   P = CARE(sys, Q, R, S) solves the continuous algebraic Riccati equation
%   using the matrices Q, R, and S. If omitted, Q defaults to I, R defaults
%   to I, and S defaults to 0.
% 
%   [P, K] = CARE(sys, ...) solves the continuous algebraic Riccati
%   equation and returns the gain matrix, K.

%   References:
%   Arnold, William F., and Alan J. Laub. "Generalized eigenproblem 
%   algorithms and software for algebraic Riccati equations." Proceedings 
%   of the IEEE 72.12 (1984): 1746-1754.

p = inputParser;
[A, B, C, ~] = getabcd(sys);
% validateMatrix = @(M) isequal(M, M.') && isequal(size(A), size(M));
validateMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, ...
                       {'square', 'nonnegative', 'size', size(A)});
addRequired(p, 'sys');
addOptional(p, 'Q', eye(size(A)), validateMatrix);
addOptional(p, 'R', eye(size(A)));
addOptional(p, 'S', C.'*C);
parse(p, sys, varargin{:});

Q = p.Results.Q;
if ~issymmetric(Q)
    error('Q must be symmetric.');
end

R = p.Results.R;
if ~issymmetric(R)
    error('R must be symmetric.');
end

S = p.Results.S;

Ri = inv(R);

% Form the Hamiltonian.
H = [A, -B*Ri*B.'; -S.'*Q*S, -A.'];

% Solve the continuous algebraic Riccati equation using the Hamiltonian.
P = slvham(H);

% Compute the gain matrix, K.
K = Ri*B.'*P;

end

