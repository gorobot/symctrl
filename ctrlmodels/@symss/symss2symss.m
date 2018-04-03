function T = symss2symss(sys, P)
%SYMSS2SYMSS State space similarity transformation.
% 
%   sys = SYMSS2SYMSS(sys, P) uses a similarity transform matrix, P, to
%   perform a similarity transform on system.
%   
%   The new state space model has the following form:
%       Dx = (P*A/P)x + (P*B)u
%        y = (C/P) + D

p = inputParser;
[A, B, C, D] = sys.getabcd();
validateMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, ...
                          {'nonempty', 'square', 'size', size(A)});
addRequired(p, 'sys');
addRequired(p, 'P', validateMatrix);
parse(p, sys, P);

if ~isa(P, 'sym')
    P = sym(P);
end

A = P*A/P;
B = P*B;
C = C/P;

T = sys;
T.f = A*T.states + B*T.inputs;
T.g = C*T.states + D*T.inputs;

end

