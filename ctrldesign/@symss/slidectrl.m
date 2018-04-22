function u = slidectrl(sys, S, varargin)
%SLIDECTRL Computes a control input for sliding mode control.
%
%   u = SLIDECTRL(sys, S, ...) computes a control input for sliding mode
%   control using a matrix defining the sliding surfaces S. The total
%   control is defined by the equation:
%
%   u = ueq - us
%
%   Where the equivalent control 'ueq' is defined by:
%              -1
%   ueq = -(SB)  SAx
%
%   and the surface control is defined by:
%                -1
%   us = eta*(SB)  sign(sigma)
%
%   'eta' is defined by:
%
%   eta = L + alpha/sqrt(2)
%
%   The switching function, which defaults to 'sign' can be changed by
%   setting the 'SwitchingFunction' parameter.
%
%   See also symss/slide

p = inputParser;
addRequired(p, 'sys');
addRequired(p, 'S');
addOptional(p, 'eta', 1);
addParameter(p, 'SwitchingFunction', @sign);
parse(p, sys, S, varargin{:});

sf = p.Results.SwitchingFunction;

sigma = S*sys.states;

% Compute equivalent control.
[A, B] = sys.getabcd();
ueq = -(S*B)\S*A*sys.states;

% Compute surface control.
eta = p.Results.eta;
us = eta*inv(S*B)*sf(sigma);

% Compute total control.
u = ueq - us;

end
