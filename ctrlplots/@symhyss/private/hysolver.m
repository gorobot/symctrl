function [t, y] = hysolver(sys, u, tspan, x0, varargin)
%HYSOLVER Internal hybrid function solver.

p = inputParser;
addRequired(p, 'sys');
addRequired(p, 'u');
addRequired(p, 'tspan');
addRequired(p, 'x0');
addOptional(p, 'options', struct([]));
addParameter(p, 'Solver', @ode45);
parse(p, sys, u, tspan, x0, varargin{:});

T = sym('t');

% Get the state equations and conditions.
[tx, tu, tf] = subvars(sys);
conds = sys.guard;
edges = sys.edge;

% Substitute variables into the input.
u = p.Results.u;
u = subs(u, sys.states, tx);

% Substitute the input into the state equations.
for k = 1:numel(tf)
    tf{k} = subs(tf{k}, tu, u);
end

conds = subs(conds, [sys.states; sys.inputs], [tx; tu]);
conds = subs(conds, tu, u);

% Get time span.
tspan = p.Results.tspan;
t0 = tspan(1);
tmax = tspan(end);

solver = p.Results.Solver;

t = double.empty;
y = double.empty;

x0 = reshape(p.Results.x0, [], 1);

% Select a starting mode.
icond = isAlways(subs(conds, tx, x0));

% Ignore continuous probability modes. These correspond to the guards along
% the main diagonal.
icond(1:1 + size(icond, 1):end) = 0;
idx = find(icond, 1);

% Find the dynamics that correspond to the mode.
[nmode, ~] = ind2sub(size(icond), idx);

% Simulate the hybrid system.
while t0 < tmax
    x0 = reshape(x0, [], 1);

    if isempty(nmode)
        break;
    else
        mode = nmode;
    end

    % Create a Matlab function.
    Ffun = symfun(tf{mode}, [T; tx]);
    odefun = matlabFunction(Ffun, 'Vars', {T, tx});

    % Handle discontinuous jumps. If the mode is discontinuous, meaning
    % there is a 0 probability of staying within the current mode, evaluate
    % the current conditions and continue.
    if conds(mode, mode) == sym(0)
        xn = odefun(0, x0);
        t(end + 1, :) = t(end) + eps('double');
        y(end + 1, :) = xn.';
        x0 = xn;

        guard = isAlways(subs(conds(mode, :), tx, xn));
        % Find next mode.
        nmode = find(~guard & edges(mode, :), 1);
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
    function [value, isterminal, direction] = odeEvent(~, x)
        guard = isAlways(subs(conds(mode, :), tx, x));
        if any(~guard) || conds(mode, mode) == sym(0)
            % Find next mode.
            nmode = find(~guard & edges(mode, :), 1);
            value = 0;
        else
            value = 1;
        end
        isterminal = 1;
        direction = 0;
    end
end
