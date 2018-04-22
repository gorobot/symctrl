function G = subs(G, varargin)
%SUBS Replace a symbolic variable in state space.
%   
%   sys = SUBS(sys, ...) utility wrapper for 'subs' function.

G.Numerator = subs(G.Numerator, varargin{:});
G.Denominator = subs(G.Denominator, varargin{:});

end

