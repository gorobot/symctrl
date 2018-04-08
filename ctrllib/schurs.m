function [U, T] = schurs(A, varargin)
%SCHURS Symbolic Schur decomposition.
% 
%   This function returns the Schur decomposition of a matrix by computing
%   the generalized eigenvectors of a matrix and performing a QR
%   decomposition.

p = inputParser;
validateMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, {'nonempty'});
addRequired(p, 'A', validateMatrix);
parse(p, A, varargin{:});

if ~isa(A, 'sym')
    A = sym(A);
end

[V, D] = eig(A);

% Find generalized eigenvectors when the matrix is defective, i.e. has
% non-linearly independent eigenvectors. The Matlab command JORDAN returns
% the generalized eigenvectors of a matrix.
if ~isequal(size(V), size(A))
    [V, J] = jordan(A);
    D = diag(J);
end

[~, idx] = sort(real(diag(D)));
V = V(:, idx);

[U, ~] = qr(V, 0, 'real');

T = U.'*A*U;

end

