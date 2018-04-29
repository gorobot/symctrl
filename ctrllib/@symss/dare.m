function [P, K] = dare(sys, varargin)
%DARE Solve the discrete algebraic Riccati equation.
%
%   P = DARE(sys) solves the discrete algebraic Riccati equation for
%   a symbolic state-space model and returns the solution P.
%
%   P = DARE(sys, Q, R) solves the discrete algebraic Riccati equation
%   using the matrices Q and R. If omitted, Q defaults to I, and R defaults
%   to I.
%
%   [P, K] = DARE(sys, ...) solves the discrete algebraic Riccati
%   equation and returns the gain matrix, K.

% References:
% Kucera, Vladimir. "The discrete Riccati equation of optimal control."
% Kybernetika 8.5 (1972): 430-447.

p = inputParser;
[A, B] = sys.getabcd();
validateMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, ...
                       {'square', 'nonnegative', 'size', size(A)});
addRequired(p, 'sys');
addOptional(p, 'Q', eye(size(A)));
addOptional(p, 'R', eye(min(size(B))));
addParameter(p, 'exact', false);
parse(p, sys, varargin{:});

Q = p.Results.Q;
if ~issymmetric(Q)
    error('Q must be symmetric.');
end

R = p.Results.R;
if ~issymmetric(R)
    error('R must be symmetric.');
end

Ai = inv(A).';
Ri = inv(R);

BB = B*Ri*B.';
% CC = C.'*Q*C;
CC = Q;

% Form the symplectic matrix.
H = [A + BB*Ai*CC, -BB*Ai; -Ai*CC, Ai];

% Solve the continuous algebraic Riccati equation using the Hamiltonian.
P = slvdham(H, 'exact', p.Results.exact);

% Compute the gain matrix, K.
K = (R + B.'*P*B)\B.'*P*A;

end
