function varargout = propp(m, xidx, uidx, pattern)
%PROPP Propagate probability pattern through matrix.
%
%   P = PROPP(m, xidx, uidx, pattern)
%
%   Propagate probability pattern through matrix.
%
%       m - mdp object
%       xidx - state index
%       uidx - input index
%       pattern - probability pattern
%
%   The pattern must have exactly one NaN value, which serves as an
%   alignment indicator.
%
%   Specify all values of the state ':' with NaN. Specify the pattern as a
%   matrix centered around the current state, with the indicator specified
%   by NaN.
%
%   If no output is specified, the function updates P in the mdp object.
%
%   The pattern values (omitting the NaN) cannot exceed 1, representing the
%   probability of reaching a future state. If the values of the pattern
%   are less than 1, the NaN value is replaced with the remaining
%   probability.
%
%   ----------
%
%   For example, if the state space is the canonical grid world example,
%   with two states, X and Y, and one input, such as "move forward", we
%   propagate the probabilities through the matrix by specifying the
%   pattern as:
%
%   pattern = [  0 , 0.8,  0  ;
%               0.1, NaN, 0.1 ;
%                0 ,  0 ,  0  ]
%
%   P = PROPP(m, [NaN, NaN], 1, pattern);
%             ^       ^      ^     ^
%             |       |      |     probability pattern
%             |       |      input index
%             |       {x1, x2} values to iterate over (NaN for all)
%             mdp object
%
%   This will iterate over all specified values of X and Y and place the
%   pattern on top of the probability matrix. For this example, X and Y
%   form an NxM matrix, where N is the number of discrete values of X, and
%   M is the number of discrete values of Y. The grid coordinates with an
%   overlaid pattern may be displayed like below.
%
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%       |  0  | 0.8 |  0  |     |       |     |  0  | 0.8 |  0  |
%       +-----+--^--+-----+-----+       +-----+-----+--^--+-----+
%       | 0.1 | NaN | 0.1 |     |       |     | 0.1 | NaN | 0.1 |
%     X +-----+-----+-----+-----+  -->  +-----+-----+-----+-----+
%       |  0  |  0  |  0  |     |       |     |  0  |  0  |  0  |
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%       |     |     |     |     |       |     |     |     |     |
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%                   Y
%
%   However, the probability matrix defines a from/to relationship, so the
%   probability matrix is an (NxM)x(NxM)xU matrix.
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
%   This implies that the probability matrix is a 16x16x1 matrix for the
%   grid world example with one input, where each element in the matrix
%   represents the conditional probability
%
%     P{x'|x, u}
%
%   Which can be read as "the probability that x' will be reached, given
%   the current state x and taking action u".
%
%               To
%          From \      1           2           3
%                +-----------+-----------+-----------+
%              1 | P{1|1, 1} | P{2|1, 1} | P{3|1, 1} |
%                +-----------+-----------+-----------+
%              2 | P{1|2, 1} | P{2|2, 1} | P{3|2, 1} | ...
%                +-----------+-----------+-----------+
%              3 | P{1|3, 1} | P{2|3, 1} | P{3|3, 1} |
%                +-----------+-----------+-----------+
%                                 ...
%
%   In order to propagate the pattern into the space, the pattern is
%   "squeezed" into a smaller space by folding the probabilities along each
%   dimension into the available space. For example, if we apply the
%   pattern above to state 1 and 5, the probabilities that would lie
%   outside of the possible space are added along the X and Y dimensions
%   iteratively, where NaN (which would be in state 1 and 5) is replaced by
%   the remaining probability. Example below.
%
%       +--^--+-----+-----+-----+       +-----+--^--+-----+-----+
%       | 0.9 | 0.1 |     |     |       | 0.1 | 0.8 | 0.1 |     |
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%       |  0  |  0  |     |     |       |  0  |  0  |  0  |     |
%     X +-----+-----+-----+-----+  -->  +-----+-----+-----+-----+
%       |     |     |     |     |       |     |     |     |     |
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%       |     |     |     |     |       |     |     |     |     |
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%                   Y
%
%   See also mdp, propr, propr2

% References:
% https://people.eecs.berkeley.edu/~pabbeel/cs287-fa12/slides/mdps-exact-methods.pdf

p = inputParser;
addRequired(p, 'm');
addRequired(p, 'xidx', ...
    @(arg) validateattributes(arg, {'numeric', 'cell'}, ...
                              {'row', 'numel', ndims(m.X)}));
addRequired(p, 'uidx', ...
    @(arg) validateattributes(arg, {'numeric'}, ...
                              {'scalar', 'positive', '<=', length(m.U)}));
addRequired(p, 'pattern', ...
    @(arg) validateattributes(arg, {'numeric'}, {'nonnegative'}));
parse(p, m, xidx, uidx, pattern);

psum = sum(pattern(:), 'omitnan');
if psum > 1
    error('Probabilities in pattern must not exceed 1.');
end

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

P = m.P;

% Propagate pattern through probability matrix.
for k = 1:numel(pidx)
    % "Squeeze" pattern into state space.
    Zt = squeezepattern(m.X, Z, pidx(k));
    Zt = reshape(Zt, 1, []);

    % Ensure probabilities equal 1.
    Zt(isnan(Zt)) = 1 - sum(Zt, 'omitnan');

    P(pidx(k), 1:length(Zt), uidx) = Zt;
end

if nargout ~= 0
    varargout{1} = P;
else
    m.P = P;
end

end
