function varargout = propr(m, xidx, uidx, pattern, varargin)
%PROPR Propagate reward pattern through matrix.
%
%   R = PROPR(m, xidx, uidx, pattern)
%
%   Propagate reward pattern through matrix.
%
%       m - mdp object
%       xidx - state index
%       uidx - input index
%       pattern - reward pattern
%
%   The pattern must have exactly one NaN value, which serves as an
%   alignment indicator.
%
%   Specify all values of the state ':' with NaN. Specify the pattern as a
%   matrix centered around the current state, with the indicator specified
%   by NaN.
%
%   If no output is specified, the function updates R in the mdp object.
%
%   The pattern values represent the expected reward for taking action U at
%   state X to reach state X'.
%
%   ----------
%
%   For example, if the state space is the canonical grid world example,
%   with two states, X and Y, and one input, such as "move forward", we
%   propagate the rewards through the matrix by specifying the
%   pattern as:
%
%   pattern = [1; NaN]
%
%   R = PROPR(m, {2, 2:3}, 1, pattern)
%             ^     ^      ^     ^
%             |     |      |     reward pattern
%             |     |      input index
%             |     {x1, x2} values to iterate over (NaN for all)
%             mdp object
%
%   This will iterate over all specified values of X and Y and place the
%   pattern on top of the reward matrix. For this example, X and Y form an
%   NxM matrix, where N is the number of discrete values of X, and M is the
%   number of discrete values of Y. The grid coordinates with an overlaid
%   pattern may be displayed like below.
%
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%       |     |  1  |     |     |       |     |     |  1  |     |
%       +-----+--^--+-----+-----+       +-----+-----+--^--+-----+
%       |     | NaN |     |     |       |     |     | NaN |     |
%     X +-----+-----+-----+-----+  -->  +-----+-----+-----+-----+
%       |     |     |     |     |       |     |     |     |     |
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%       |     |     |     |     |       |     |     |     |     |
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%                   Y
%
%   However, the reward matrix defines a from/to relationship, so the
%   reward matrix is an (NxM)x(NxM)xU matrix.
%
%   For the example above, the X/Y coordinate matrix above has 16 possible
%   states.
%
%       +-----+-----+-----+-----+
%       |  1  |  5  |  9  | 13  |
%       +-----+-----+-----+-----+
%       |  2  |  6  | 10  | 14  |
%       +-----+-----+-----+-----+
%       |  3  |  7  | 11  | 15  |
%       +-----+-----+-----+-----+
%       |  4  |  8  | 12  | 16  |
%       +-----+-----+-----+-----+
%
%   This implies that the reward matrix is a 16x16x1 matrix for the
%   grid world example with one input, where each element in the matrix
%   represents the expected reward
%
%     E{x'|x, u}
%
%   Which can be read as "the expected reward for reaching x', given the
%   current state x and taking action u".
%
%               To
%          From \      1           2           3
%                +-----------+-----------+-----------+
%              1 | E{1|1, 1} | E{2|1, 1} | E{3|1, 1} |
%                +-----------+-----------+-----------+
%              2 | E{1|2, 1} | E{2|2, 1} | E{3|2, 1} | ...
%                +-----------+-----------+-----------+
%              3 | E{1|3, 1} | E{2|3, 1} | E{3|3, 1} |
%                +-----------+-----------+-----------+
%                                 ...
%
%   See also mdp, propp, propr2

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

    R(pidx(k), 1:length(Zt), uidx) = Zt;

    % Replace reward with NaN value.
    R(pidx(k), pidx(k), uidx) = p.Results.nanvalue;
end

if nargout ~= 0
    varargout{1} = R;
else
    m.R = R;
end

end
