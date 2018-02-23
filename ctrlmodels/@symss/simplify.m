function sys = simplify(sys, varargin)
%SIMPLIFY Simplify a system using assumptions.
%
%   sys = SIMPLIFY(sys, ...)
%   
%   Uses assumptions defined in the workspace to simplify a state space
%   system. 
p = inputParser;

validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);

validateSteps = @(Steps) validateattributes(Steps, {'numeric'}, {'positive', 'integer'});
addParameter(p, 'Steps', 1, validateSteps);

parse(p, sys, varargin{:});

sys = p.Results.sys;
Steps = p.Results.Steps;

% Apply the assumptions to the state matrices.
sys.A = simplify(sys.A, 'Steps', Steps);
sys.B = simplify(sys.B, 'Steps', Steps);
sys.C = simplify(sys.C, 'Steps', Steps);
sys.D = simplify(sys.D, 'Steps', Steps);

end
