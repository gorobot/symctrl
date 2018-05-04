function varargout = nlsim(sys, varargin)
%NLSIM Simulate a non-linear system in one variable.
%   Detailed explanation goes here

%   References:
%   Khalil, Hassan K. "Noninear systems."
%   Prentice-Hall, New Jersey 2.5 (1996): 5-1.

p = inputParser;

% Validate sim inputs.
validatesimargs(p, sys, varargin{:});

u = p.Results.u;
tspan = p.Results.tspan;
x0 = p.Results.x0;
options = p.Results.options;

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

slvparams = {'Solver', p.Results.Solver};

for k = 1:numel(x0)
    ic = reshape(x0{k}, [], 1);
    [ts, ys] = nlsolver(sys, u, tspan, ic, options, slvparams{:});
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
