function varargout = nlsim(sys, u, varargin)
%NLSIM Simulate a non-linear system in one variable.
%   Detailed explanation goes here

%   References:
%   Khalil, Hassan K. "Noninear systems." 
%   Prentice-Hall, New Jersey 2.5 (1996): 5-1.

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
validateSolver = @(S) ...
    validateattributes(S, {'function_handle'}, {'nonempty'});
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
addRequired(p, 'u', validateInput);
addOptional(p, 'tspan', [0 5], validateTime);
addOptional(p, 'x0', cell.empty, validateICs);
addParameter(p, 'vars', cell.empty, validateVars);
addParameter(p, 'solver', @ode45, validateSolver);
parse(p, sys, u, varargin{:});

tspan = p.Results.tspan;

x0 = p.Results.x0;
if ~iscell(x0)
    x0 = {x0};
end

if numel(x0) > 1
    t = cell(size(x0));
    y = cell(size(x0));
end

if any(strcmp('vars', p.UsingDefaults))
    vars = sys.states(1);
else
    vars = cell2sym(p.Results.vars);
    if length(vars) ~= 1
        error('Incorrect number of output variables.');
    end
end

for k = 1:numel(x0)
    ic = reshape(x0{k}, [], 1);
    [ts, ys] = nlsolver(sys, u, tspan, ic);
    t{k} = ts;
    y{k} = ys(:, has(sys.states.', vars));
end

if nargout ~= 0
    varargout{1} = t;
    varargout{2} = y;
else
    plotoutput(y, tspan);
    
%     ax = gca;
%     current_state = ax.NextPlot;
%     
%     for k = 1:numel(x0)
%         ax.NextPlot = 'add';
%         plot(t{k}, y{k})
%     end
%     
%     ax.NextPlot = current_state;
%     ax.XLimMode = 'auto';
%     ax.YLimMode = 'auto';
%     ax.XLabel.String = 'Time (seconds)';
%     ax.YLabel.String = 'Amplitude';
end

end

