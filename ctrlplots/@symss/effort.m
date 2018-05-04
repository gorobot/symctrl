function varargout = effort(sys, varargin)
%EFFORT Compute the control effort of a system to arbitrary inputs.
%
%   [t, y] = EFFORT(sys, u, t) computes the control effort of a system and
%   returns the time series data in 't' and the control efforts in 'y'.
%
%   EFFORT uses the simulated output of a system to compute the control
%   effort. It uses the simulated outputs as inputs to the control function
%   'u' to compute the control inputs at each time step.
%
%   When no outputs are specified, EFFORT plots the output.

p = inputParser;

% Validate sim inputs.
validatesimargs(p, sys, varargin{:});

tspan = p.Results.tspan;
x0 = p.Results.x0;

if ~iscell(x0)
    x0 = {x0};
end

if numel(x0) > 1
    t = cell(size(x0));
    u = cell(size(x0));
end

T = sym('t');

[ts, ys] = nlsim(sys, varargin{:});

tx = subvars(sys);

% Create a Matlab function.
Ufun = symfun(subs(p.Results.u, sys.states, tx), [T; tx]);
odefun = matlabFunction(Ufun, 'Vars', {T, tx});

for k = 1:numel(x0)
    t{k} = ts{k};
    u{k} = odefun(ts{k}.', ys{k}.').';
end

if nargout ~= 0
    varargout{1} = t;
    varargout{2} = u;
else
    ax = gca;
    current_state = ax.NextPlot;

    for k = 1:numel(x0)
        ax.NextPlot = 'add';
        plot(t{k}, u{k})
    end

    ax.NextPlot = current_state;
    ax.XLimMode = 'auto';
    ax.YLimMode = 'auto';
    ax.XLabel.String = 'Time (seconds)';
    ax.YLabel.String = 'Amplitude';
end

end
