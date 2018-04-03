function ts = gettsdata(f, rg)
%GETTSDATA Get time-series data for a function.
%   Detailed explanation goes here

p = inputParser;
validateFunction = @(F) validateattributes(F, {'sym'}, {'nonempty'});
validateRange = @(R) ...
    validateattributes(R, {'numeric'}, {'row', 'positive', 'increasing'});
addRequired(p, 'f', validateFunction);
addRequired(p, 'tspan', validateRange);
parse(p, f, rg);

syms t
Ffun = symfun(formula(f), t);
ts = Ffun(rg);

if length(ts) > 1
    for k = 1:numel(ts)
        ts(k) = {double(ts{k})};
    end
end

end

