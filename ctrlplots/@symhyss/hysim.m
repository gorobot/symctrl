function varargout = hysim(sys, u, varargin)
%HSIM Compute the hybrid system response of a system to arbitrary inputs.
%   
%   [t, y] = HYSIM(sys, u, t) computes the response of a hybrid system to
%   an arbitrary input. 

% References:
% Lygeros, John, Claire Tomlin, and Shankar Sastry. "Hybrid systems:
% modeling, analysis and control." preprint (1999).

p = inputParser;
validateInput = @(U) ...
    validateattributes(U, {'sym', 'numeric', 'function_handle'}, ...
                          {'nonempty'});
validateTime = @(T) ...
    validateattributes(T, {'numeric'}, ...
                          {'nonempty', 'nonnegative', 'increasing'});
validateICs = @(P) ...
    validateattributes(P, {'numeric', 'cell'}, {'nonempty'});
validateVars = @(V) ...
    validateattributes(V, {'sym', 'cell'}, {'nonempty'});
addRequired(p, 'sys');
addRequired(p, 'u', validateInput);
addOptional(p, 'tspan', [0 5], validateTime);
addOptional(p, 'x0', cell.empty, validateICs);
addParameter(p, 'Vars', cell.empty, validateVars);
parse(p, sys, u, varargin{:});

tspan = p.Results.tspan;

x0 = p.Results.x0;
if ~iscell(x0)
    x0 = {x0};
end

if isempty(x0)
    x0 = {zeros(1, numel(sys.states))};
end

if numel(x0) > 1
    t = cell(size(x0));
    y = cell(size(x0));
end

for k = 1:numel(x0)
    ic = reshape(x0{k}, [], 1);
    [ts, ys] = hysolver(sys, u, tspan, ic);
    t{k} = ts;
    y{k} = ys;
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

