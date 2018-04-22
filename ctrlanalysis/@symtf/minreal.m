function T = minreal(G)
%MINREAL Computes the minimal realization of a transfer function.
%   
%   T = MINREAL(G) computes the minimal realization of a transfer function
%   by performing pole-zero cancellations.

tf = G.tf;
[N, D] = numden(tf);
T = symtf(N, D);

end

