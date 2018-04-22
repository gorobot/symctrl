function varargout = reach(sys, X, varargin)
%REACH Computes a backward-reachable region for a given state.
%
%   R = REACH(sys, X) computes the backward-reachable region for a state X.
%
%   [R, S] = REACH(sys, X, ...) computes the backward-reachable region for
%   a state X, and also returns the points surrounding the final set, S,
%   denoting the region where the system will reach X in Tf seconds.
%
%   REACH(____) if no output is specified, the function will plot the
%   region.
%
%   The function creates a ring of points around the state X and performs
%   gradient ascent along the function trajectories in order to find the
%   boundary of a shape that gives the backward-reachable region of initial
%   conditions that will allow a system to reach the desired state.
%
%   Use BOUNDARY or CONVHULL in conjunction with INPOLYGON to estimate
%   whether an initial condition is within the backward-reachable region.
%
%   Parameters:
%       Points - specify the number of points in the ring (default 20).
%       Ts - specify the sample time (default 1E-3).
%       Tf - specify the final time (default 10).
%       ZeroSpacing - The radial distance of the ring from the target
%           point, X (default 1E-3).
%       ComputationTime - The maximum computation time of the function, in
%           seconds (default 30).
%
%   Tips:
%       The approximated region is more accurate when the sampling time
%       Ts is small. However, a smaller sampling time can lead to long
%       computation times for the function. Try using a relaxed function
%       first, before decreasing the sampling time.
%
%   See also symss/elroa

p = inputParser;
validateNumber = @(N) ...
    validateattributes(N, {'numeric'}, {'scalar', 'positive'});
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
addRequired(p, 'x');
addParameter(p, 'Points', 20, validateNumber);
addParameter(p, 'Ts', 1E-3, validateNumber);
addParameter(p, 'Tf', 10, validateNumber);
addParameter(p, 'ZeroSpacing', 1E-3, validateNumber);
addParameter(p, 'ComputationTime', 30, validateNumber);
parse(p, sys, X, varargin{:});

np = p.Results.Points;
zs = p.Results.ZeroSpacing;
t = p.Results.ComputationTime;

Ts = p.Results.Ts;
Tf = p.Results.Tf;

[tx, ~, tf] = subvars(sys);
PFfun = symfun(tf, tx);

% Create polar circle and convert to cartesian.
R = [zs*ones([np + 1, 1]), linspace(0, 2*pi, np + 1).'];
R = R(1:end - 1, :);
R = [R(:, 1).*cos(R(:, 2)), R(:, 1).*sin(R(:, 2))];

% Move to current point.
R = R + X{:};
PF = R;

k = 0;

orig = warning('off');

tic
while true
    k = k + Ts;

    % Compute the trajectories.
    nPF = PFfun(PF(:, 1), PF(:, 2));
    nPF = reshape(nPF, 1, []);
    nPF = double(cell2sym(nPF))*Ts;

    % Take the negative gradient.
    nPF = PF - nPF;

    % Remove points within the shape.
    b = boundary(R);
    inR = inpolygon(nPF(:, 1), nPF(:, 2),...
        R(b, 1), R(b, 2));

    b = boundary(nPF);
    inPF = inpolygon(R(:, 1), R(:, 2),...
        nPF(b, 1), nPF(b, 2));

    % Add new points.
    R = [R(~inPF, :); [nPF(~inR, 1), nPF(~inR, 2)]];

    % Set new starting points.
    PF = nPF;

    if k >= Tf
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
    varargout{2} = PF;
else
    b = boundary(R);
    plot(R(b, 1), R(b, 2));
end

end
