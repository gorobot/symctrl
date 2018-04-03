function varargout = lsim(sys, u, varargin)
%LSIM Compute the linear response of a system to arbitrary inputs.
% 
%   y = LSIM(sys, u, t) computes the linear response of a system to an
%   arbitrary input where 'u' is a symbolic s-domain input signal or
%   time-series data, and 't' is a time vector.
%   
%   y = LSIM(sys, u, t, x0) computes the linear response of a system to an
%   arbitrary input where 'u' is time-series data, 't' is a time vector,
%   and 'x0' are the initial conditions.


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
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
addRequired(p, 'u', validateInput);
addOptional(p, 'tspan', [0 5], validateTime);
addOptional(p, 'x0', cell.empty, validateICs);
addParameter(p, 'vars', cell.empty, validateVars);
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
    y = cell(size(x0));
end

for k = 1:numel(x0)
    ic = reshape(x0{k}, [], 1);
    y{k} = linsolver(sys, u, tspan, ic);
    y{k} = subs(y{k}, sys.states, ic);
end

if nargout ~= 0
    varargout{1} = y;
else
    plotoutput(y, tspan);
    
%     if length(y) == 1
%         h = fplot(y);
%         h.XRange = tspan; 
%         h.XRangeMode = 'auto'; 
%         xlabel('Time (seconds)');
%         ylabel('Amplitude');
%     else
%         [m, n] = size(y{:});
%         for k = 1:numel(y{:})
%             subplot(n, m, k)
%             h = fplot(y{:}(k));
%             h.XRange = tspan; 
%             h.XRangeMode = 'auto'; 
%             xlabel('Time (seconds)');
%             ylabel('Amplitude');
% %             title(['Output ', num2str(m), ' for input ', num2str(n)]);
%         end
%     end
end

end

