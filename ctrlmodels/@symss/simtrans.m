function sys = simtrans(sys, P)
%SIMTRANS State space similarity transformation.
% 
%   sys = sys*P
% 
%   sys = SIMTRANS(sys, P)
% 
%   Uses a similarity transform matrix, P, to transform the system into an
%   equivalent system. 

p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);

validateP = @(P) validateattributes(P, ...
    {'numeric', 'sym'}, {'square', 'nonempty'});
addRequired(p, 'P', validateP);

parse(p, sys, P);

sys = p.Results.sys;
P = p.Results.P;

if ~isa(P, 'sym')
    P = sym(P)
end

% Substitute the values into the state matrices.
sys.A = P*sys.A/P;
sys.B = P*sys.B;
sys.C = sys.C/P;
sys.D = sys.D;

end

