function varargout = lsim(sys, varargin)
%LSIM Compute the linear response of a system to arbitrary inputs.
%
%   y = LSIM(sys, u, t, x0) computes the linear response of a system to an
%   arbitrary input, where u is a symbolic s-domain input signal, t is a time
%   span and x0 is the initial conditions.

p = inputParser;

% Validate sim inputs.
validatesimargs(p, sys, varargin{:});

u = p.Results.u;
tspan = p.Results.tspan;
x0 = p.Results.x0;

if ~iscell(x0)
    x0 = {x0};
end

y = cell(size(x0));

for k = 1:numel(x0)
    ic = reshape(x0{k}, [], 1);
    ys = linsolver(sys, u, tspan, ic);
    y{k} = ys;
end

if nargout ~= 0
    varargout{1} = y;
else
    for k = 1:numel(y)
        out = y{k};
        [m, n] = size(out);
        for p = 1:numel(out)
            ax = subplot(n, m, p);
            ax.NextPlot = 'add';

            h = fplot(out(p));
            h.XRange = tspan;
            h.XRangeMode = 'auto';

            [input, output] = ind2sub([m, n], p);
            title(['Output [', num2str(output), ', ', num2str(input), ']']);
        end
    end
end

end
