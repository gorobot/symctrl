function plotgraph(sys, varargin)
%PLOTGRAPH Plot a graph of a hybrid state-space model.

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
parse(p, sys, varargin{:});

A = sys.edge;
names = arrayfun(@(x) {char(x)}, sys.cond);
names = names(~strcmp(names, '0'));

G = digraph(A);

plot(G, 'Layout', 'force', 'EdgeLabel', names);

end

