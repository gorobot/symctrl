function [f, g] = nlsep(sys)
%NLSEP Separate nonlinear functions into f(x) and g(x).
%   
%   [f, g] = NLSEP(sys) separates the state equations into f(x) and g(x).
% 
%   From state equations of the form:
%   .
%   x = f(x) + g(x)*u
% 
%   The function returns f(x) and g(x).

[A, ~, ~, ~] = getabcd(sys);

f = cell([size(A, 1), 1]);
g = cell([size(A, 1), 1]);

for k = 1:numel(sys.f)
    C = coeffs(sys.f(k), sys.inputs, 'All');
    if numel(C) == 2
        f{k} = C(2);
        g{k} = C(1);
    else
        f{k} = C;
        g{k} = 0;
    end
end

f = cell2sym(f).';
g = cell2sym(g).';

end

