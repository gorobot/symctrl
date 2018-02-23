function sys = subs(sys, old, new)
%SUBS Replace a symbolic variable in state space.
%   Detailed explanation goes here

p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);
addRequired(p, 'old');
addRequired(p, 'new');

parse(p, sys, old, new);

sys = p.Results.sys;
old = p.Results.old;
new = p.Results.new;

sys.A = subs(sys.A, old, new);
sys.B = subs(sys.B, old, new);
sys.C = subs(sys.C, old, new);
sys.D = subs(sys.D, old, new);

end
