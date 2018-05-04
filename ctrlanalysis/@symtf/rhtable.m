function [T, rhp, lhp] = rhtable(G, varargin)
%RHTABLE Generates a Routh-Hurwitz table for stability analysis.
% 
%   [T, rhp, lhp] = RHTABLE(G) computes the Routh-Hurwitz table(s) for a given
%   system. It returns the tables as 'T', as well as the number of poles in the
%   right-half plane equal to the number of sign changes in the first column of
%   the table in 'rhp' and the number of poles in the left hand plane 'lhp'. If
%   no output is specified, the table is displayed to the command window.
% 
%   NOTE: If the transfer function 'G' contains undefined symbolic variables,
%   the number of poles in the right-hand plane may not be correct. The function
%   uses XOR and ISALWAYS to evaluate sign changes in the first column of the
%   R-H table. For numerical symbolic values, this achieves the correct number
%   of poles in the right-hand plane. For symbolic variables, this is not
%   guaranteed to work.

p = inputParser;
addRequired(p, 'G');
addParameter(p, 'reverse', false);
parse(p, G, varargin{:});

syms s
den = G.Denominator;

T = cell(size(den));
rhp = sym(zeros(size(den)));
lhp = sym(zeros(size(den)));

% For each transfer function presented, compute the Routh-Hurwitz table.
for k = 1:numel(den)
    co = coeffs(den(k), s, 'All');
    deg = co - 1;
    if deg == 0
        T{k} = 0;
        rhp(k) = 0;
        lhp(k) = 0;
        continue
    end
    
    nc = mod(length(co), 2) + length(co);
    q = sym(zeros(nc/(nc/2), nc/2));
    
    % If the parameter specifying we should use reverse coefficients is not
    % set, flip the coefficients to correspond to the regular R-H table.
    if ~p.Results.reverse
        co = fliplr(co);
    end
    
    for m = 1:length(co)
        q(m) = co(m);
    end
    
    t = sym(zeros(length(co), nc/2));
    t(1:nc/(nc/2), 1:nc/2) = q;
    
    for m = 3:length(co)
        for n = 1:nc/2
            a = t(m-2, 1);
            c = t(m-1, 1);
            
            if n == size(t, 2)
                b = 0;
                d = 0;
            else
                b = t(m-2, n+1);
                d = t(m-1, n+1);
            end
            D = [a, b; c, d];
            t(m, n) = -det(D)/c;
        end
    end
    
    rowNames = strcat('s^', num2str(flipud((1:length(co))')));
    T{k} = array2table(t, 'RowNames', cellstr(rowNames));
    
    % Figure out how many sign changes there are. 
    tc1 = sign(t(:, 1));
    pos = tc1 > 0;
    changes = xor(pos(1:end - 1), pos(2:end));
    rhp(k) = nnz(isAlways(changes));
    lhp(k) = length(tc1) - rhp(k);
end

end

