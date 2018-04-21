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
    %       cond(1, 2) = x < 0 switches from mode 1 to mode 2 when x >= 0.
    %
    %   Discontinuous jump states can be specified by setting the guard
    %   condition along the main diagonal to 0 for the mode. Any nonzero
    %   numeric values along the main diagonal are considered continuous.
    %   For example,
    %
    %       cond(1, 1) = 1 specifies that mode 1 is continuous.
    %       cond(2, 2) = 0 specifies that mode 2 is discontinuous.
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
    %       sys.cond(1, 2) = x >= 20
    %       
    %       sys.f(2, 1) = -a*(x - 30)
    %       sys.cond(2, 1) = x <= 22
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
    properties (Dependent, AbortSet = true)
        % Guard Conditions
        cond
        
        % Adjacency Matrix
        edge
    end
    
    % Internal properties.
    properties (Access = private)
        % State Dynamics
        % 1xn cell array. Each column represents a mode. Each element in
        % the cell array is a 1xm symbolic array representing system
        % dynamics of the mode.
        f_ = cell.empty(0, 1)
        
        % Switching Conditions
        % nxn symbolic matrix. Each row and column represents a mode. Each
        % element in the cell array represents the guard conditions for
        % switching the mode.
        cond_ = sym.empty
        
        % Adjacency Matrix 
        % The elements of the adjacency matrix represent the probability of
        % switching to another mode.
        edge_ = double.empty
    end
    
    % Constructor
    methods
        function obj = symhyss(varargin)
            %SYMHYSS Construct an instance of this class
            %   Detailed explanation goes here
            ni = nargin;
            
            if ni == 1 && isa(varargin{1}, 'symhyss')
                obj = varargin{1};
                return;
            end
            
            if ni ~= 0
                % Handle states.
                if isscalar(varargin{1})
                    % First argument is numeric.
                    n = varargin{1};
                    obj.states_ = sym('x', [n, 1]);
                elseif isa(varargin{1}, 'sym')
                    obj.states = varargin(1);
                else
                    error('symhyss:invalidArgument', ...
                          'Invalid argument to symhyss constructor.');
                end

                % Handle inputs.
                if isscalar(varargin{2})
                    % Second argument is numeric.
                    m = varargin{2};
                    obj.inputs_ = sym('u', [m, 1]);
                elseif isa(varargin{2}, 'sym')
                    obj.inputs = varargin(2);
                else
                    error('symhyss:invalidArgument', ...
                          'Invalid argument to symhyss constructor.');
                end
            else
                % No output arguments.
            end
        end
    end
    
    % Getters and setters.
    methods
        function obj = set.cond(obj, varargin)
            % Set switching conditions for hybrid modes.
            obj = privSetCond(obj, varargin{:});
        end
        function obj = set.edge(obj, varargin)
            % Set adjacency for hybrid modes.
            obj = privSetEdge(obj, varargin{:});
        end
        
        function cond = get.cond(obj)
            cond = privGetCond(obj);
        end
        function edge = get.edge(obj)
            edge = privGetEdge(obj);
        end
    end
    
    % Overloadable protected methods.
    methods (Access = protected)
        function obj = privSetF(obj, varargin)
            if nargin == 2
                obj.f_ = varargin{:};
            else
                idx = varargin{1};
                if numel(obj.f_) < idx(1)
                    d = sym.empty(0, 1);
                    d(idx(2)) = cell2sym(varargin(2:end));
                else
                    d = obj.f_{idx(1)};
                    d(idx(2:end)) = cell2sym(varargin(2:end));
                end
                
                obj.f_(idx(1)) = {reshape(d, [], 1)};
            end
            
            obj = privReshapeDim(obj);
        end
        function f = privGetF(obj, varargin)
            if nargin == 1
                f = obj.f_;
            else
                idx = varargin(1);
                if numel(idx{:}) == 1
                    f = obj.f_{idx{:}};
                else
                    d = obj.f_{idx{1}};
                    f = d{idx{2}};
                end
            end
        end
        
        function A = privGetA(obj, varargin)
            [tx, tu, tf, ~] = varsub(obj);
            
            if nargin == 1
                for k = 1:numel(tf)
                    A{k} = jacobian(tf(k), tx);
                    A{k} = subs(A{k}, [tx; tu], [obj.states; obj.inputs]);
                end
            else
                idx = varargin(1);
                if numel(idx{:}) == 1
                    f = tf(idx{:});
                else
                    error('Index is out of range.');
                end

                A = jacobian(f, tx);
                A = subs(A, [tx; tu], [obj.states; obj.inputs]);
            end
        end
        function B = privGetB(obj, varargin)
            [tx, tu, tf, ~] = varsub(obj);
            
            if nargin == 1
                for k = 1:numel(tf)
                    B{k} = jacobian(tf(k), tu);
                    B{k} = subs(B{k}, [tx; tu], [obj.states; obj.inputs]);
                end
            else
                idx = varargin(1);
                if numel(idx{:}) == 1
                    f = tf(idx{:});
                else
                    error('Index is out of range.');
                end

                B = jacobian(f, tu);
                B = subs(B, [tx; tu], [obj.states; obj.inputs]);
            end
        end

        function obj = privSetCond(obj, varargin)
            obj.cond_ = formula(varargin{:});
        end
        function obj = privSetEdge(obj, varargin)
            obj.edge_ = varargin{:};
        end
        
        function cond = privGetCond(obj)
            cond = obj.cond_;
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
            [nc, mc] = size(obj.cond_);
            [ne, me] = size(obj.edge_);
            
            n = max([nf, nc, mc, ne, mc]);
            
            if ~isequal(size(obj.cond_), [n, n])
                C = eye([n, n], 'sym');
                if ~isempty(obj.cond_)
                    C(1:nc, 1:mc) = obj.cond_;
                end
                obj.cond_ = C;
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
            switch S(1).type
                case '.'
                    if numel(S) > 1
                        idx = cell2mat(S(2).subs);
                        
                        switch S(1).subs
                            case 'f'
                                varargout = {privGetF(obj, idx)};
                            case 'A'
                                varargout = {privGetA(obj, idx)};
                            case 'B'
                                varargout = {privGetB(obj, idx)};
                            otherwise
                                [varargout{1:nargout}] = builtin('subsref', obj, S);
                        end
                    else
                        [varargout{1:nargout}] = builtin('subsref', obj, S);
                    end
                otherwise
                    [varargout{1:nargout}] = builtin('subsref', obj, S);
            end
        end
        
        function obj = subsasgn(obj, S, varargin)
            switch S(1).type
                case '.'
                    if numel(S) > 1
                        idx = S(2).subs;
                        c = strcmp(idx, ':');
                        if any(c)
                            idx(c) = {1:numel(obj.f)};
                        end
                        
                        idx = cell2mat(idx);
                        
                        switch S(1).subs
                            case 'f'
                                obj = privSetF(obj, idx, varargin{:});
                            otherwise
                                obj = builtin('subsasgn', obj, S, varargin{:});
                        end
                    else
                        obj = builtin('subsasgn', obj, S, varargin{:});
                    end
                otherwise
                    obj = builtin('subsasgn', obj, S, varargin{:});
            end
        end
    end
end

