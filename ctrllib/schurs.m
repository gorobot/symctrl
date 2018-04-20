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
addParameter(p, 'GramSchmidt', false);
parse(p, A, varargin{:});

if ~isa(A, 'sym')
    A = sym(A);
end

[V, ~] = eig(A);

% Find generalized eigenvectors when the matrix is defective, i.e. has
% non-linearly independent eigenvectors. The Matlab command JORDAN returns
% the generalized eigenvectors of a matrix.
if ~isequal(size(V), size(A))
    [V, ~] = jordan(A);
end

if p.Results.GramSchmidt
    % Gram-Schmidt.
    n = size(V, 2);

    U = zeros(size(V), 'like', V);

    U(:, 1) = V(:, 1)/norm(V(:, 1));
    for k = 2:n
        U(:, k) = V(:, k);
        for r = 1:k - 1
            U(:, k) = U(:, k) - (U(:, k)'*U(:, r))/(U(:, r)'*U(:, r))*U(:, r);
        end

        U(:, k) = U(:, k)/norm(U(:, k));
    end
else
    % QR
    [U, ~] = qr(V, 0, 'real');
end

T = U.'*A*U;

end

