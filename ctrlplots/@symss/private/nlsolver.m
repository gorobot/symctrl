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
addParameter(p, 'solver', @ode45, validateSolver);
parse(p, sys, u, varargin{:});

t = sym('t');

nx = cell(size(sys.states));
nx(:) = {'SUBX'};
tx = sym(genvarname(nx, who));
% 
% nu = cell(size(sys.inputs));
% nu(:) = {'SUBX'};
% tu = sym(genvarname(nu, who));
% 
tf = subs(sys.f, sys.states, tx);
% [tx, tu, tf, ~] = varsub(sys);
% tv = [tx; tu];

Ffun = symfun(formula(tf), [t; tx]);
odefun = matlabFunction(Ffun, 'vars', {t, tx});

tspan = p.Results.tspan;
x0 = reshape(p.Results.x0, [], 1);

solver = p.Results.solver;

[t, y] = feval(solver, odefun, tspan, x0);

% y = conv(y, u, 'valid');

end

