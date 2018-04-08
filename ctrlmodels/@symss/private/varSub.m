function [tx, tu, tf, tg] = varsub(obj, varargin)
%VARSUB Replaces variables with dummy variables for symbolic operations.

nx = cell(size(obj.states_));
nx(:) = {'SUBX'};

nu = cell(size(obj.inputs_));
nu(:) = {'SUBU'};

tx = sym(genvarname(nx, who));
tu = sym(genvarname(nu, who));

tf = subs(obj.f, [obj.states; obj.inputs], [tx; tu]);
tg = subs(obj.g, [obj.states; obj.inputs], [tx; tu]);

end

