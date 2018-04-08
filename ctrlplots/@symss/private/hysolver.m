function [t, y] = hysolver(sys, u, varargin)
%HYSOLVER Internal hybrid function solver. 
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
u = p.Results.u;
u = subs(u, sys.states, tx);

% Substitute the input into the state equations.
tf = subs(tf, tu, u);

% Get the state equations and conditions.
ch = children(tf);

tspan = p.Results.tspan;

t0 = tspan(1);
tmax = tspan(end);

x0 = reshape(p.Results.x0, [], 1);

solver = p.Results.Solver;

t = double.empty;
y = double.empty;

while t0 < tmax
    x0 = reshape(x0, [], 1);

    % Select a function.
    cond = isAlways(subs(ch(:, 2), tx, x0));
    idx = find(cond, 1);

    % Create a Matlab function.
    Ffun = symfun(ch(idx, 1), [T; tx]);
    odefun = matlabFunction(Ffun, 'Vars', {T, tx});
    
    % Handle discontinuous jumps. If the function evaluated at the next
    % time step would violate the current conditions, set the new
    % conditions to the evaluated ones and continue.
    xt = round(x0, 6) + odefun(0, x0)*eps('double');
    if ~isAlways(subs(ch(idx, 2), tx, xt))
        xe = odefun(0, x0);
        t(end + 1, :) = t(end) + eps('double');
        y(end + 1, :) = (xe).';
            
        x0 = xe;
        continue;
    end

    % Set event function.
    options = odeset('Events', @odeEvent);

    % Solve the function.
    [tt, yy, t0, x0, ~] = feval(solver, odefun, [t0 tmax], x0, options);
    
    t = [t; tt];
    y = [y; yy];
end

    % Event function. This function detects when the current value of the
    % simulation violates the conditions for being in the current state and
    % ends the ODE solver.
    function [value, isterminal, direction] = odeEvent(t, x)
        if isAlways(subs(ch(idx, 2), tx, x))
            value = 1;
        else
            value = 0;
        end
        isterminal = 1;
        direction = 0;
    end
end

