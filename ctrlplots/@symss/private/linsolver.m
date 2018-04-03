function y = linsolver(sys, u, varargin)
%LINSOLVER Internal linear function solver. 
%   Detailed explanation goes here

p = inputParser;
validateInput = @(U) ...
    validateattributes(U, {'sym', 'numeric', 'function_handle'}, ...
                          {'nonempty'});
validateTspan = @(tspan) ...
    validateattributes(tspan, {'numeric', 'increasing'}, {'row'});
addRequired(p, 'sys');
addOptional(p, 'u', sym.empty, validateInput);
addOptional(p, 'tspan', [0 5], validateTspan);
addOptional(p, 'x0', []);
parse(p, sys, u, varargin{:});

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
    y = subs(iL, sys.states, x0);
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

