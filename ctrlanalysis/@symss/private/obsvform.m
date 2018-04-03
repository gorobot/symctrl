function T = obsvform(sys)
%OBSVFORM Observable canonical form.
%   
%   T = OBSVFORM(sys) converts a state space system to observable
%   canonical form.
% 
%   The transfer function defined by:
% 
%   Y(s)   b0*s^(n) + b1*s^(n-1) + ... + bn
%   ---- = --------------------------------
%   U(s)       s^(n) + a1*s^(n-1) + an
% 
%   Converts to the state space representation:
% 
%   .   |  0   0  -a3 |    | b3-a3*b0 |
%   x = |  1   0  -a2 |x + | b2-a2*b0 |u
%       |  0   1  -a1 |    | b1-a1*b0 |
%   
%   y = |  0   0   1  |x + b0*u

% T = ctrbform(sys);
% 
% T.f = T.A.'*T.states + T.C.'*T.inputs;
% T.f = T.B.'*T.states + T.D*T.inputs;

[A, B, C, D] = getabcd(sys);

% Get the number of outputs from the C matrix size.
p = size(C, 1);

% Compute the observability matrix.
Ob = obsv(sys);

% If the system is not fully observable, we can determine the
% unobservable states and compute the canonical form from the
% states which are in Ao.
if length(A) > rank(Ob)
    warning('System has uncontrollable states.')
end

n = rank(Ob);
if p == 1 % Single output case (p = 1)
    Oi = inv(Ob);
    q = Oi(:, end);
    Q = [q, zeros(n, n-1)];

    for k = 2:size(Oi, 2)
        Q(:, k) = A^(k-1)*q;
    end

else % Multiple output case (p > 1)
    li = [1];

    % Get the first n linearly independent rows in Ob.
    for k = 2:size(Ob, 1)
        s = Ob([li k], :);
        if rank(s) == size(s, 1)
            % Include this index.
            li = [li k];

            % Stop if we have the right amount of vectors.
            if length(li) == n
                break
            end
        end
    end

    % Group the rows based on their order.
    nu = ones(1, p);
    if p > 1
        for k = 1:p
            [~, u] = intersect(li, k:p:size(Ob, 1));
            nu(k) = length(u);
            allIdx = 1:n;
            allIdx(u) = [];
            allIdx = [allIdx u'];
            li = li(allIdx);
        end
    end

    L = inv(Ob(li, :));
    sigma = cumsum(nu);
    q = L(:, sigma);
    Q = [];
    %     P = zeros(n, sum(mu));

    for k = 1:size(q, 2)
        for a = 1:nu(k)
            Q = [Q, A^(a-1)*q(:, k)];
        end
    end
end

% Compute the similarity transformations using P. This is
% equivalent to the command:
% 
% sys = sys*inv(Q);
% 
% However, it can be computationally intensive to compute the
% inverse of Q, so we compute the similarity transformation here
% rather than using 'simtrans'.
A = Q\A*Q;
B = Q\B;
C = C*Q;

T = sys;
T.f = A*T.states + B*T.inputs;
T.g = C*T.states + D*T.inputs;

end

