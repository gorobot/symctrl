function X = mat2se(A)

X = cell(size(A));

switch (class(A))
    case 'cell'
        X = cellfun(@(x) {char(x)}, A);
    case 'string'
        X = cellstr(A);
    case 'char'
        X = {A};
    case 'sym'
        X = sym2cell(A);
        X = cellfun(@(x) {char(x)}, X);
    case 'symfun'
        X = sym2cell(formula(A));
        X = cellfun(@(x) {char(x)}, X);
    otherwise
        if isnumeric(A)
            X = num2cell(A);
            X = cellfun(@(x) {num2str(x)}, X);
        else
            error('SYMCTRL::InvalidInput', 'Cannot convert input to C type.');
        end
end

end
