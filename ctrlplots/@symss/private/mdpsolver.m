function [t, y] = mdpsolver(sys, m, tspan, x0, varargin)
%MDPSOLVER Internal policy input solver.

p = inputParser;
p.StructExpand = false;
addRequired(p, 'sys');
addRequired(p, 'm');
addRequired(p, 'tspan');
addRequired(p, 'x0');
addOptional(p, 'options', struct([]));
addParameter(p, 'Solver', @ode45);
addParameter(p, 'MdpOptions', struct([]));
parse(p, sys, m, tspan, x0, varargin{:});

T = sym('t');

[tx, tu, tf] = subvars(sys);

% Get MDP options.
mdpopts = p.Results.MdpOptions;

sf = mdpopts.StateFunction;
term = mdpopts.TermEvent;

% Get time span.
tspan = p.Results.tspan;
t0 = tspan(1);
tmax = tspan(end);

Ts = sys.Ts;

Td = mdpopts.Td;

options = p.Results.options;

solver = p.Results.Solver;

t = double.empty;
y = double.empty;

x0 = reshape(p.Results.x0, [], 1);

% Simulate the hybrid system.
while t0 < tmax
    % Set the terminal time for this simulation.
    Tf = t0 + Td;

    % Copy the substituted functions to avoid overwrite.
    funs = tf;

    x0 = reshape(x0, [], 1);

    % Choose an input from the policy.
    x = num2cell(x0);
    x = sf(x{:});
    if isempty(x)
        break;
    end

    uprob = m.policy(x, :);
    r = rand();
    for k = 1:numel(uprob)
        if k == numel(uprob)
            u = m.U{k};
        elseif r < sum(uprob(1:k))
            u = m.U{k};
            break;
        end
    end

    u = reshape(u, [], 1);

    % Substitute the input into the state equations.
    funs = subs(funs, tu, u);

    % Create a Matlab function.
    Ffun = symfun(funs, [T; tx]);
    odefun = matlabFunction(Ffun, 'Vars', {T, tx});

    % Set event function.
    if ~isempty(mdpopts.TermEvent)
        options = odeset(options, 'Events', @odeEvent);
    end

    % Solve the function.
    [tt, yy, te] = feval(solver, odefun, [t0 Tf], x0, options);

    t = [t; tt];
    y = [y; yy];

    % Get the new initial conditions.
    t0 = Tf;
    x0 = yy(end, :);

    % Check for terminating event.
    if ~isempty(mdpopts.TermEvent) && ~isempty(te)
        break;
    end
end

    % Event function. This function detects when the current value of the
    % simulation triggers a terminating event and ends the ODE solver.
    function [value, isterminal, direction] = odeEvent(t, x)
        X = num2cell(x);
        if term(t, X) == 1
            value = 0;
        else
            value = 1;
        end
        isterminal = 1;
        direction = 0;
    end

end
