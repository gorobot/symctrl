function [F, args] = getsymfuns(expr)
%GETSYMFUNS Finds all symbolic functions in an expression.

validateattributes(expr, {'sym'}, {'nonempty'});

args = argnames(expr);
F = formula(expr);

if ~isa(expr, 'symfun') || ~any(has(F, args))
    F = sym.empty;
    args = sym.empty;
    return;
end

% Isolate functions by removing terms that are not symbolic functions.
while true
    for k = 1:numel(F)
        ch = {children(F(k))};
        ch = cell2sym(ch);

        h = has(ch(~ismember(ch, args)), args);
        if any(h)
            F = [F(1:k - 1), ch(h), F(k + 1:end)];
        end
    end

    if ~any(has(ch, args)) || ...
            all(arrayfun(@(x) isequal(x, args), cell2sym({children(F)})))
        break;
    end
end

end
