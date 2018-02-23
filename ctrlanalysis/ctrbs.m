function Co = ctrbs(A, B)
%CTRBS Symbolic controllability matrix
% 
%   Co = CTRBS(SYS) returns the controllability matrix [B, A*B, A^2*B, ...]
p = inputParser;

validateA = @(A) validateattributes(A, {'sym'}, {'square', 'nonempty'});
validateB = @(B) validateattributes(B, {'sym'}, {'nonempty'});
addRequired(p, 'A', validateA);
addRequired(p, 'B', validateB);

parse(p, A, B);

A = p.Results.A;
B = p.Results.B;

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

