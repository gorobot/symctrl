function [tx, tu, tf, tg] = varsub(obj, varargin)
%VARSUB Replaces variables with dummy variables for symbolic operations.

nx = cell(size(obj.states));
nx(:) = {'SUBX'};

nu = cell(size(obj.inputs));
nu(:) = {'SUBU'};

tx = sym(genvarname(nx, who));
tu = sym(genvarname(nu, who));

n = numel(obj.f_);
tf = cell([1, n]);

for k = 1:n
    tf{k} = subs(obj.f(k), [obj.states; obj.inputs], [tx; tu]);
end

tg = subs(obj.g, [obj.states; obj.inputs], [tx; tu]);

end

