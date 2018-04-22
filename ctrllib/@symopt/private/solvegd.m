function S = solvegd(opt, x0, varargin)
%SOLVEGD Solve using gradient descent algorithm.

% References:
% Boyd, Stephen, and Lieven Vandenberghe. Convex optimization. Cambridge
% university press, 2004.

p = inputParser;
addRequired(p, 'opt');
addRequired(p, 'x0');
addOptional(p, 'e', 1E-6);
addParameter(p, 'lsparams', [0.4, 0.8]);
parse(p, opt, x0, varargin{:});

x = x0;
if ~isequal(size(reshape(x, 1, [])), size(opt.vars))
    error('Insufficient initial conditions.');
end

x = reshape(x, [], 1);

e = p.Results.e;
lsparams = p.Results.lsparams;

a = lsparams(1);
b = lsparams(2);
validateattributes(a, {'numeric'}, {'positive', '<', 0.5});
validateattributes(b, {'numeric'}, {'positive', '<', 1});

Ffun = symfun(opt.f, opt.vars);
gf = gradient(Ffun);

while true
    % Compute the gradient.
    x = num2cell(x);
    dx = gf(x{:});
    if norm(dx) < e
        break;
    end
    
    % Find step size. Backtracing line search.
    t = 1;
    while true
        fd = num2cell(x - dx*t);
        % while f(x + dx*t) > f(x) + a*t*dx.'*dx
        if Ffun(fd{:}) < Ffun(x{:}) - (dx.')*dx*a*t
            break;
        end
        t = b*t;
    end
    
    % Update. x = x+ dx*t
    x = x - dx*t;
end

% Store result.
S = struct;
nv = arrayfun(@(x) {char(x)}, opt.vars);
for k = 1:numel(nv)
    S.(nv{k}) = x{k};
end

end

