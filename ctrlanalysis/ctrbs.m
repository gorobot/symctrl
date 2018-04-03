function Co = ctrbs(A, B)
%CTRBS Symbolic controllability matrix
% 
%   Co = CTRBS(A, B) returns the controllability matrix 
%       Co = [B, A*B, A^2*B, ...]

p = inputParser;
validateStateMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, {'square', 'nonempty'});
validateInputMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, ...
                          {'nonempty', 'nrows', size(A, 1)});
addRequired(p, 'A', validateStateMatrix);
addRequired(p, 'B', validateInputMatrix);
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

