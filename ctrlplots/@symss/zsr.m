function Ys = zsr(sys, u)
%ZSR Get the zero state response of a system.
%   The zero state response is defined as:
%
%                     -1
%   Ys(s) = (C(sI - A)  B + D)u(s) = G(s)u(s)
%
%   And equivalently in the time domain as:
%
%            /t  A(t-s)
%   ys(t) = C|  e      B u(s) ds + Du(t) = G(t) * u(t)
%            /0
%

p = inputParser;
validateInput = @(U) ...
    validateattributes(U, {'sym', 'numeric'}, {'nonempty'});
addRequired(p, 'sys');
addRequired(p, 'u', validateInput);
parse(p, sys, u);

syms s
[~, B, C, D] = sys.getabcd();
Phi = stm(sys);

G = C*Phi*B + D;

Ys = G*u;

end
