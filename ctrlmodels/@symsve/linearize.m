function sv = linearize(sv, eqns, varargin)
%LINEARIZE Linearize a system around an equilibrium point.
%
%   Detailed explanation goes here 
%   
%   The input parameter 'eqns' should be a system of symbolic functions 
%   organized into a cell array.
p = inputParser;

validateSys = @(sv) isa(sv, 'symsv');
validateEqns = @(eqns) validateattributes(eqns, {'cell'}, {'nonempty'});

addRequired(p, 'sv', validateSys);
addRequired(p, 'eqns', validateEqns);
addParameter(p, 'limit', false);

parse(p, sv, eqns, varargin{:});

sv = p.Results.sv;
eqns = p.Results.eqns;

% Begin by replacing any symbolic variables which match the state variables
% with their values. This protects against unwittingly replacing the lhs of
% the state variables later on.
eqns = subs(eqns, [lhs(sv.x), lhs(sv.u)], [rhs(sv.x), rhs(sv.u)]);

% Substitute the new values of the linearization values into the state
% variable equations.
sv.x = lhs(sv.x) == subs(rhs(sv.x), lhs(eqns), rhs(eqns));
sv.u = lhs(sv.u) == subs(rhs(sv.u), lhs(eqns), rhs(eqns));

% Once we have substituted the values in the state variable equations, we
% can do the same for the first derivative and output equations,
% essentially f and g. We begin by replacing the state variables in f and g
% with their actual values from the substituted equations, and then we
% convert any remaining values to the state variables.

sv.Dx = lhs(sv.Dx) == subs(rhs(sv.Dx), ...
    [lhs(sv.x), lhs(sv.u)], [rhs(sv.x), rhs(sv.u)]);
sv.y = lhs(sv.y) == subs(rhs(sv.y), ...
    [lhs(sv.x), lhs(sv.u)], [rhs(sv.x), rhs(sv.u)]);

% sv.Dx = lhs(sv.Dx) == subs(rhs(sv.Dx), ...
%     [rhs(sv.x), rhs(sv.u)], [lhs(sv.x), lhs(sv.u)]);
% sv.y = lhs(sv.y) == subs(rhs(sv.y), ...
%     [rhs(sv.x), rhs(sv.u)], [lhs(sv.x), lhs(sv.u)]);

sv = simplify(sv, 'Steps', 2, 'Clear', true);

end

