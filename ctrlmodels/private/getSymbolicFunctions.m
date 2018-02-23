function S = getSymbolicFunctions(expr)
%GETSYMBOLICFUNCTIONS Gets the symbolic functions from an expression.
%
%   Currently, there is no good way to detect symbolic functions in MATLAB.
%   There is a function for detecting symbolic variables, but it ignores
%   symbolic functions such as 'x(t)', returning only 't'. This helper
%   function is a workaround for finding symbolic functions from the base
%   workspace which also appear in the expression passed to this function.
% 
%   It works in the same way a call to 'syms' with an output argument
%   works, by getting the symbolic functions in the current scope. Instead,
%   we get the symbolic functions in the base scope and compare with the
%   terms of the expression passed to the function.

% Get all symfuns defined in the base workspace. We then iteratively step
% through each child in the expression passed to this function and
% determine if they are the same as the symfuns.
P = evalin('base', 'whos');
classNames = {P.class};
baseFuns = {P(strcmp('symfun', classNames)).name};

baseFuns = str2sym(strcat(baseFuns, '(t)'));

if isempty(baseFuns)
    warning('No symbolic functions found in workspace.');
    return
end

% Get the symbolic variables defined in this function. We can use these to
% filter out our search results in the loop.
syms t
vars = symvar(expr);

idx = zeros(size(baseFuns));

% Starting condition.
ch = expr;

% We define a safety catch for exiting the loop if it goes too long.
safety = 0;

% While there are still terms in the children array which are not part of
% the vars obtained above, meaning there are still unknown terms in the
% children, continue.
while nnz(has(ch, vars)) ~= 0
    % Get the children of the expression and convert them into a symbolic
    % array.
    ch = children(ch);
    ch = cell2sym(ch);
    
    % Remove the elements which are just symbolic variables.
    ch = setdiff(ch, vars);
    
    for k = 1:numel(ch)
        idx = idx | has(baseFuns, ch(k));
    end
    
    % We include as a hard limit a 10-level deep iteration on the while
    % loop. The loop could end before this, but we don't want the loop to
    % continue to infinity.
    safety = safety + 1;
    if safety == 10
        break
    end
end

S = baseFuns(idx);

end

