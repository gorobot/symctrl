function varargout = findstates(expr, varargin)
%FINDSTATES Makes a logical guess as to which variables are the state
%variables, input variables, and output variables given an expression.
% 
%   X = FINDSTATES(expr, 'States')
%   U = FINDSTATES(expr, 'Inputs')
%   Y = FINDSTATES(expr, 'Outputs')
%   [X, U, Y] = FINDSTATES(expr, 'All')
%   
%   A 'logical' guess is made with the following assumptions: 
%   
%   1. State variables are symbolic functions in MATLAB. If a variable is
%   defined as 'x(t)', for example, it is a candidate state variable. If a
%   variable is just defined as 'x', it is a symbolic variable and is not a
%   state variable.
%   2. If variables are labeled using standard variable names, then they
%   are the likely candidates for state variables, i.e. 'q', 'x', or 'y' is
%   a state variable and 'u' is an input. We choose one of the state
%   variables as the output if no other output is specified.
%   2. Output variables are also state variables. 
%   3. If a variable has the highest number of derivatives or integrals, it
%   is likely a state variable. The output of every integrator in a block
%   diagram is likely a state variable. Hence, every variable with a
%   derivative below the highest derivative is likley a state variable. 

p = inputParser;
validateExpr = @(expr) validateattributes(expr, {'cell', 'symfun'}, {'nonempty'});
addRequired(p, 'expr', validateExpr);

addParameter(p, 'States', true);
addParameter(p, 'Inputs', false);
addParameter(p, 'Outputs', false);
addParameter(p, 'All', false);

addParameter(p, 'SISO', false);
addParameter(p, 'MIMO', false);

parse(p, expr, varargin{:});

flAll = p.Results.All;

if ~flAll
    flStates = p.Results.States;
    flInputs = p.Results.Inputs;
    flOutputs = p.Results.Outputs;
end

% Convert the expression from a cell array to a symbolic array.
if isa(expr, 'cell')
    expr = cell2sym(expr);
end

syms t

S = getSymbolicFunctions(expr);
D = getSymbolicDerivatives(expr);

% Variables with derivatives.
Dch = cell2sym(children(D))
Swd = S(has(S, Dch(Dch ~= t)));

% Get the variables that have no derivatives. These are likely the input
% variables. We take the difference between the variables with derivatives
% and all variables.
U = setdiff(S, Swd);

% If there are no variables without derivatives, meaning the input
% variables also have a derivative, we need to figure out which variables
% have the lowest order.
if isempty(U)
    ord = ones(size(Swd));

    % Get the order of each derivative.
    for k = 1:numel(D)
        ch = children(D(k));
        idx = ismember(Swd, ch(1));

        cd = length(ch) - 1;
        if cd > ord(idx)
            ord(idx) = cd;
        end
    end
end

% If all variables have derivatives, we choose the variables with the
% highest derivatives as the state variables.
% [~, minidx] = min(ord);
% U = Swd(

disp('done');

end

