function Yi = tzir(sys, x0)
%TZIR Get the zero input response of a system.
%   The zero input response is defined as:
% 
%                    -1
%   Yi(s) = C(sI - A)  x(0)
% 
%   And equivalently in the time domain:
%   
%             At
%   yi(t) = Ce  x(0)
% 

syms s t
[~, ~, C, ~] = getabcd(sys);
phi = ilaplace(stm(sys), s, t);

Yi = C*phi*x0;

end

