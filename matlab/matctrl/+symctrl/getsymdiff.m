function D = getsymdiff(expr)
%GETSYMDIFF Finds all symbolic derivatives in expression.

validateattributes(expr, {'sym'}, {'nonempty'});

if ~has(expr, 'diff')
    D = sym.empty;
    return;
end

D = formula(expr);

% Isolate derivatives by removing terms that do not contain derivatives.
while true
    for k = 1:numel(D)
        ch = {children(D(k))};
        ch = cell2sym(ch);
        
        h = has(ch, 'diff');
        if any(h)
            D = [D(1:k - 1), ch(h), D(k + 1:end)];
        end
    end
    
    if ~any(has(ch, 'diff'))
        break;
    end
end

end

