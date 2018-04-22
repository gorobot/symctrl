function Co = ctrbs(A, B)
%CTRBS Symbolic controllability matrix
% 
%   Co = CTRBS(A, B) returns the controllability matrix 
%       Co = [B, A*B, A^2*B, ...]

p = inputParser;
addRequired(p, 'A', ...
    @(arg) validateattributes(arg, {'sym', 'numeric'}, ...
                                   {'square', 'nonempty'}));
addRequired(p, 'B', ...
    @(arg) validateattributes(arg, {'sym', 'numeric'}, ...
                                   {'nonempty', 'nrows', size(A, 1)}));
parse(p, A, B);

nx = size(A, 1);
[~, bc] = size(B);

Co = sym('Co', [nx bc*nx]);

Co(:, 1:bc) = B;

for k = 2:nx
    prev = bc*(k - 2)+1:bc*(k - 1);
    next = bc*(k - 1)+1:bc*k;
    
    Co(:,next) = A*Co(:,prev);
end

end

