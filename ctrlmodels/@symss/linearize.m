function sys = linearize(sys, eqns, varargin)
%LINEARIZE Linearize a system around an equilibrium point.
%
%   Detailed explanation goes here 
%   
%   The input parameter 'eqns' should be a system of symbolic functions 
%   organized into a cell array. Typically, 
p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);
addOptional(p, 'eqns', eqns);
addParameter(p, 'limit', false);

parse(p, sys, eqns, varargin{:});

sys = p.Results.sys;
eqns = p.Results.eqns;

% Return a copy of the equations, replacing their values with the values
% obtained from the workspace. This effectively converts the cell array of
% symbolic functions into an array of symbolic functions.
eqns = subs(eqns);

% Substitute the values into the state matrices.
sys.A = subs(sys.A, lhs(eqns), rhs(eqns));
sys.B = subs(sys.B, lhs(eqns), rhs(eqns));
sys.C = subs(sys.C, lhs(eqns), rhs(eqns));
sys.D = subs(sys.D, lhs(eqns), rhs(eqns));

end

