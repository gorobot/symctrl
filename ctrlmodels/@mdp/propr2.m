function varargout = propr2(m, xidx, uidx, pattern, varargin)
%PROPR2 Summary of this function goes here
%   Detailed explanation goes here
% 
%   See also mdp, propp, propr

p = inputParser;
addRequired(p, 'm');
addRequired(p, 'xidx', ...
    @(arg) validateattributes(arg, {'numeric', 'cell'}, ...
                              {'row', 'numel', ndims(m.X)}));
addRequired(p, 'uidx', ...
    @(arg) validateattributes(arg, {'numeric'}, ...
                              {'scalar', 'positive', '<=', length(m.U)}));
addRequired(p, 'pattern', ...
    @(arg) validateattributes(arg, {'numeric'}, {'nonempty'}));
addParameter(p, 'nanvalue', 0, ...
    @(arg) validateattributes(arg, {'numeric'}, {'scalar'}));
parse(p, m, xidx, uidx, pattern, varargin{:});

if numel(find(isnan(pattern))) ~= 1
    error('Pattern must have exactly one ''NaN'' value.');
end

if ~iscell(xidx)
    idx = num2cell(xidx);
else
    idx = xidx;
end

% Replace NaN values in indices.
for k = 1:numel(idx)
    if isnan(idx{k})
        idx{k} = 1:size(m.X, k);
    end
end

% Get the subscripts for the pattern indices.
Z = zeros(size(m.X));
Z(idx{:}) = 1;
pidx = find(Z);
Z(idx{:}) = 0;

% Convert pattern to an array.
psz = num2cell(size(pattern));
for k = 1:numel(psz)
    psz{k} = 1:psz{k};
end

Z(psz{:}) = pattern;

R = m.R;

% Propagate pattern through probability matrix.
for k = 1:numel(pidx)
    % "Fit" pattern into state space.
    Zt = fitpattern(m.X, Z, pidx(k));
    Zt = reshape(Zt, 1, []);

    Zt = repmat(Zt, length(Zt), 1);

    R(:, 1:length(Zt), uidx) = R(:, 1:length(Zt), uidx) + Zt;

    % Replace reward with NaN value.
    R(:, pidx(k), uidx) = p.Results.nanvalue;
end

if nargout ~= 0
    varargout{1} = R;
else
    m.R = R;
end

end
