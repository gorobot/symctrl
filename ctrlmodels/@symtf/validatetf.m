function validatetf(G, varargin)
%VALIDATETF Check vlidity of a transfer function.
% 
%   VALIDATETF(G, attributes) throws an error if transfer function does not
%   have specified attributes.

p = inputParser;
addRequired(p, 'G');
addOptional(p, 'attributes', cell.empty, ...
    @(arg) validateattributes(arg, {'cell'}, {'nonempty'}));
parse(p, G, varargin{:});

attributes = p.Results.attributes;
va_ = @validateattributes;
mf_ = mfilename;
S = {'sym'};

for k = 1:numel(attributes)
    if ~ischar(attributes{k})
        continue;
    end
    
    switch attributes{k}
        % Attributes without arguments.
        case 'proper'
            for g = 1:numel(G.tf)
                if numel(G.num_{g}) > numel(G.den_{g})
                    error('Expected transfer function to be proper.');
                end
            end
        case 'SISO'
            va_(G.num_, {'cell'}, {'size', [1, 1]}, mf_, 'numerator');
            va_(G.den_, {'cell'}, {'size', [1, 1]}, mf_, 'denominator');
        % Attributes with arguments.
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

