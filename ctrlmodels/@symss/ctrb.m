function Co = ctrb(sys)
%UNTITLED18 Summary of this function goes here
%   Detailed explanation goes here
p = inputParser;

validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);

parse(p, sys);

sys = p.Results.sys;

Co = ctrbs(sys.A, sys.B);

end

