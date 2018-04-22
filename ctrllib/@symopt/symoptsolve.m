function S = symoptsolve(opt, algorithm, varargin)
%SYMOPTSOLVE Symbolic optimization solver.
%   
%   S = SYMOPTSOLVE(opt, 'sgd', ...)
% 
%   Available solvers:
%       gd - gradient descent
%       newton - newton's method
%       sgd - stochastic gradient descent

% 144 equivalent
% 498
% 535
% 575
p = inputParser;
addRequired(p, 'opt');
addRequired(p, 'algorithm');
parse(p, opt, algorithm);

algorithm = p.Results.algorithm;

switch algorithm
    case 'newton'
        solver = @solvenewton;
    case 'gd'
        solver = @solvegd;
    case 'sgd'
        solver = @solvesgd;
end

S = solver(opt, varargin{:});

end

