function [L, a, b] = lagrangian(opt)
%LAGRANGIAN Compute the Lagrangian of an optimization problem.
%   Detailed explanation goes here

eq = ~opt.isinequality(opt.st);

% Get all terms on lhs.
ch = cell2sym({children(opt.st)});
ch = ch(:, 1) - ch(:, 2);

% Separate equality and inequality constraints.
g = ch(~eq);
h = ch(eq);

% Define Lagrangian multipliers.
na = cell(nnz(~eq), 1);
na(:) = {'a'};
a = sym(genvarname(na, [who; {'a'}]));

nb = cell(nnz(eq), 1);
nb(:) = {'b'};
b = sym(genvarname(nb, [who; {'b'}]));

% Form the Lagrangian.
L = [opt.f; g; h].'*[1; a; b];

end

