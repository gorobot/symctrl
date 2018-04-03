function T = ctrbform(sys)
%CTRBFORM Controllable canonical form.
%   
%   T = CTRBFORM(sys) converts a state space system to controllable
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
%   .   |  0   1   0  |    | 0 |
%   x = |  0   0   1  |x + | 0 |u
%       | -a3 -a2 -a1 |    | 1 |
%   
%   y = | b3-a3*b0 b2-a2*b0 b1-a1*b0 |x + b0*u

[A, B, C, D] = getabcd(sys);

% Get the number of inputs from the B matrix size.
m = size(B, 2);

% Compute the controllability matrix.
Co = ctrb(sys);

% If the system is not fully controllable, we can determine the
% uncontrollable states and compute the canonical form from the
% states which are in Ac.
if length(A) > rank(Co)
    warning('System has uncontrollable states.')
end

n = rank(Co);

if m == 1 % Single-input case (m = 1)
    Ci = inv(Co);
    q = Ci(end, :);
    P = [q; zeros(n-1, n)];

    for k = 2:size(Ci, 1)
        P(k, :) = q*A^(k-1);
    end
else % Multiple input case (m > 1)

    li = [1];

    % Get the first n linearly independent columns in Co.
    for k = 2:size(Co, 2)
        s = Co(:, [li k]);
        if rank(s) == size(s, 2)
            % Include this index.
            li = [li k];

            % Stop if we have the right amount of vectors.
            if length(li) == n
                break
            end
        end
    end

    % Group the columns based on their order.
    mu = ones(1, m);
    if m > 1
        for k = 1:m
            [~, u] = intersect(li, k:m:size(Co, 2));
            mu(k) = length(u);
            allIdx = 1:n;
            allIdx(u) = [];
            allIdx = [allIdx u'];
            li = li(allIdx);
        end
    end

    L = inv(Co(:, li));
    sigma = cumsum(mu);
    q = L(sigma, :);
    P = [];
    %     P = zeros(n, sum(mu));

    for k = 1:size(q, 1)
        for a = 1:mu(k)
            P = [P; q(k, :)*A^(a-1)];
        end
    end
end

% Compute the similarity transformations using P.
A = P*A/P;
B = P*B;
C = C/P;

T = sys;
T.f = A*T.states + B*T.inputs;
T.g = C*T.states + D*T.inputs;

end

