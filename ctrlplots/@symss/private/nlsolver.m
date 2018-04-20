function [t, y] = nlsolver(sys, u, varargin)
%NLSOLVER Internal nonlinear function solver.
%   Detailed explanation goes here

p = inputParser;
validateInput = @(U) ...
    validateattributes(U, {'sym', 'numeric', 'function_handle'}, ...
                          {'nonempty'});
validateTspan = @(tspan) ...
    validateattributes(tspan, {'numeric', 'increasing'}, {'row'});
validateSolver = @(solver) ...
    validateattributes(solver, {'function_handle'}, {'nonempty'});
addRequired(p, 'sys');
addOptional(p, 'u', sym.empty, validateInput);
addOptional(p, 'tspan', [0 5], validateTspan);
addOptional(p, 'x0', []);
addParameter(p, 'Solver', @ode45, validateSolver);
parse(p, sys, u, varargin{:});

T = sym('t');

[tx, tu, tf, ~] = varsub(sys);

% Substitute variables into the input.
u = subs(u, sys.states, tx);
u = reshape(u, [], 1);

% Substitute the input into the state equations.
tf = subs(tf, tu, u);

% Create a Matlab function.
Ffun = symfun(formula(tf), [T; tx]);
odefun = matlabFunction(Ffun, 'vars', {T, tx});

tspan = p.Results.tspan;
x0 = reshape(p.Results.x0, [], 1);

solver = p.Results.Solver;

% Solve the function.
[t, y] = feval(solver, odefun, tspan, x0);

end

