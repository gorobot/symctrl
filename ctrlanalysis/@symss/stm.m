function Phi = stm(sys)
%STM Compute the state transition matrix of a symbolic state space system.
%   
%   Compute the state transition matrix defined by:
%       Phi = (sI - A)^-1
%   
%   Phi = STM(sys) computes the state transition matrix of a system.

syms s
A = sys.A;

Phi = inv(s*speye(size(A)) - A);
    
end

