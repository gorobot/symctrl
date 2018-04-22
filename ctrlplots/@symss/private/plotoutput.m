function plotoutput(y, tspan)
%PLOTOUTPUT Plots the output of lsim or nlsim.
%   
%   Plots the output of a simulation. Handles SISO and MIMO cases.

p = inputParser;
addRequired(p, 'y');
addRequired(p, 'tspan');
parse(p, y, tspan);

for k = 1:numel(y)
    out = y{k};
    [m, n] = size(out);
    for p = 1:numel(out)
        ax = subplot(n, m, p);
        ax.NextPlot = 'add';
        
        h = fplot(out(p));
        h.XRange = tspan; 
        h.XRangeMode = 'auto';
        
        [input, output] = ind2sub([m, n], p);
        title(['Output [', num2str(output), ', ', num2str(input), ']']);
    end
end

end

