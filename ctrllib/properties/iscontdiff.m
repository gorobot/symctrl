function tf = iscontdiff(f, varargin)
%ISCONTDIFF Returns logical 1 (true) if a function is continuously
%differentiable at a point or logical 0 (false) if it is not.
% 
%   ISCONTDIFF(f, ...) checks for continuous differentiability of a
%   function by searching for discontinuities in a range. 
% 
%   ISCONTDIFF(f, var, x1, x2) checks for continuous differentiability of a
%   function with respect to var on the interval [x1 x2].

p = inputParser;
validateFunction = @(F) validateattributes(F, {'sym', 'function_handle'}, {'nonempty'});
validateSym = @(S) validateattributes(S, {'sym'}, {'nonempty'});
addRequired(p, 'f', validateFunction);
addOptional(p, 'var', sym.empty, validateSym);
addOptional(p, 'x1', -Inf);
addOptional(p, 'x2', Inf);
parse(p, f, varargin{:});

% Get differentiation variable.
if any(strcmp('var', p.UsingDefaults))
    S = symvar(f);
    idx = find(ismember(S, {'t', 's', 'p', 'z', 'q', 'x', 'y', 'z'}), 1);
    if isempty(idx)
        V = S(1);
    else
        V = S(idx);
    end
else
    V = p.Results.var;
end

x1 = p.Results.x1;
x2 = p.Results.x2;
x1default = any(strcmp('x1', p.UsingDefaults));
x2default = any(strcmp('x2', p.UsingDefaults));

df = diff(f, V);

if ~x1default && x2default
    try
        % Continuously differentiable at a point.
        flim = limit(df, V, x1);
        tf = ~isnan(flim);
        if ~tf
            dffun = symfun(df, V);
            tf = isequal(flim, dffun(x1));
        end
    catch ME
        if strcmp(ME.identifier, 'symbolic:kernel:DivisionByZero')
            tf = false;
            return;
        else
            rethrow(ME);
        end
    end
else
    dcont = feval(symengine, 'discont', df, V);
    % Check if discontinuities are in the range.
    tf = ~any(isAlways(x1 <= dcont & dcont <= x2));
end

end

