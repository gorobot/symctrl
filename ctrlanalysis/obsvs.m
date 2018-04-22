function Ob = obsvs(A, C)
%OBSVS Symbolic observability matrix
% 
%   Ob = OBSVS(A, C) returns the observability matrix 
%       Ob = [C; C*A; C*A^2; ...]

p = inputParser;
addRequired(p, 'A', ...
    @(arg) validateattributes(arg, {'sym', 'numeric'}, ...
                                   {'square', 'nonempty'}));
addRequired(p, 'C', ...
    @(arg) validateattributes(arg, {'sym', 'numeric'}, ...
                                   {'nonempty', 'ncols', size(A, 2)}));
parse(p, A, C);

nx = size(A, 1);
[cr, ~] = size(C);

Ob = sym('Ob', [cr*nx nx]);

Ob(1:cr, :) = C;

for k = 2:nx
    prev = cr*(k - 2)+1:cr*(k - 1);
    next = cr*(k - 1)+1:cr*k;
    
    Ob(next,:) = Ob(prev,:)*A;
end

end
