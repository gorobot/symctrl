function T = jordanform(sys)
%JORDANFORM Jordan canonical form.
%   
%   T = JORDANFORM(sys) converts a state space model to Jordan 
%   canonical form.

% Get the matrix of eigenvectors.
[A, B, C, D] = getabcd(sys);
[V, ~] = eig(A);

% Compute the similarity transformations using V.
A = V\A*V;
B = V\B;
C = C*V;

T = sys;
T.f = A*T.states + B*T.inputs;
T.g = C*T.states + D*T.inputs;
        
end

