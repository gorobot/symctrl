function G = simplify(G, varargin)
%SIMPLIFY Simplify a transfer function model.

fun = G.tf;
fun = simplify(fun, varargin{:});

[N, D] = numden(fun);
G.Numerator = N;
G.Denominator = D;

end

