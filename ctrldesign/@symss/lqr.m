function [K, P, L] = lqr(sys, Q, R)
%LQR Summary of this function goes here
%   Detailed explanation goes here

% p = inputParser;
[A, B, ~, ~] = getabcd(sys);
% validateMatrix = @(M) isequal(M, M.') && isequal(size(A), size(M));
% addRequired(p, 'sys');
% addRequired(p, 'Q', validateMatrix);
% addRequired(p, 'R', validateMatrix);
% parse(p, sys, Q, R);

P = care(sys, Q, R);

K = inv(R)*B.'*P;
L = eig(A - B*K);

end

