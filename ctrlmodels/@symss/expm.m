function R = expm(sys)
%EXPM Compute the matrix exponential of a symbolic state space system.
% 
%   R = EXPM(SYS) computes the matrix exponential L^-1{inv(sI-A)}.
% 
%   The standard 'expm' function computes the matrix exponential using a
%   convergent power series method. While this method is formally defined
%   as the matrix exponential, in practice the computation of this matrix
%   can cause the Matlab to hang. Symbolically, it is easier to compute the
%   inverse laplace transform of inv(sI-A), and less error-prone.
p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);

parse(p, sys);

sys = p.Results.sys;

syms s t
Phi = inv(s*eye(size(sys.A)) - sys.A);
R = ilaplace(Phi, s, t);

end

