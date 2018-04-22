function tf = islinear(f, x)
%ISLINEAR Checks for linearity of a function f(x) wrt x.
%   
%   tf = ISLINEAR(f, x)
%   checks for linearity of a function using additivity and homogeneity.

p = inputParser;
validateFunction = @(F) validateattributes(F, {'sym', 'symfun'}, {'nonempty'});
validateVariables = @(V) validateattributes(V, {'sym'}, {'nonempty'});
addRequired(p, 'f', validateFunction);
addRequired(p, 'x', validateVariables);
parse(p, f, x);

na = cell(size(x));
na(:) = {'A'};
ta = sym(genvarname(na, who));

nb = cell(size(x));
nb(:) = {'B'};
tb = sym(genvarname(nb, who));

nx = cell(size(x));
nx(:) = {'SUBX'};
tx = sym(genvarname(nx, who));

% Disable warnings.
orig_state = warning('off','all');

% Additivity
tf = all(isAlways(subs(f, x, ta) + subs(f, x, tb) == subs(f, x, ta + tb)));

% Homogeneity
if tf
    a = sym('a');
    tf = all(isAlways(subs(f, x, a*tx) == a*subs(f, x, tx)));
end

% try
%     % Additivity
% %     A_ = sym2cell(ta);
% %     B_ = sym2cell(tb);
% %     C_ = sym2cell(ta + tb);
% %     tf = isAlways(Ffun(A_{:}) + Ffun(B_{:}) == Ffun(C_{:}));
%     tf = isAlways(Ffun(a) + Ffun(b) == Ffun(a + b));
%     % Homogeneity
%     if tf
% %         syms C
% %         D_ = sym2cell(C.*ta);
% %         tf = isAlways(Ffun(D_{:}) == C.*Ffun(A_{:}));
%         tf = isAlways(Ffun(a*b) == a*Ffun(b));
%     end
% catch ME
%     warning(orig_state);
%     if strcmp(ME.identifier, 'something')
%         % do something
%     else
%         rethrow(ME);
%     end
% end

% Restore warnings.
warning(orig_state);

end

