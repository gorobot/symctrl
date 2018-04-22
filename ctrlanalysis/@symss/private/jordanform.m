function sys = jordanform(sys)
%JORDANFORM Jordan canonical form.
%
%   T = JORDANFORM(sys) converts a state space model to Jordan
%   canonical form.

% Get the matrix of eigenvectors.
[A, B, C, D] = sys.getabcd();
[V, ~] = eig(A);

% Compute the similarity transformations using V.
A = V\A*V;
B = V\B;
C = C*V;

sys.f = A*sys.states + B*sys.inputs;
sys.g = C*sys.states + D*sys.inputs;

end
