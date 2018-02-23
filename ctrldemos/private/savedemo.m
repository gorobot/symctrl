function savedemo(name, varargin)
%UNTITLED12 Summary of this function goes here
%   Detailed explanation goes here
p = inputParser;

validateName = @(arg) validateattributes(arg, {'char', 'string'}, {'nonempty'});
addRequired(p, 'name', validateName);

validateParams = @(P) validateattributes(P, {'sym', 'cell'}, {'nonempty'});

addParameter(p, 'Variables', {}, validateParams);

addParameter(p, 'StateEquations', {}, validateParams);
addParameter(p, 'OutputEquations', {}, validateParams);

addParameter(p, 'States', {}, validateParams);
addParameter(p, 'Inputs', {}, validateParams);
addParameter(p, 'Outputs', {}, validateParams);

parse(p, name, varargin{:});

Variables = p.Results.Variables;
StateEquations = p.Results.StateEquations;
OutputEquations = p.Results.OutputEquations;
States = p.Results.States;
Inputs = p.Results.Inputs;
Outputs = p.Results.Outputs;

% Compute the state variables, state space, and transfer function.
sv = symsv(StateEquations, OutputEquations, ...
    'States', States, ...
    'Inputs', Inputs, ...
    'Outputs', Outputs);

sys = symss(sv);
G = symtf(sys);

% Create the structure to save to file.
demosys = struct();

demosys.SymbolicVariables = Variables;
demosys.StateVariables = States;
demosys.InputVariables = Inputs;
demosys.OutputVariables = Outputs;

demosys.StateEquations = StateEquations;
demosys.OutputEquations = OutputEquations;

demosys.StateVariables = sv;
demosys.StateSpace = sys;
demosys.TransferFunction = G;

[folder, ~, ~] = fileparts(mfilename('fullpath'));
name = fullfile(folder, name);
save(name, 'demosys')

end

