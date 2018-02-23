function block(sys, varargin)
%BLOCK Convert transfer function to Simulink block diagram.
%   Detailed explanation goes here

p = inputParser;

validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);

validateAs = @(As) ismember(As, {'Block', 'StateSpace', 'TransferFunction'});
addParameter(p, 'As', 'Block', validateAs);

addParameter(p, 'Name', 'untitled');

parse(p, sys, varargin{:});

As = p.Results.As;
Name = p.Results.Name;

% Create a new Simulink model.
open_system(new_system(Name));

n = length(sys.A);
layout = [];
for k = 1:n
    blockName = strcat(Name, '/', 'Block', num2str(k));
    sumName = strcat(Name, '/', 'Block', num2str(k), 'Sum');
    add_block('simulink/Continuous/Integrator', blockName);
    add_block('simulink/Math Operations/Sum', sumName);
    
%     layout = 
end

end

