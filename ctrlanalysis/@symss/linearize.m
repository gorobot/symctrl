function sys = linearize(sys, varargin)
%LINEARIZE Linearize a system around an equilibrium point.
%
%   T = LINEARIZE(sys) linearizes a system around an equilibrium point. If
%   no point is specified, the system is linearized around f(x) = 0.
%
%   T = LINEARIZE(sys, eq) linearizes a system around the equilibrium point
%   defined by eq. For instance, T = LINEARIZE(sys, [x1(0), x2(0)]).

p = inputParser;
sz = size([sys.states; sys.inputs]);
addRequired(p, 'sys');
addOptional(p, 'eq', zeros(sz), ...
    @(arg) validateattributes(arg, {'sym', 'numeric', 'cell'}, ...
                                   {'size', sz}));
parse(p, sys, varargin{:});

eq = p.Results.eq;
if iscell(eq)
    eq = cell2sym(eq);
end

[A, B, C, D] = sys.getabcd();
M = cellfun(@(X) {subs(X, [sys.states; sys.inputs], eq)}, {A, B, C, D});

sys.f = M{1}*sys.states;
sys.g = M{3}*sys.states;

if ~isempty(B)
     sys.f = sys.f + M{2}*sys.inputs;
     sys.g = sys.g + M{4}*sys.inputs;
end

end
