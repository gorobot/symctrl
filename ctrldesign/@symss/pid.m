function u = pid(sys, varargin)
%PID Summary of this function goes here
%   Detailed explanation goes here

p = inputParser;
addRequired(p, 'sys');
addOptional(p, 'Kp', 0);
addOptional(p, 'Ki', 0);
addOptional(p, 'Kd', 0);
parse(p, sys, varargin{:});

Kp = p.Results.Kp;
Ki = p.Results.Ki;
Kd = p.Results.Kd;

syms s
u = Kp + Ki/s + Kd*s;

end

