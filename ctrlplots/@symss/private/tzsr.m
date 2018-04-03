function ys = tzsr(sys, u)
%TZSR Get the zero state response of a system.
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

syms s t
[~, B, C, D] = getabcd(sys);
Phi = stm(sys);

G = C*Phi*B + D;
Gt = ilaplace(G, s, t);

ys = conv(Gt, u, 'valid');

end

