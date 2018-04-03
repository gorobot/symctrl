function L = lie(f, x, h)
%LIE Lie derivative of a function.
%   
%   The Lie derivative is defined as:
%   
%   L = (df(.)/dx)*h(.)

L = gradient(f, x).'*h;

end

