function varargout = hysim(sys, varargin)
%HSIM Compute the hybrid system response of a system to arbitrary inputs.
%
%   [t, y] = HYSIM(sys, u, t) computes the response of a hybrid system to
%   an arbitrary input.

% References:
% Lygeros, John, Claire Tomlin, and Shankar Sastry. "Hybrid systems:
% modeling, analysis and control." preprint (1999).

p = inputParser;

% Validate sim inputs.
validatesimargs(p, sys, varargin{:});

u = p.Results.u;
tspan = p.Results.tspan;
x0 = p.Results.x0;

if ~iscell(x0)
    x0 = {x0};
end

t = cell(size(x0));
y = cell(size(x0));

if any(strcmp('Vars', p.UsingDefaults))
    vars = sys.states;
else
    vars = cell2sym(p.Results.Vars);
    if length(vars) ~= 1
        error('Incorrect number of output variables.');
    end
end

for k = 1:numel(x0)
    ic = reshape(x0{k}, [], 1);
    [ts, ys] = hysolver(sys, u, tspan, ic);
    t{k} = ts;
    y{k} = ys(:, has(sys.states.', vars));
end

if nargout ~= 0
    varargout{1} = t;
    varargout{2} = y;
else
    ax = gca;
    current_state = ax.NextPlot;

    for k = 1:numel(x0)
        ax.NextPlot = 'add';
        plot(t{k}, y{k})
    end

    ax.NextPlot = current_state;
    ax.XLimMode = 'auto';
    ax.YLimMode = 'auto';
    ax.XLabel.String = 'Time (seconds)';
    ax.YLabel.String = 'Amplitude';
end

end
