function varargout = dspace(m, sys, blocks, varargin)
%DSPACE Discretize a state-space into blocks.
%
%   X = DSPACE(m, sys, blocks) computes a discretized state space for use
%   with an MDP.
%
%   The function partitions a continuous state space into discrete chunks,
%   allowing the MDP to utilize a discretized model for planning.
%
%   [X, in, Xf] = DSPACE(m, sys, blocks) computes a discretized state space
%   for use with an MDP and also returns a symbolic matrix of inequalities
%   and an indexing function, which can be used to determine the current
%   partition the state is currently in.
% 
%   If no output is specified, the function updates X in the mdp object.
%
%   For example, discretizing a 2-D state space using the following
%   command:
%
%   X = DSPACE(m, sys, {[0, 3, 8, 10], [0, 2, 5]})
%
%   would create the following space discretization:
%
%     x2
%     ^
%     |
%   5 +- - - - - - - + - - - - - - - - - - - -+- - - - -+
%     |              |                        |         |
%   4 +              |                        |         |
%     |    {1,2}     |         {2,2}          |  {3,2}  |
%   3 +              |                        |         |
%     |              |                        |         |
%   2 +- - - - - - - + - - - - - - - - - - - -+- - - - -+
%     |              |                        |         |
%   1 +    {1,1}     |         {2,1}          |  {3,1}  |
%     |              |                        |         |
%   0 +----+----+----+----+----+----+----+----+----+----+-> x1
%     0    1    2    3    4    5    6    7    8    9    10
%
%   The symbolic matrix is indexed according to the states. For example,
%
%   X(x1, x2, x3, ...)
%
%   For the above example, this means that for {x1 = 9, x2 = 3}, the
%   partition which would return a 1 when the equalities are evaluated
%   would be {3, 2} = 6.
%
%   The inequalities default to include the bounds to the right, meaning
%   for {x1 = 8, x2 = 2} in the above example, the partition that would
%   return a 1 would be {2, 1} = 2. In order to flip the inequalities, set
%   the 'LeftInequalities' parameter to true. If set, the above example
%   would evaluate to partition {3, 2} = 6.
%
%   Example:
%       syms x1 x2
%       sys = symss
%       sys.states = [x1, x2]
%       
%       m = mdp
%       [X, in, Xf] = DSPACE(m, {[0, 3, 8, 10], [0, 2, 5]})
%       [x1, x2] = ind2sub(size(X), Xf(5, 2))
%
%   Outputs:
%       x1 = 2
%       x2 = 1
%
%   See also mdp

p = inputParser;
addRequired(p, 'm');
addRequired(p, 'sys');
addRequired(p, 'blocks', ...
    @(arg) validateattributes(arg, {'cell'}, {'nonempty'}));
addParameter(p, 'LeftInequalities', false)
parse(p, m, sys, blocks, varargin{:});

left = p.Results.LeftInequalities;

blocks = reshape(p.Results.blocks, 1, []);
for b = blocks
    validateattributes(b{:}, {'numeric'}, {'increasing'});
end
sz = arrayfun(@(x) length(x{:}), blocks);
n = numel(sz);

L = cell(1, n);
[L{:}] = ndgrid(blocks{:});

X = double(ones(sz - 1));
for k = 1:numel(X)
    X(k) = k;
end

in = sym(ones(sz - 1));
idx = cell(size(sz));

for k = 1:numel(L)
    d = L{k};

    for r = 1:numel(d)
        [idx{:}] = ind2sub(sz, r);
        if any([idx{:}] >= sz)
            continue;
        end

        ni = num2cell([idx{:}] + 1);

        if left
            % Bounds are to the left.
            in(idx{:}) = ...
                        d(idx{:}) <= sys.states(k) ...
                        & sys.states(k) < d(ni{:}) ...
                        & in(idx{:});
        else
            % Default behavior. Bounds are to the right.
            in(idx{:}) = ...
                        d(idx{:}) < sys.states(k) ...
                        & sys.states(k) <= d(ni{:}) ...
                        & in(idx{:});
        end
    end
end

if nargout ~= 0
    % Return the indices of the discretized space.
    varargout{1} = X;
    
    if nargout > 1
        varargout{2} = in;

        % Create helper function.
        Xf = symfun(in, sys.states);
        Xf = @(varargin) find(isAlways(Xf(varargin{:})));

        varargout{3} = Xf;
    end
else
    m.X = X;
end

end
