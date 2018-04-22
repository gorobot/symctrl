function tf = islyap(P, Q)
%ISLYAP Check Lyapunov criteria. 
%   Detailed explanation goes here

p = inputParser;
addRequired(p, 'P');
addRequired(p, 'Q');
parse(p, P, Q);

% Check conditions on P.
tf = any(all(isAlways(P > 0)));

if tf
    tf = any(all(isAlways(Q >= 0)));
end

end

