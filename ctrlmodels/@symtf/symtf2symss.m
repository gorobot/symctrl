function sys = symtf2symss(G)
%SYMTF2SYMSS Convert a symbolic transfer function to a symbolic state space
%model.
% 
%   sys = SYMTF2SYMSS(sys)
%   converts a symbolic transfer function to a symbolic state space model.

%   References:
%   H. R. Pota, "MIMO systems-transfer function to state-space," in IEEE 
%   Transactions on Education, vol. 39, no. 1, pp. 97-99, Feb 1996.

% SISO case.
if numel(G.tf) == 1
    num = G.num_{:};
    den = G.den_{:};
    
    n = max([numel(num) numel(den)]) - 1;
    
    b = num./num(1);
    a = den./den(1);
    a = [zeros(1, length(b) - length(a)), a];
    b = [zeros(1, length(a) - length(b)), b];

    A = sym(zeros(n));
    A(1:end - 1, 2:end) = eye(n - 1);
    A(end, :) = fliplr(-a(2:end));

    B = sym([zeros(n - 1, 1); 1]);

    C = fliplr(b(2:end)) - fliplr(a(2:end)).*b(1);

    D = sym(b(1));

    sys = symss(A, B, C, D);
else
    for k = 1:numel(G.Denominator)
        f = arrayfun(@(D) {factor(D, G.Variable)}, G.Denominator(:, k));
        cf = intersect(f{:});

    %     Z{k} = ilaplace(x(k)*cf == sys.inputs(k));
        % iztrans
        C = coeffs(cf, G.Variable, 'All');
        C = -C(2:end)./C(1);

        vn = {'x'};
        nx = cell([1, numel(C)]);
        nx(:) = vn;

        s = arrayfun(@(x) {char(x)}, sys.states);
        if ~isempty(s)
            vn = [vn, s];
        end

        x = cell2sym(genvarname(nx, vn));

    %     sys.f(k) = 
    end

    for k = G.Denominator
        ncf = arrayfun(@(F) {setdiff(cell2sym(F), cf)}, f);
    end
end
    
end

