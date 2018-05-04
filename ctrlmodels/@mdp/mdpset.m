function options = mdpset(m, varargin)
%MDPSET Create or modify options for MDP simulation.
%
%   options = MDPSET(m, options, ...) creates or modifies options for MDP
%   simulation.
%
%   Options can be set outside of MDPSET, and there is no error checking until
%   the options are used in a function. You can check them manually by running
%
%   MDPSET(m, options)
%
%   Parameters:
%       StateFunction - A function for determining the discrete state of a
%           system using continuous dynamics.
%       Td - decision interval.
%       TermEvent - A function for determining the terminating
%           conditions of the MDP solver.

va_ = @validateattributes;

p = inputParser;
addRequired(p, 'm');
if isstruct(varargin{1}) && nargin > 2
    addOptional(p, 'options', struct);
    p.StructExpand = false;
end
addParameter(p, 'StateFunction', [], ...
    @(arg) va_(arg, {'symfun', 'function_handle'}, {'nonempty'}));
addParameter(p, 'Td', [], ...
    @(arg) va_(arg, {'double'}, {'positive', 'nonempty'}));
addParameter(p, 'TermEvent', [], ...
    @(arg) va_(arg, {'symfun', 'function_handle'}, {'nonempty'}));
parse(p, m, varargin{:});

% List of all possible options.
allopts = {'StateFunction', 'Td', 'TermEvent'};

% Get previous options structure.
if any(strcmp('options', p.Parameters))
    options = p.Results.options;
    if isempty(options)
        options = struct;
    end
else
    options = struct;
end

% Populate the structure.
for k = 1:numel(allopts)
    % If the parameter is using a default, set the value to [].
    if any(strcmp(allopts{k}, p.UsingDefaults))
        if ~isfield(options, allopts{k})
            options.(allopts{k}) = [];
        end
    else
        options.(allopts{k}) = p.Results.(allopts{k});
    end
end

end
