function sys = diagform(sys)
%DIAGFORM Diagonal canonical form.
%   
%   T = DIAGFORM(sys) converts a state space model to diagonal
%   canonical form.
% 
%   The transfer function defined by:
% 
%   Y(s)   b0*s^(n) + b1*s^(n-1) + ... + bn
%   ---- = --------------------------------
%   U(s)      (s + p1)*(s + p2)*(s + p3)
% 
%   Converts to the state space representation:
% 
%   .   | -p1  0   0  |    | 1 |
%   x = |  0  -p2  0  |x + | 1 |u
%       |  0   0  -p3 |    | 1 |
%   
%   y = |  c1  c2  c3 |x + b0*u

end

