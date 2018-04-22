function [V, P, dV] = lyap(sys, varargin)
%LYAP Solves the lyapunov equation for a system.
%
%   V = LYAP(sys) solves the Lyapunov matrix equation for a symbolic
%   state-space model and returns the equation V.
%
%   V = LYAP(sys, Q) solves the Lyapunov matrix equation for a symbolic
%   state space model using the matrix Q. If omitted, Q defaults to I.
%
%   [V, P, dV] = LYAP(sys, Q) solves the Lyapunov matrix equation and
%   returns the solution P, the Lyapunov function V = x.'*P*x, and the
%   Lyapunov function derivative dV = -x.'*Q*x.
%
%   Tips:
%       In almost all cases, it is necessary to use a linearized system for
%       nonlinear state space models to compute the Lyapunov equation.
%
%       Rank-deficient state matrices will not produce a unique result, and
%       the P matrix may not be symmetric. Check the rank of A before
%       running the function.
%
%   See also symss/care, lyap, pinv

p = inputParser;
A = sys.getabcd();
validateMatrix = @(M) isequal(M, M.') && isequal(size(M), size(A));
addRequired(p, 'sys')
addOptional(p, 'Q', eye(size(A)), validateMatrix);
parse(p, sys, varargin{:});

Q = p.Results.Q;

% Form the Hamiltonian.
H = [A, zeros(size(A)); -Q, -A.'];

% Solve the Lyapunov equation using the Hamiltonian.
P = slvham(H);

% Compute the symbolic Lyapunov function and derivative.
V = sys.states.'*P*sys.states;
dV = -sys.states.'*Q*sys.states;

end
