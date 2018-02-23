function block(sv, varargin)
%BLOCK Convert transfer function to Simulink block diagram.
%   Detailed explanation goes here

p = inputParser;

validateStateVars = @(sv) isa(sv, 'symsv');
addRequired(p, 'G', validateStateVars);

validateAs = @(As) ismember(As, {'Block', 'StateSpace', 'TransferFunction'});
addParameter(p, 'As', 'Block', validateAs);

addParameter(p, 'Name', 'untitled');

parse(p, sv, varargin{:});

As = p.Results.As;
Name = p.Results.Name;

% Create a new Simulink model.
open_system(new_system(Name));

n = length(sv.A);
layout = [];
for k = 1:n
    blockName = strcat(Name, 'Block', num2str(k));
    sumName = strcat(Name, 'Block', num2str(k), 'Sum');
    add_block('simulink/Continuous/Integrator', blockName);
    add_block('simulink/Math Operations/Sum', sumName);
    
%     layout = 
end

end

