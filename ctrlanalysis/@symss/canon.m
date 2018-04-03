function T = canon(sys, varargin)
%CANON Transform a state space model into a canonical form.
% 
%   T = CANON(sys, ...) converts a state space representation to a
%   canonical form via similarity transformation.
% 
%   T = CANON(sys, 'Type', t)
%   
%   Type can be one of the following:
%   - Controllable: 'c', 'C', 'co', 'Co', 'controllable', 'companion'
%   - Observable: 'o', 'O', 'ob', 'Ob', 'observable'
%   - Jordan: 'j', 'jordan', 'Jordan'
%   - Kalman: 'k', 'kalman', 'Kalman'
% 
%   See also symss/normal

%   References:
%   Antsaklis, Panos J., and Anthony N. Michel. A linear systems primer. 
%   Vol. 1. Boston: Birkhäuser, 2007.

p = inputParser;
validateType = @(T) ...
    ismember(T, {'c', 'C', 'co', 'Co', 'controllable', 'companion', ...
                 'o', 'O', 'ob', 'Ob', 'observable', ...
                 'j', 'J', 'jordan', 'Jordan', ...
                 'k', 'kalman', 'Kalman'});
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
addOptional(p, 'Type', 'c', validateType);
parse(p, sys, varargin{:});

type = p.Results.Type;

switch type
    % Controllable or companion form.
    case {'c', 'C', 'co', 'Co', 'controllable', 'companion'} 
        T = ctrbform(sys);
        
    % Observable form.
    case {'o', 'O', 'ob', 'Ob', 'observable'} 
        T = obsvform(sys);
        
    % Jordan form.
    case {'j', 'J', 'jordan', 'Jordan'}
        T = jordanform(sys);

    % Kalman decomposition.
    case {'k', 'kalman', 'Kalman'}
        T = kalmanform(sys);
end

end

