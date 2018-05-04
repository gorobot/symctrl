function varargout = nlsim2(sys, varargin)
%NLSIM2 Simulate a non-linear system in two variables.
%   Detailed explanation goes here

p = inputParser;

% Add extra parameters unique to this function.
addParameter(p, 'Trajectory', ...
    false, ...
    @(arg) validateattributes(arg, {'logical'}, {'scalar'}));

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
    vars = sys.states(1:2);
else
    vars = cell2sym(p.Results.Vars);
    if length(vars) ~= 2
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
    c = lines;

    for k = 1:numel(x0)
        ax.NextPlot = 'add';
        yp = y{k};
        h = plot(yp(:, 1), yp(:, 2));
        h.Color = c(2, :);
    end

    ax.NextPlot = current_state;
    ax.XLimMode = 'auto';
    ax.YLimMode = 'auto';
    ax.XLabel.String = char(vars(1));
    ax.YLabel.String = char(vars(2));

    if p.Results.Trajectory
        xl = ax.XLim;
        yl = ax.YLim;

        X = cell([1, 2]);
        [X{:}] = ndgrid(...
            linspace(xl(1), xl(2), 20), ...
            linspace(yl(1), yl(2), 20));

        nx = cell(size(sys.states));
        nx(:) = {'SUBX'};
        tx = sym(genvarname(nx, who));
        tf = subs(sys.f, sys.states, tx);
        Ffun = symfun(tf, tx);
        Y = Ffun(X{:});

        XVal = X(has(sys.states.', vars));
        YVal = Y(has(sys.states.', vars));

        ax.NextPlot = 'add';
        h = quiver(XVal{1}, XVal{2}, double(YVal{1}), double(YVal{2}));
        h.Color = c(1, :);

        ax.XLim = xl;
        ax.YLim = yl;
        ax.NextPlot = current_state;
    end

end

end
