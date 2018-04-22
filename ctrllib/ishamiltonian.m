function tf = ishamiltonian(M)
%ISHAMILTONIAN Returns logical 1 (true) if a matrix is Hamiltonian or 
%logical 0 (false) if it is not.
% 
%   For a matrix J = [0 I; -I 0], a matrix M is Hamiltonian if: 
% 
%   J^(-1)M.'J = -M
% 
%   See also issymplectic

sz = size(M)/2;
J = [zeros(sz), eye(sz); -eye(sz), zeros(sz)];

tf = isequal(J\M.'*J, -M);

end

