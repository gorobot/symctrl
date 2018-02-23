function sv = subs(sv, old, new)
%SUBS Replace a symbolic variable in state space.
%   Detailed explanation goes here

p = inputParser;
validateSys = @(sv) isa(sv, 'symsv');
addRequired(p, 'sv', validateSys);
addRequired(p, 'old');
addRequired(p, 'new');

parse(p, sv, old, new);

sv = p.Results.sv;
old = p.Results.old;
new = p.Results.new;

% Throw an error if the variables passed are state variables. 
if nnz(ismember(symvar([sv.x, sv.u, lhs(sv.Dx), lhs(sv.y)]), old)) >= 1
    error('Cannot replace state variables using SUBS. Use LINEARIZE instead.');
end

sv.x = lhs(sv.x) == subs(rhs(sv.x), old, new);
sv.Dx = lhs(sv.Dx) == subs(rhs(sv.Dx), old, new);
sv.u = lhs(sv.u) == subs(rhs(sv.u), old, new);
sv.y = lhs(sv.y) == subs(rhs(sv.y), old, new);

end
