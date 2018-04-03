function [Ue, Se] = ordschurs(U, S)
%ORDSCHURS Reorder eigenvalues of symbolic Schur decomposition.

A = U*S*U.';
L = diag(S);
[~, idx] = sort(real(L));
Ue = U(:, idx);

Se = Ue.'*A*Ue;

end

