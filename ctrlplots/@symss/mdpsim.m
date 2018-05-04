function varargout = mdpsim(sys, m, varargin)
%MDPSIM Compute the response of a system using an MDP as input.
%
%   [t, y] = MDPSIM(sys, m, tspan) computes the response of a system to
%   an input policy given by an MDP.

p = inputParser;

addParameter(p, 'MdpOptions', struct, ...
    @(arg) validateattributes(arg, {'struct'}, {'nonempty'}));

% Validate sim inputs.
validatesimargs(p, sys, zeros(size(sys.inputs)), varargin{:});

% Verify MDP is compatible with system.
nX = numel(sys.states);
validateattributes(m.X, {'numeric'}, {'ndims', nX});

nU = numel(sys.inputs);
for k = 1:numel(m.U)
    validateattributes(m.U{k}, {'sym', 'numeric'}, {'numel', nU});
end

% Ensure a decision interval.
mdpopts = p.Results.MdpOptions;
if isempty(mdpopts.Td)
    mdpopts = mdpset(m, mdpopts, 'Td', 1);
end

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

slvparams = {'Solver', p.Results.Solver, ...
             'MdpOptions', mdpopts};

for k = 1:numel(x0)
    ic = reshape(x0{k}, [], 1);
    [ts, ys] = mdpsolver(sys, m, tspan, ic, options, slvparams{:});
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
