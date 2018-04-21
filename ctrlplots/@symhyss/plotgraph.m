function plotgraph(sys, varargin)
%PLOTGRAPH Plot a graph of a hybrid state-space model.

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
parse(p, sys, varargin{:});

A = sys.edge & isAlways(sys.cond == sym(0), 'Unknown', 'true');
names = arrayfun(@(x) {char(x)}, sys.cond);
names = names(~strcmp(names, '0'));
names = names(~strcmp(names, '1'));

G = digraph(A);

plot(G, 'Layout', 'force', 'EdgeLabel', names);

end

