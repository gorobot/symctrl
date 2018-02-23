function D = ctrldemo(name, varargin)
%CTRLDEMO Loads a demo system from memory.
% 
%   Detailed explanation goes here
p = inputParser;

validateName = @(arg) validateattributes(arg, {'char', 'string'}, {'nonempty'});
addRequired(p, 'name', validateName);

% addParameter(p, 'Equations', true);
% addParameter(p, 'StateVariables', true);
% addParameter(p, 'StateSpace', false);
% addParameter(p, 'TransferFunction', false);

parse(p, name, varargin{:});

% getEquations = p.Results.Equations;
% getStateVariables = p.Results.StateVariables;
% getStateSpace = p.Results.StateSpace;
% getTransferFunction = p.Results.TransferFunction;

S = load(name);
D = S.demosys;

end

