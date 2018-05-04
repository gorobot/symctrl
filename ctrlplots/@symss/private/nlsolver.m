function [t, y] = nlsolver(sys, u, tspan, x0, varargin)
%NLSOLVER Internal nonlinear function solver.
%   Detailed explanation goes here

p = inputParser;
p.StructExpand = false;
addRequired(p, 'sys');
addRequired(p, 'u');
addRequired(p, 'tspan');
addRequired(p, 'x0');
addOptional(p, 'options', struct([]));
addParameter(p, 'Solver', @ode45);
parse(p, sys, u, tspan, x0, varargin{:});

T = sym('t');

[tx, tu, tf] = subvars(sys);

% Substitute variables into the input.
u = subs(u, sys.states, tx);
u = reshape(u, [], 1);

% Substitute the input into the state equations.
tf = subs(tf, tu, u);

% Create a Matlab function.
Ffun = symfun(formula(tf), [T; tx]);
odefun = matlabFunction(Ffun, 'vars', {T, tx});

x0 = reshape(x0, [], 1);

solver = p.Results.Solver;

% Solve the function.
options = odeset(p.Results.options);
[t, y] = feval(solver, odefun, tspan, x0, options);

end
