classdef (SupportExtensionMethods = true) symhyss < symss
    %SYMHYSS Construct symbolic hybrid state-space model.
    %
    %   hsys = SYMHYSS creates an empty hybrid state-space representation.
    %
    %   A hybrid state-space model is defined by both continuous and
    %   discrete dynamics along with switching conditions and an adjacency
    %   matrix.
    %
    %   Define system dynamics by specifying the state equations for each
    %   mode. The first index corresponds to the dynamics of a mode. The
    %   second index defines the equation in the dynamics. For example,
    %                              .
    %       f(1, 3) corresponds to x3 = f3(t, x, u) in mode 1.
    %
    %   The conditions are specified as an inequality matrix, indicating
    %   the guard condition for switching to a new mode. For example,
    %
    %       guard(1, 2) = x < 0 switches from mode 1 to mode 2 when x >= 0.
    %
    %   Discontinuous jump states can be specified by setting the guard
    %   condition along the main diagonal to 0 for the mode. Any nonzero
    %   numeric values along the main diagonal are considered continuous.
    %   For example,
    %
    %       guard(1, 1) = 1 specifies that mode 1 is continuous.
    %       guard(2, 2) = 0 specifies that mode 2 is discontinuous.
    %
    %   Additionally, the adjacency matrix defines the modes which are
    %   available from the current mode. For example,
    %
    %       edge(1, 2) = 1 means the system is allowed switch to mode 2
    %       from mode 1.
    %
    %   By default, all edges are enabled.
    %
    %   If a condition is specified for a specific transition, it also
    %   modifies the adjacency matrix to allow for the transition.
    %
    %   Example (Thermostat):
    %       syms x a
    %       sys = symhyss
    %       sys.states = x
    %
    %       sys.f(1, 1) = -a*x
    %       sys.guard(1, 2) = x >= 20
    %
    %       sys.f(2, 1) = -a*(x - 30)
    %       sys.guard(2, 1) = x <= 22
    %
    %   See also symss

    %   References:
    %   Van Der Schaft, Arjan J., and Johannes Maria Schumacher. An
    %   introduction to hybrid dynamical systems. Vol. 251. London:
    %   Springer, 2000.
    %
    %   Goebel, Rafal, Ricardo G. Sanfelice, and Andrew R. Teel. "Hybrid
    %   dynamical systems." IEEE Control Systems 29.2 (2009): 28-93.
    %
    %   Savkin, Andrey V., and Robin J. Evans. Hybrid dynamical systems:
    %   controller and sensor switching problems. Springer Science &
    %   Business Media, 2002.

    % Dependent properties.
    properties (Dependent)
        % Guard Conditions
        % The elements of the guard matrix are the guard conditions for
        % staying in a current mode.
        guard

        % Adjacency Matrix
        % The elements of the adjacency matrix represent the availability
        % of switching to another mode.
        edge
    end

    % Internal properties.
    properties (Access = private)
        % State Dynamics
        % 1xn cell array. Each element in the cell array is a 1xm symbolic
        % array representing system dynamics of the mode.
        f_@cell

        guard_@sym
        edge_@double

        nmodes@double
    end

    % Constructor
    methods
        function obj = symhyss(varargin)
            %SYMHYSS Construct a hybrid state-space model.
            ni = nargin;

            % Quick copy.
            if ni == 1 && isa(varargin{1}, 'symhyss')
                obj = varargin{1};
                return;
            end

            if ni ~= 0
                if ni == 1
                    arg = varargin{1};
                    validateattributes(arg, {'sym'}, {'vector'});
                    obj.states = reshape(cell2sym(varargin(1)), [], 1);
                elseif ni == 2
                    validateattributes(varargin{1}, {'sym'}, {'vector'});
                    validateattributes(varargin{2}, {'sym'}, {'vector'});
                    obj.states = reshape(cell2sym(varargin(1)), [], 1);
                    obj.inputs = reshape(cell2sym(varargin(2)), [], 1);
                else
                    error('symhyss:invalidArguments', ...
                          'Invalid arguments to symhyss constructor.');
                end
            end
        end
    end

    % Getters and setters.
    methods
        function obj = set.guard(obj, varargin)
            % Set switching conditions for hybrid modes.
            obj = privSetGuard(obj, varargin{:});
        end
        function obj = set.edge(obj, varargin)
            % Set adjacency for hybrid modes.
            obj = privSetEdge(obj, varargin{:});
        end

        function guard = get.guard(obj)
            guard = privGetGuard(obj);
        end
        function edge = get.edge(obj)
            edge = privGetEdge(obj);
        end
    end

    % Overloadable protected methods.
    methods (Access = protected)
        function obj = privSetF(obj, varargin)
            if isempty(varargin{1})
                obj.f_ = varargin(2:end);
            else
                idx = varargin{1};
                if numel(idx) == 1
                    obj.f_{idx{1}} = reshape(cell2sym(varargin(2:end)), [], 1);
                else
                    if numel(obj.f_) < idx{1} 
                        d = sym.empty(0, 1); 
                        d(idx{2}) = cell2sym(varargin(2:end)); 
                    else
                        d = obj.f_{idx{1}};
                        d(idx{2}) = cell2sym(varargin(2:end));
                    end
                    
                    obj.f_{idx{1}} = reshape(d, [], 1);
                end
            end

            obj.nmodes = numel(obj.f);
            obj = privReshapeDim(obj);
        end
        function f = privGetF(obj, varargin)
            if isempty(varargin)
                f = obj.f_;
            else
                idx = varargin{1};
                if numel(idx) == 1
                    f = obj.f_{idx{1}};
                else
                    d = obj.f_{idx{1}};
                    f = d(idx{2:end});
                end
            end
        end

        function A = privGetA(obj, varargin)
            [tx, tu, tf] = subvars(obj);

            if isempty(varargin)
                for k = 1:numel(tf)
                    A{k} = jacobian(tf(k), tx);
                    A{k} = subs(A{k}, [tx; tu], [obj.states; obj.inputs]);
                end
            else
                idx = varargin{1};
                if numel(idx{:}) == 1
                    f = tf(idx{:});
                else
                    error('Index exceeds matrix dimensions.');
                end

                A = jacobian(f, tx);
                A = subs(A, [tx; tu], [obj.states; obj.inputs]);
            end
        end
        function B = privGetB(obj, varargin)
            [tx, tu, tf] = subvars(obj);

            if isempty(varargin)
                for k = 1:numel(tf)
                    B{k} = jacobian(tf(k), tu);
                    B{k} = subs(B{k}, [tx; tu], [obj.states; obj.inputs]);
                end
            else
                idx = varargin{1};
                if numel(idx{:}) == 1
                    f = tf(idx{:});
                else
                    error('Index exceeds matrix dimensions.');
                end

                B = jacobian(f, tu);
                B = subs(B, [tx; tu], [obj.states; obj.inputs]);
            end
        end

        function obj = privSetGuard(obj, varargin)
            validateattributes(varargin{:}, {'sym'}, {'nonempty'});
            obj.guard_ = formula(varargin{:});
        end
        function obj = privSetEdge(obj, varargin)
            validateattributes(varargin{:}, {'sym'}, {'nonempty'});
            obj.edge_ = varargin{:};
        end

        function guard = privGetGuard(obj)
            guard = obj.guard_;
        end
        function edge = privGetEdge(obj)
            edge = obj.edge_;
        end
    end

    methods (Access = private)
        function obj = privReshapeDim(obj)
            % Reshape internal matrices to be as large as the number of
            % modes, or as large as the largest matrix.
            nf = numel(obj.f_);
            [ng, mg] = size(obj.guard_);
            [ne, me] = size(obj.edge_);

            n = obj.nmodes;

            if ~isequal(size(obj.guard_), [n, n])
                C = eye([n, n], 'sym');
                if ~isempty(obj.guard_)
                    C(1:ng, 1:mg) = obj.guard_;
                end
                obj.guard_ = C;
            end

            if ~isequal(size(obj.edge_), [n, n])
                E = double(~eye([n, n], 'double'));
                if ~isempty(obj.edge_)
                    E(1:ne, 1:me) = obj.edge_;
                end
                obj.edge_ = E;
            end
        end
    end

    % Overloaded subsref & subsasgn.
    methods
        function varargout = subsref(obj, S)
            if strcmp(S(1).type, '.') && strcmp(S(1).subs, 'f')
                if numel(S) == 1
                    error('Not enough input arguments.');
                end
                
                idx = S(2).subs;
                varargout = {privGetF(obj, idx)};
                
            elseif strcmp(S(1).type, '.') && strcmp(S(1).subs, 'A')
                if numel(S) == 1
                    error('Not enough input arguments.');
                end
                
                idx = S(2).subs;
                varargout = {privGetA(obj, idx)};
                
            elseif strcmp(S(1).type, '.') && strcmp(S(1).subs, 'B')
                if numel(S) == 1
                    error('Not enough input arguments.');
                end
                
                idx = S(2).subs;
                varargout = {privGetB(obj, idx)};

            else
                [varargout{1:nargout}] = builtin('subsref', obj, S);
            end
        end

        function obj = subsasgn(obj, S, varargin)
            if strcmp(S(1).type, '.') && strcmp(S(1).subs, 'f')
                if numel(S) > 1
                    idx = S(2).subs;
                else
                    % Reject assignment to entire cell.
                    error('Not enough input arguments.');
                end
                
                obj = privSetF(obj, idx, varargin{:});
            else
                obj = builtin('subsasgn', obj, S, varargin{:});
            end
        end
    end
end
