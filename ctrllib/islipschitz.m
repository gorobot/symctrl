function tf = islipschitz(f, varargin)
%ISLIPSCHITZ Returns logical 1 (true) if a function is Lipschitz at a point
%or logical 0 (false) if it is not.
% 
%   Tests for Lipschitz continuity using the following steps:
%       1. Check for continuous differentiability by checking for
%       discontinuities in the derivative of f in the range [x1, x2]. 
%       
%       2. Check for 
%   
%   If ISLIPSCHITZ is called to evaluate Lipscitz continuity at a point, we
%   check if the function is continually differentiable at a point. If it
%   is, the function is locally Lipschitz continuous.
%   
%   tf = ISLIPSCHITZ(f) tests for Lipschitz continuity on the interval
%   (-Inf Inf). The function uses symvar to determine the variable.
%   
%   tf = ISLIPSCHITZ(f, var) tests for Lipschitz continuity on the interval
%   (-Inf Inf) with respect to the variable 'var'.
% 
%   tf = ISLIPSCHITZ(f, var, pt) tests for Lipschitz continuity at a point
%   'pt' respect to the variable 'var'.
%   
%   tf = ISLIPSCHITZ(f, var, x1, x2) tests for Lipschitz continuity on an
%   interval [x1, x2].

p = inputParser;
verifyNum = @(N) isnumeric(N);
verifySym = @(S) validateattributes(S, {'sym'}, {'nonempty'});
addRequired(p, 'f', verifySym);
addOptional(p, 'var', [], verifySym);
addOptional(p, 'x1', -Inf, verifyNum);
addOptional(p, 'x2', Inf, verifyNum);

parse(p, f, varargin{:});

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

% Test for continuous differentiability.
if ~x1default && x2default
    try
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

g = abs(df);

% Test for Lipschitz conditions.
if ~tf
    % Try to find functional inverse if one exists.
    try
        ginv = finverse(g, V);
        if ~isempty(ginv)
            llim = limit(ginv, V, x1, 'right');
            rlim = limit(ginv, V, x2, 'left');
            tf = isequal(llim, Inf);
        end
    catch ME
        if strcmp(ME.identifier, 'something')
            % do something
        else
        end
    end
end
    
if ~tf
    try
        minbnd = x1;
        maxbnd = x2;
        if isinf(minbnd)
            minbnd = -double(realmax('single'));
        end
        if isinf(maxbnd)
            maxbnd = double(realmax('single'));
        end
%         arg = feval(symengine, 'coerce', [{V > 0}, minfun], 'DOM_LIST')
%         r = feval(symengine, 'linopt::maximize', 0 < V, minfun)
%         options = optimset('PlotFcns',@optimplotfval);
%         options = optimset('FunValCheck', 'on');
        minfun = symfun(-g, V);
        [x, fval] = fminbnd(minfun, minbnd, maxbnd);
        
%         if isnan(fval) && isequal([x1 x2], [-Inf Inf])
%             maxbnd = double(realmax('single'));
% %             maxbnd = double(realmax);
%             [x, fval] = fminbnd(minfun, -maxbnd, maxbnd);
%         end
        
        tf = ~isnan(fval);
    catch ME
        if strcmp(ME.identifier, 'MATLAB:fminbnd:checkfun:NaNFval')
            warning('Could not determine supremum of function.');
            tf = false;
        elseif strcmp(ME.identifier, 'symbolic:specfunc:ExpectingArithmeticalExpression')
            warning('fminbnd failed to find a minimum.');
            tf = false;
        else
            rethrow(ME)
        end
    end
    
    if ~tf
        
    end
%     [~, D] = numden(f);
%     dg = length(coeffs(D, V, 'All'));
%     sols = solve(D, V, 'MaxDegree', dg, 'Real', true);

%     tf = ~any(sols == rg);
end

end

