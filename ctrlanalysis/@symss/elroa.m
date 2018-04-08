function varargout = elroa(sys, varargin)
%ELROA Elastic estimation of region of attraction.
%   
%   R = ELROA(sys, ...) estimates the region of attraction around the
%   origin using an elastic method.
% 
%   The function creates a ring of points around the origin and grows the
%   points until they encompass the region of attraction. The boundary
%   created by the points is an estimation of the region of attraction and
%   is not exact. 
% 
%   Use BOUNDARY or CONVHULL in conjunction with INPOLYGON to estimate
%   whether an initial condition is within the region of attraction.
% 
%   Example (For initial condition [1 1]):
%       R = ELROA(sys)
%       b = convhull(R)
%       inpolygon(1, 1, R(b, 1), R(b, 2))
% 
%   Use NLSIM2 to plot the trajectories at the points on the region of
%   attraction boundary.
% 
%   Example:
%       R = ELROA(sys)
%       ic = num2cell(R, 2)
%       tspan = [0 10]
%       nlsim2(sys, 0, tspan, ic)
% 
%   Parameters:
%       Points - specify the number of points in the ring (default 20).
%       T0 - specify the initial temperature (default 2).
%       CoolingFactor - specify the cooling factor (default 1.02).
%       ZeroSpacing - specify the radial distance of the ring from the
%           origin (default 1E-3).
%       ComputationTime - The maximum computation time of the function, in
%           seconds (default 30).
%       Radial - specify whether the points should move in a strictly
%           radial direction, or if the points can move along the
%           trajectories (default false).
% 
%   Tips:
%       The cooling factor is a positive number > 1. Small changes to the
%       cooling factor can have a dramatic effect. Lower values produce
%       less conservative results. It is recommended to change the cooling
%       factor in increments of 1E-2 or 1E-3 if needed.
% 
%       If 'Radial' is set, the points move along the projection of the
%       trajectory evaluated at the point with a radial vector from the
%       origin to the point. This option can be useful if the points move
%       too far down a limit cycle during computation, but can give points
%       outside the region of attraction if the cooling factor is too high.
%   
%   See also boundary, convhull, inpolygon, symss/roa, symss/nlsim2

p = inputParser;
validateNumber = @(N) ...
    validateattributes(N, {'numeric'}, {'scalar', 'positive', 'integer'});
addRequired(p, 'sys');
addParameter(p, 'Points', 20, validateNumber);
addParameter(p, 'T0', 2, validateNumber);
addParameter(p, 'CoolingFactor', 1.02, validateNumber);
addParameter(p, 'ZeroSpacing', 1E-3, validateNumber);
addParameter(p, 'ComputationTime', 30, validateNumber);
addParameter(p, 'Radial', false);
parse(p, sys, varargin{:});

np = p.Results.Points;
zs = p.Results.ZeroSpacing;
t = p.Results.ComputationTime;

radial = p.Results.Radial;
cf = p.Results.CoolingFactor;

T0 = p.Results.T0;
k = 1;

[tx, ~, tf, ~] = varsub(sys);
PFfun = symfun(tf, tx);

% Create polar circle and convert to cartesian.
R = [zs*ones([np + 1, 1]), linspace(0, 2*pi, np + 1).'];
R = R(1:end - 1, :);
R = [R(:, 1).*cos(R(:, 2)), R(:, 1).*sin(R(:, 2))];

orig = warning('off');

tic
while true
    % Cooling factor.
    T = T0*cf^k;
    k = k + 1;
    
    % Compute the trajectories.
    PF = PFfun(R(:, 1), R(:, 2));
    PF = reshape(PF, 1, []);
    PF = double(cell2sym(PF))/T;
    
    b = convhull(R);
    
    in = inpolygon(R(:, 1) + PF(:, 1), R(:, 2) + PF(:, 2),...
        R(b, 1), R(b, 2));
    
    if radial
        chg = (dot(PF(in, :), R(in, :) - 0, 1)/vecnorm(R(in, :) - 0, 2, 1).^2)*(R(in, :) - 0);
    else
        chg = PF(in, :);
    end
    
    R(in, :) = R(in, :) - chg;
    
    if ~any(in)
        break;
    elseif ~any(chg > 1E-5)
        break;
    elseif toc > t
        warning(orig);
        warning('Computation time exceeded.');
        break;
    end
end

warning(orig);

if nargout ~= 0
    varargout{1} = R;
else
    b = convhull(R);
    plot(R(b, 1), R(b, 2));
end

end

