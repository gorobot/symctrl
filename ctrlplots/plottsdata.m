function ax = plottsdata(ts, rg)
%PLOTTSDATA Plot time-series data.
%   Detailed explanation goes here

p = inputParser;
validateTsData = @(T) ...
    validateattributes(T, {'numeric'}, {'ncols', size(rg, 2)});
validateRange = @(R) ...
    validateattributes(R, {'numeric'}, {'row', 'positive', 'increasing'});
addRequired(p, 'ts', validateTsData);
addRequired(p, 'rg', validateRange);
parse(p, ts, rg);

if ~iscell(ts)
    plot(rg, ts);
    ax = gca;
    ax.XLim = [0 10];
    ax.XLimMode = 'auto';
    xlabel('Time (seconds)');
    ylabel('Amplitude');
else
    [m, n] = size(ts);
    for k = 1:numel(ts)
        subplot(n, m, k);
        plot(rg, ts{k});
        ax = gca;
        ax.XLim = [0 10];
        ax.XLimMode = 'auto';
        xlabel('Time (seconds)');
        ylabel('Amplitude');
        [in, out] = ind2sub(size(ts), k);
        title(['Output ', num2str(in), ' for Input ', num2str(out)]);
    end
end

end

