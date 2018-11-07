function X = se2mat(A)
% SE2MAT Convert SymEngine output to Matlab.

X = cell(size(A));
tf = true;

for k = 1:numel(A)
    % Attempt to convert numeric.
    if tf
        [r, tf] = str2num(A{k});
        X(k) = {r};
    end

    if ~tf
        try
            % Attempt to convert symbolic.
            r = str2sym(A{k});
            X(k) = {r};

        catch ME
            disp(ME.identifier);

            if any(strcmp(ME.identifier, 'MATLAB::unable_to_convert'))
                rethrow(ME);
            else
                rethrow(ME);
            end
        end
    end
end

if tf
    X = cell2mat(X);
else
    X = cell2sym(X);
end

end
