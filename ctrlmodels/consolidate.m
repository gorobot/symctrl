function newEqns = consolidate(eqns)
%CONSOLIDATE Simplifies a set of equations for state 
%   Detailed explanation goes here

p = inputParser;

validateEqns = @(eqns) validateattributes(eqns, {'cell'}, {'notempty'});

addRequired(p, 'eqns', validateEqns);

parse(p, eqns);

eqns = p.Results.eqns;

end

