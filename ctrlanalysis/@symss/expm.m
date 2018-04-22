function phi = expm(sys)
%EXPM Compute the matrix exponential of a symbolic state space system.
% 
%   Compute the matrix exponential defined by:
%       phi = L^-1{(sI-A)^-1}
% 
%   phi = EXPM(sys) computes the matrix exponential of a system.

%   The standard 'expm' function computes the matrix exponential using a
%   convergent power series method. While this method is formally defined
%   as the matrix exponential, in practice the computation of this matrix
%   can cause Matlab to hang. Symbolically, it is easier to compute the
%   inverse laplace transform of (sI-A)^-1, and less error-prone.

syms s t
Phi = stm(sys);
phi = ilaplace(Phi, s, t);

end

