function eqx = eqpt(sv)
%EQPT Finds the trivial equilibrium point for f(t, x, u) = 0.
% 
%   eqx = EQPT(sv)
% 
%   Finds the trivial equilibrium point given f(t, x, u) = 0.
p = inputParser;

validateSys = @(sv) isa(sv, 'symsv');
addRequired(p, 'sv', validateSys);

parse(p, sv);

fn = subs(sv.f) == 0;

a = assumptions;

assume(lhs(sv.u) == 0);

try
    sol = cell2sym(struct2cell(solve(fn, lhs(sv.x))));
catch ME
    % Attempt to catch certain errors.
    rethrow(ME);
end

% If no solution is found, return an empty set of equations and display a
% warning.
if ~isempty(sol)
    eqx = lhs(sv.x) == sol;
    eqx = simplify(eqx);
    for k = 1:length(eqx)
        eqx(k) = isolate(eqx(k), lhs(sv.x(k)));
    end
else
    warning('Unable to find a trivial equilibrium point for f(t, x, u) = 0.');
    eqx = sol;
end

assume(sv.u, 'clear');
assume(a);

eqx = sym2cell(eqx);

end

