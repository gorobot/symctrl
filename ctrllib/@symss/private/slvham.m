function P = slvham(H)
%SLVHAM Solves the ARE using the Hamiltonian method.
% 
%   Methodology:
%   The Hamiltonian is used in order to solve the algebraic Riccati
%   equation. If the Hamiltonian has linearly independent eigenvectors, no
%   zero eigenvalues, and no repeated eigenvalues, we can use the Schur
%   decomposition to compute the matrix P.
% 
%   We sort the eigenvalues so that the eigenvectors corresponding to
%   stable eigenvectors appear in U_11 and U_21 and compute U_21*U_11^-1.
%   
%   In the case of a defective matrix, the inverse may not produce the
%   actual inverse of the matrix. In these cases, the Moore-Penrose
%   pseudoinverse is used. See PINV for more information.

%   References:
%   Arnold, William F., and Alan J. Laub. "Generalized eigenproblem 
%   algorithms and software for algebraic Riccati equations." Proceedings 
%   of the IEEE 72.12 (1984): 1746-1754.
% 
%   Laub, Alan. "A Schur method for solving algebraic Riccati equations." 
%   IEEE Transactions on automatic control 24.6 (1979): 913-921.
% 
%   https://stanford.edu/class/ee363/lectures/clqr.pdf
%   http://www2.mpi-magdeburg.mpg.de/mpcsc/mitarbeiter/saak/lehre/Matrixgleichungen/pyuantong_09WS.pdf
%   https://www.cs.cornell.edu/~bindel/class/cs6210-f16/lec/2016-11-02.pdf

p = inputParser;
addRequired(p, 'H', @(M) ishamiltonian(M));
parse(p, H);

% Compute the Schur decomposition.
[U, ~] = schurs(H);
U = mat2cell(U, size(H)/2, size(H)/2);

cs = warning('off', 'all');

% Compute the solution to the algebraic Riccati equation.
P = U{2, 1}/U{1, 1};

% Compute the inverse using the Moore-Penrose pseudoinverse if the
% inverse does not exist.
if any(isinf(P))
    P = U{2, 1}*pinv(U{1, 1});
end

warning(cs);

end

