function G = subs(G, old, new)
%SUBS Replace a symbolic variable in state space.
%   Detailed explanation goes here

p = inputParser;
validateSys = @(G) isa(G, 'symtf');
addRequired(p, 'G', validateSys);
addRequired(p, 'old');
addRequired(p, 'new');

parse(p, G, old, new);

G = p.Results.G;
old = p.Results.old;
new = p.Results.new;

G.Numerator = subs(G.Numerator, old, new);
G.Denominator = subs(G.Denominator, old, new);

end

