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
%       nlsim2(sys, tspan, ic)
% 
%   Parameters:
%   - 'Points' specify how many points should be in the elastic ring.
% 
%   - 'T0' specify the initial temperature (default 2).
% 
%   - 'CoolingFactor' specify the temperature cooling factor (default
%   1.02).
% 
%   - 'ZeroSpacing' specify the initial distance of the elastic ring from
%   the origin (default 1E-3).
% 
%   - 'ComputationTime' specify the maximum allowed computation time in
%   seconds (default 30).
% 
%   - 'Radial' specify whether the points should move in a strictly radial
%   direction, or if the points can move along the trajectories (default
%   false).
% 
%   Tips:
%   The cooling factor is a positive number > 1. Small changes to the
%   cooling factor can have a dramatic effect. Lower values produce less
%   conservative results. It is recommended to change the cooling factor in
%   increments of 1E-2 or 1E-3 if needed.
% 
%   If 'Radial' is set, the points move along the projection of the
%   trajectory evaluated at the point with a radial vector from the origin
%   to the point. This option can be useful if the points move too far down
%   a limit cycle during computation, but can give points outside the
%   region of attraction if the cooling factor is too high.
%   
%   See also boundary, inpolygon, symss/roa, symss/nlsim2

p = inputParser;
addRequired(p, 'sys');
addParameter(p, 'Points', 20);
addParameter(p, 'T0', 2);
addParameter(p, 'CoolingFactor', 1.02);
addParameter(p, 'ZeroSpacing', 1E-3);
addParameter(p, 'ComputationTime', 30);
addParameter(p, 'Radial', false);
addParameter(p, 'Trajectory', false);
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
    
%     plot(R(:, 1), R(:, 2), 'o')
%     hold on
%     plot(R(b, 1), R(b, 2))
%     quiver(R(:, 1), R(:, 2), PF(:, 1), PF(:, 2));
% %     quiver(R(:, 1), R(:, 2), NF(:, 1), NF(:, 2));
% %     plot(R(in, 1) + PF(in, 1)/T, R(in, 2) + PF(in, 2)/T, 'rx')
% %     plot(R(in, 1) + NF(in, 1)/2, R(in, 2) + NF(in, 2)/2, 'ks')
%     quiver(R(in, 1), R(in, 2), R(in, 1) - 0, R(in, 2) - 0)
%     
% %     chg = dot(R(in, :) - 0, (PF(in, :)/norm(PF(in, :))), 2);
%     
% %     quiver(R(in, 1), R(in, 2), chg(:, 1), chg(:, 2), 'AutoScale', 'off')
%     hold off
    
%     R(in, :) = R(in, :) - PF(in, :)/T;
%     R(in, :) = R(in, :) - sqrt((PF(in, 1)/T).^2 + (PF(in, 2)/T).^2);

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
    
    rgx = xlim*1.5;
    rgy = ylim*1.5;
    xlim(rgx);
    ylim(rgy);

    [X, Y] = meshgrid(linspace(rgx(1), rgx(2), 20), ...
                      linspace(rgy(1), rgy(2), 20));

    ax = gca;
    axcs = ax.NextPlot;
    
    % Plot function trajectories.
    if p.Results.Trajectory
        ax.NextPlot = 'add';
        F1 = subs(sys.f(1), sys.states, {X; Y});
        F2 = subs(sys.f(2), sys.states, {X; Y});
        q = quiver(ax, X, Y, F1, F2);
        q.AutoScale = 'on';
        q.AlignVertexCenters = 'on';
    end
    
    ax.NextPlot = axcs;
end

end

