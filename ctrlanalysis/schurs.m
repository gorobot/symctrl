function [U, T] = schurs(A, varargin)
%SCHURS Symbolic Schur decomposition.
% 
%   This function returns the Schur decomposition of a matrix by computing
%   the eigenvectors of a matrix and performing a QR decomposition.

p = inputParser;
validateMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, {'nonempty'});
addRequired(p, 'H', validateMatrix);
parse(p, A, varargin{:});

if ~isa(A, 'sym')
    A = sym(A);
end

% HB = feval(symengine, 'linalg::hessenberg', H);

[V, D, P] = eig(A);

% Form an eigenbasis when the matrix has non-linearly independent
% eigenvectors.
if ~isequal(size(V), size(A))
    V = orth([V, eye(size(A))], 'real');
%     Vf = sym(zeros(size(A)));
%     for k = 1:size(V, 2)
%         L = any(D == D(P(k), P(k)), 1);
%         Vf(:, L) = repmat(V(:, k), 1, nnz(L));
%     end
%     V = Vf;
end

[~, idx] = sort(diag(D));
V = V(:, idx);

[U, ~] = qr(V, 'real');

T = U.'*A*U;

end

