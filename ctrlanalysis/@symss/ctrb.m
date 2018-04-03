function Co = ctrb(sys)
%CTRB Computes the controllability matrix of a state space model.
%   
%   Co = CTRB(sys) returns the controllability matrix 
%   
%       Co = [B, A*B, A^2*B, ...]
% 
%   See also ctrbs

%   References:
%   Antsaklis, Panos J., and Anthony N. Michel. A linear systems primer. 
%   Vol. 1. Boston: Birkhäuser, 2007.

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'hasinput'}));
parse(p, sys);

[A, B, ~, ~] = sys.getabcd();
Co = ctrbs(A, B);

end

