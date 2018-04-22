function L = lieb(f, g, x)
%LIEB Lie bracket of two functions.
%   
%   The Lie bracket is defined as:
% 
%   [f, g] = (dg/dx)*f - (df/dx)*g

L = gradient(g, x).'*f - gradient(f, x).'*g;

end

