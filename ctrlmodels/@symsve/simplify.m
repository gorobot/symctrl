function sv = simplify(sv, varargin)
%SIMPLIFY Simplify state variables using assumptions.
%
%   sv = SIMPLIFY(sv, ...)
%   
%   Uses assumptions defined in the workspace to simplify a state variable
%   object.
% 
%   If the 'Clear' flag is set, the assumptions on the state variables are
%   cleared.
p = inputParser;

validateSv = @(sv) isa(sv, 'symsv');
addRequired(p, 'sv', validateSv);

validateSteps = @(Steps) validateattributes(Steps, {'numeric'}, {'positive', 'integer'});
addParameter(p, 'Steps', 1, validateSteps);

addParameter(p, 'Clear', false);

parse(p, sv, varargin{:});

sv = p.Results.sv;
Steps = p.Results.Steps;
Clear = p.Results.Clear;

% Store the current assumptions.
a = assumptions;

% Apply the assumptions to the state variable equations.
sv.x = lhs(sv.x) == simplify(rhs(sv.x), 'Steps', Steps);
sv.u = lhs(sv.u) == simplify(rhs(sv.u), 'Steps', Steps);

% Replace the updated assumptions in the derived equations.
assume(sv.x);
assumeAlso(sv.u);

dx = lhs(sv.Dx);
sv.Dx = simplify(sv.Dx, 'Steps', Steps);
for k = 1:length(dx)
    sv.Dx(k) = isolate(sv.Dx(k), dx(k));
end

y = lhs(sv.y);
sv.y = simplify(sv.y, 'Steps', Steps);
for k = 1:length(y)
    sv.y(k) = isolate(sv.y(k), y(k));
end

assume(sv.x, 'clear');
assume(sv.u, 'clear');

% Restore the prior assumptions.
assume(a);

% Clear the assumptions for further computation.
if Clear
    assume(sv.x, 'clear');
    assume(sv.u, 'clear');
end

end

