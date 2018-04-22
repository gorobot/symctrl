function tf = isschur(A)
%ISSCHUR Returns logical 1 (true) if the matrix or transfer function is
%Schur, or logical 0 (false) if it is not.
%   
%   tf = ISSCHUR(A) tests for Schur conditions on a symbolic matrix.

p = inputParser;
validateMatrix = @(M) validateattributes(M, {'sym', 'numeric'}, {'square'});
addRequired(p, 'A', validateMatrix);
parse(p, A);

rL = real(eig(A));

if isa(A, 'sym')
    tf = ~any(isAlways(rL >= 1));
else
    tf = ~any(rL >= 1);
end

end

