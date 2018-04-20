function [Ue, Se] = ordschurs(U, S, varargin)
%ORDSCHURS Reorder eigenvalues of symbolic Schur decomposition.

p = inputParser;
validateKeyword = @(K) ismember(K, {'lhp', 'rhp', 'udi', 'udo'});
addRequired(p, 'U');
addRequired(p, 'S');
addOptional(p, 'keyword', 'lhp', validateKeyword);
parse(p, U, S, varargin{:});

% Compute the original A matrix. A = USU.'
A = U*S*U.';

% Reorder the eigenvalues fom the diagonal.
L = diag(S).';

key = p.Results.keyword;

switch key
    case 'lhp'
        idx = isAlways(real(L) < 0);
    case 'rhp'
        idx = isAlways(real(L) >= 0);
    case 'udi'
        idx = isAlways(abs(L) < 1);
    case 'udo'
        idx = isAlways(abs(L) >= 1);
    otherwise
        error('Keyword is not supported.');
end

Ue = [U(:, idx), U(:, ~idx)];

Se = Ue.'*A*Ue;

end

