function y = linsolver(sys, u, tspan, x0, varargin)
%LINSOLVER Internal linear function solver.
%   Detailed explanation goes here

p = inputParser;
addRequired(p, 'sys');
addRequired(p, 'u');
addRequired(p, 'tspan');
addRequired(p, 'x0');
parse(p, sys, u, tspan, x0, varargin{:});

u = p.Results.u;

x0 = reshape(p.Results.x0, [], 1);

syms s t

% Get the zero input response and the zero state response.
if isa(u, 'sym')
    Yi = zir(sys, x0);
    Ys = zsr(sys, u);

    if ~isempty(Ys)
        Y = Yi + Ys;
    else
        Y = Yi;
    end

    iL = ilaplace(Y, s, t);
    y = iL;
else
    yi = tzir(sys, x0);
    ys = tzsr(sys, u);

    if ~isempty(ys)
        y = yi + ys;
    else
        y = yi;
    end
end

end
