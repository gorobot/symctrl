function varargout = decompose(sys)
%DECOMPOSE Compute the Kalman decomposition of a state-space realization.
%
%   sys = DECOMPOSE(sys) computes the Kalman decomposition of a state-space
%   realization.
%
%   [sys, n] = DECOMPOSE(sys) computes the Kalman decomposition of a
%   state-space realization and returns the dimensions of the controllable
%   and observable subspace of A.
%
%   [A, B, C, D] = DECOMPOSE(sys) computes the Kalman decomposition of a
%   state-space realization and returns the controllable and observable
%   subspace of the system.

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
parse(p, sys);

[A, B, C] = sys.getabcd();

n = size(A, 1);
m = size(B, 2);
p = size(C, 1);

% Find the controllability and observability matrices.
Co = ctrbs(A, B);
Ob = obsvs(A, C);

N = null(Ob);

% Compute an orthonormal transformation matrix.
P = orth([Co, N, eye(size(A))], 'real');

% Compute the Kalman decomposition of the system.
T = symss2symss(sys, P.');

nout = nargout;
if nout == 1
    varargout{1} = T;
else
    nr = rank(Co);
    no = rank(N);

    if nout == 2
        varargout{1} = T;
        varargout{2} = [nr, no];
    elseif nargout > 3
        n = min([nr, no]);
        varargout{1} = T.A(1:n, 1:n);
        varargout{2} = T.B(1:n, :);
        varargout{3} = T.C(:, 1:n);
        if nout == 4
            varargout{4} = T.D;
        end
    end
end

end
