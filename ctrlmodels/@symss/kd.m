function varargout = kd(sys)
%KD Compute the Kalman decomposition of a state space.
% 
%   Ksys = KD(sys) computes the Kalman decomposition of a state
%   space realization.
%   [Ksys, n] = KD(sys)
%   [A, B, C, D] = KD(SYS)
n_out = nargout;

p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);

parse(p, sys);

% Find the controllable and uncontrollable states of the system. 
Co = ctrb(sys);
Ob = obsv(sys);

Co_basis = orth(Co, 'real', 'skipnormalization');
Ob_basis = null(Ob);

% Compute the dimensions of the submatrices.
% n = length(sys.A);
% 
% n_c = rank(Co);
% n_cb = n - n_c;
% 
% n_o = rank(Ob);
% n_ob = n - n_o;
% 
% n_cob = rank(intersect(Co_basis, Ob_basis));

% if n_cb
%     Q = orth([Co, eye(size(Co, 1))], 'real', 'skipnormalization');
%     Cosys = sys*inv(Q);
% end

% if n_ob
%     P = orth([Ob.', eye(size(Ob, 2))], 'real', 'skipnormalization');
%     Obsys = sys*P.';
% end

% Compute the similarity transform matrix, P.
Q = orth([Co_basis, Ob_basis, eye(length(sys.A))], ...
    'real', 'skipnormalization');
P = inv(Q);

% Compute the Kalman decomposition of the system.
Ksys = sys*P;

if n_out == 1
    varargout{1} = Ksys;
elseif n_out == 2
    varargout{1} = Ksys;
    
    n_c = rank(Co);
    n_o = rank(Ob);
    varargout{2} = [n_c n_o];
elseif n_out > 3
    varargout{1} = Ksys.A;
    varargout{2} = Ksys.B;
    varargout{3} = Ksys.C;
%     A = sym('A%d%d', [4 4]);
%     
%     A11 = [1 0; 1 1];
%     
%     A = subs(A, [A(1,2) A(1,4) A(3,1) A(3,2) A(3,4) A(4,1) A(4,2)], ...
%         [0 0 0 0 0 0 0]);
    
    if n_out == 4
        varargout{4} = Ksys.D;
    end
end

end

