function P = care(sys, Q, R)
%CARE Solve the continuous algebraic Riccati equation.
%   Detailed explanation goes here

% p = inputParser;
[A, B, C, ~] = getabcd(sys);
% validateMatrix = @(M) isequal(M, M.') && isequal(size(A), size(M));
% addRequired(p, 'sys');
% addRequired(p, 'Q', validateMatrix);
% addRequired(p, 'R', validateMatrix);
% parse(p, sys, Q, R);

Q = sym(Q);
R = sym(R);
M = C;

H = [A, -B*inv(R)*B.'; -M.'*Q*M, -A.'];
% J = [zeros(2) eye(2); -eye(2) zeros(2)];
[U, ~] = qr(H, 'real');
U = mat2cell(U, size(A), size(A));
P = -U{2, 1}*inv(U{1, 1});

% [U, S] = schurs(H);
% 
% U = mat2cell(U, size(A), size(A));
% S = mat2cell(S, size(A), size(A));
% 
% P = U{2, 1}*inv(U{1, 1});

% [V, D] = eig(H);
% D = reshape(diag(D), 1, []);
% rV = V(:, ~all(isAlways(real(D) < 0) == 0, 1));
% XY = mat2cell(rV, [length(A), length(A)]);
% 
% P = real(XY{2}/XY{1});

end

