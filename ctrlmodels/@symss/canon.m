function sys = canon(sys, varargin)
%CANON Summary of this function goes here
% 
%   SYS = CANON(SYS, ...) converts a state space representation to a
%   canonical form via similarity transformation. 
p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);
addParameter(p, 'Form', 'c');

parse(p, sys, varargin{:});

sys = p.Results.sys;
form = p.Results.Form;

A = sys.A; B = sys.B; C = sys.C; D = sys.D;

% Determine the output 
switch form
    % Controllable or companion form.
    case {'c', 'C', 'co', 'Co', 'controllable', 'companion'} 
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

        sys = symss(A, B, C, D);
        
    % Observable form.
    case {'o', 'O', 'ob', 'Ob', 'observable'} 
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

        sys = symss(A, B, C, D);
        
    % Diagonal or Jordan form.
    case {'d', 'diag', 'diagonal', 'j', 'jordan', 'Jordan'}
        % Get the matrix of eigenvectors.
        [V, ~] = eig(A);

        % Compute the similarity transformations using V.
        A = V\A*V;
        B = V\B;
        C = C*V;

        sys = symss(A, B, C, D);
        
    otherwise
        error('Invalid form specified. Must be one of: controllable, observable, jordan')
end

end

