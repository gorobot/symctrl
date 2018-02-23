function Ob = obsv(sys)
%OBSV Summary of this function goes here
%   Detailed explanation goes here
p = inputParser;

validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);

parse(p, sys);

sys = p.Results.sys;

Ob = obsvs(sys.A, sys.C);

end

