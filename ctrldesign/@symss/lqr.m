function [K, P, L] = lqr(sys, Q, R)
%LQR Summary of this function goes here
%   Detailed explanation goes here

% Resources:
% http://www.joinville.udesc.br/portal/professores/marianasantos/materiais/lqrnotes_Regra_de_Bryson.pdf

% p = inputParser;
[A, B, ~, ~] = getabcd(sys);
% validateMatrix = @(M) isequal(M, M.') && isequal(size(A), size(M));
% addRequired(p, 'sys');
% addRequired(p, 'Q', validateMatrix);
% addRequired(p, 'R', validateMatrix);
% parse(p, sys, Q, R);

[P, K] = care(sys, Q, R);

L = eig(A - B*K);

end

