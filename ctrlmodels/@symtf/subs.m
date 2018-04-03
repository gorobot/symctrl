function H = subs(G, varargin)
%SUBS Replace a symbolic variable in state space.
%   
%   sys = SUBS(sys, ...) utility wrapper for 'subs' function.

H = G;

H.Numerator = subs(H.Numerator, varargin{:});
H.Denominator = subs(H.Denominator, varargin{:});

end

