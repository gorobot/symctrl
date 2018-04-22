function validatesystem(sys, varargin)
%VALIDATESYSTEM Check validity of a system.
% 
%   VALIDATESYSTEM(sys, attributes) throws an error if system does not have
%   specified attributes.
% 
%   Attributes:
%       full - system must be fully defined.
%       
%       nmodes - system must have N modes.

p = inputParser;
addRequired(p, 'sys');
addOptional(p, 'attributes', cell.empty, ...
    @(arg) validateattributes(arg, {'cell'}, {'nonempty'}));
parse(p, sys, varargin{:});

attributes = p.Results.attributes;
va_ = @validateattributes;
mf_ = mfilename;
S = {'sym'};
N = {'numeric'};

for k = 1:numel(attributes)
    if ~ischar(attributes{k})
        continue;
    end
    
    switch attributes{k}
        % Attributes without arguments.
        case 'full'
            n = numel(sys.f);
            va_(sys.cond, S, {'size', [n, n]}, mf_, 'condition matrix');
            va_(sys.edge, N, {'size', [n, n]}, mf_, 'adjacency matrix');
        % Attributes with arguments.
        case 'nmodes'
            nmodes = getarg(attributes, k);
            va_(sys.f, S, {'numel', nmodes}, mf_, 'modes');
    end
end

    % Helper function to get arguments from list.
    function arg = getarg(attr, k)
        try
            arg = attr{k + 1};
            if ischar(arg)
                error(['Invalid argument to ''', attr{k}, '''.']);
            elseif ~isnumeric(arg)
                error(['Argument to ', attr{k}, ' must be numeric.']);
            elseif isempty(arg)
                error(['Argument to ', attr{k}, ' must not be empty.']);
            end
        catch ME
            if strcmp(ME.identifier, 'MATLAB:badsubscript')
                error(['Insufficient arguments to ''', attr{k}, '''.']);
            else
                rethrow(ME);
            end
        end
    end
end

