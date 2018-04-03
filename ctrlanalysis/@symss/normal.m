function T = normal(sys, varargin)
%NORMAL Transform a state space system into a normal form.
%   
%   T = NORMAL(sys, ...) converts a state space representation to a normal
%   form.
% 
%   T = NORMAL(sys, 'Type', t)
% 
%   See also symss/canon

p = inputParser;
validateType = @(T) ...
    ismember(T, {'normal'});
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
addOptional(p, 'Type', 'normal', validateType);
parse(p, sys, varargin{:});

type = p.Results.Type;

switch type
    case 'normal'
        T = normalform(sys);
end

end

