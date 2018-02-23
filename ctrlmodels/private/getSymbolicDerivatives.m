function D = getSymbolicDerivatives(expr)
%GETSYMBOLICDERIVATIVES Finds all symbolic derivatives in expression.
%   Detailed explanation goes here

syms t
vars = symvar(expr);
vars = vars(vars ~= t);

ch = expr;

safety = 0;

% Isolate derivatives by removing all terms that do not contain
% derivatives.
while nnz(has(ch, vars)) ~= 0
    ch = children(ch);
    ch = cell2sym(ch);
    
    ch = ch(has(ch, {'diff', 'int'}));
    
    safety = safety + 1;
    if safety == 10
        break
    end
end

D = ch;

end

