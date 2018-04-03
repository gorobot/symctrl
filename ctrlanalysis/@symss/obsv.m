function Ob = obsv(sys)
%OBSV Computes the observability matrix of a state space model.
%   
%   Ob = OBSV(sys) returns the observability matrix
%   
%       [C; C*A; C*A^2; ...]
% 
%   See also obsvs

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'hasoutput'}));
parse(p, sys);

[A, ~, C, ~] = sys.getabcd();
Ob = obsvs(A, C);

end

