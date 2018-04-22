function tf = issymplectic(M)
%ISSYMPLECTIC Returns logical 1 (true) if a matrix is symplectic or 
%logical 0 (false) if it is not.
% 
%   For a matrix J = [0 I; -I 0], a matrix M is symplectic if: 
% 
%   J^(-1)M.'J = M^(-1)
% 
%   See also ishamiltonian

sz = size(M)/2;
J = [zeros(sz), eye(sz); -eye(sz), zeros(sz)];

tf = isequal(J\(M.')*J, inv(M));

end

