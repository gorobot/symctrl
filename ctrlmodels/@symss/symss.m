classdef (SupportExtensionMethods = true) symss < ctrlmodel
    %SYMSS Construct symbolic state-space model or convert model to
    %symbolic state-space.
    %
    %   sys = SYMSS creates an empty state-space representation.
    %
    %   A state-space model is defined by state equations and
    %   output equations, given by:
    %
    %       dx/dt = f(t, x, u)
    %           y = g(t, x, u)
    %
    %   In order to define a state-space model, begin with an empty state
    %   space model, define states and inputs, and then define state
    %   equations and output equations.
    %
    %   sys = SYMSS(A, B, C, D)
    %   Creates a state space model using the matrices A, B, C, D.
    %
    %       dx/dt = Ax(t) + Bx(t)
    %        y(t) = Cx(t) + Du(t)
    %
    %   A must be an nxn matrix, B must be an nxm matrix, and C
    %   must be a pxn matrix. If D is specified, it must be a pxm
    %   matrix.
    %
    %   sys = SYMSS(states, inputs) creates a state space model
    %   using the state variables and input variables provided.
    %
    %   sys = SYMSS(Ts) creates a discrete state space model with sampling
    %   time Ts.

    %   References:
    %   Antsaklis, Panos J., and Anthony N. Michel. A linear systems
    %   primer. Vol. 1. Boston: Birkh�user, 2007.

    % State equations.
    properties (Dependent)
        % State Equations
        f
        % Ouput Equations
        g
    end

    % State matrices.
    properties (SetAccess = immutable, Dependent)
        % State matrix A
        A
        % Input matrix B
        B
        % Output matrix C
        C
        % Feed-forward matrix D
        D
    end

    % State variables.
    properties (Dependent)
        % State Variables
        states
        % Input Variables
        inputs
    end

    % Hidden dependent properties.
    properties (Dependent, Hidden)
        % Sampling Time
        Ts
    end

    % Internal properties.
    properties (Access = private)
        f_@sym
        g_@sym

        states_@sym
        inputs_@sym

        Ts_@double
    end

    % Constructor
    methods
        function obj = symss(varargin)
            %SYMSS Construct a symbolic state space model.
            ni = nargin;

            % Quick copy.
            if ni == 1 && isa(varargin{1}, 'symss')
                obj = varargin{1};
                return;
            end

            if ni ~= 0
                if ni == 1
                    arg = varargin{1};
                    if isa(arg, 'symtf')
                        % Convert transfer function to state-space.
                        obj = symtf2symss(arg);
                    elseif isa(arg, 'sym')
                        % First argument is a vector of states.
                        validateattributes(arg, {'sym'}, {'vector'});
                        obj.states_ = reshape(cell2sym(varargin(1)), [], 1);
                    else
                        % First argument is just a number.
                        % This indicates a discrete system.
                        validateattributes(arg, {'numeric'}, {'positive'});
                        obj.Ts_ = double(arg);
                    end
                elseif ni == 2
                    validateattributes(varargin{1}, {'sym'}, {'vector'});
                    validateattributes(varargin{2}, {'sym'}, {'vector'});
                    obj.states_ = reshape(cell2sym(varargin(1)), [], 1);
                    obj.inputs_ = reshape(cell2sym(varargin(2)), [], 1);
                elseif ni == 4
                    % Ensure symbolic.
                    for k = 1:ni
                        varargin{k} = sym(varargin{k});
                    end

                    validateabcd(varargin{:})

                    n = size(varargin{1}, 1);
                    m = size(varargin{2}, 2);
                    obj.states_ = sym('x', [n, 1]);

                    obj.f_ = varargin{1}*obj.states_;
                    obj.g_ = varargin{3}*obj.states_;

                    if (all(varargin{2} == 0) - m) ~= 0
                        obj.inputs_ = sym('u', [m, 1]);
                        obj.f_ = obj.f_ + varargin{2}*obj.inputs_;
                        obj.g_ = obj.g_ + varargin{4}*obj.inputs_;
                    end
                else
                    error('symss:invalidArguments', ...
                          'Invalid arguments to symss constructor.');
                end
            end
        end
    end

    % Utility methods.
    methods (Hidden)
        function varargout = getabcd(obj)
            %GETABCD Helper function to return state space matrices.
            nout = nargout;
            varargout{1} = obj.A;
            if nout > 1, varargout{2} = obj.B; end
            if nout > 2, varargout{3} = obj.C; end
            if nout > 3, varargout{4} = obj.D; end
        end
    end

    % Getters and setters.
    methods
        function obj = set.states(obj, varargin)
            % Set state variables for state-space model.
            validateattributes(varargin{:}, {'sym'}, {'vector'});
            obj.states_ = reshape(cell2sym(varargin), [], 1);
        end
        function obj = set.inputs(obj, varargin)
            % Set input variables for the state-space model.
            validateattributes(varargin{:}, {'sym'}, {'vector'});
            obj.inputs_ = reshape(cell2sym(varargin), [], 1);
        end

        function states = get.states(obj), states = obj.states_; end
        function inputs = get.inputs(obj), inputs = obj.inputs_; end

        function obj = set.f(obj, varargin)
            % Set state equation f(x)
            obj = privSetF(obj, varargin{:});
        end
        function obj = set.g(obj, varargin)
            % Set output equation g(x)
            obj = privSetG(obj, varargin{:});
        end

        function f = get.f(obj), f = privGetF(obj); end
        function g = get.g(obj), g = privGetG(obj); end

        function A = get.A(obj)
            A = privGetA(obj);
        end
        function B = get.B(obj)
            B = privGetB(obj);
        end
        function C = get.C(obj)
            C = privGetC(obj);
        end
        function D = get.D(obj)
            D = privGetD(obj);
        end

        function obj = set.Ts(obj, varargin)
            % Set sampling time Ts.
            validateattributes(varargin{:}, {'numeric'}, {'nonnegative'});
            obj.Ts_ = varargin{1};
        end

        function Ts = get.Ts(obj)
            Ts = obj.Ts_;
        end
    end

    % Overloaded operators.
    methods (Access = public)
        function obj = mtimes(obj, P)
            %MTIMES Operator overloading to implement similarity
            %transformation syntax.
            obj = symss2symss(obj, P);
        end

        function T = or(obj, expr)
            %OR Operator overloading to implement 'given that' syntax.
            a = assumptions;
            assume([expr{:}]);
            T = simplify(obj);
            assume([expr{:}], 'clear');
            assume(a);
        end
    end

    % Overloadable protected methods.
    methods (Access = protected)
        function obj = privSetF(obj, varargin)
            validateattributes(varargin{:}, {'sym'}, {'vector'});
            obj.f_ = formula(varargin{:});
        end
        function obj = privSetG(obj, varargin)
            validateattributes(varargin{:}, {'sym'}, {'vector'});
            obj.g_ = formula(varargin{:});
        end

        function f = privGetF(obj)
            f = reshape(obj.f_, [], 1);
        end
        function g = privGetG(obj)
            g = reshape(obj.g_, [], 1);
        end

        function A = privGetA(obj)
            [tx, tu, tf] = subvars(obj);
            A = jacobian(tf, tx);
            A = subs(A, [tx; tu], [obj.states_; obj.inputs_]);
        end
        function B = privGetB(obj)
            [tx, tu, tf] = subvars(obj);
            B = jacobian(tf, tu);
            B = subs(B, [tx; tu], [obj.states_; obj.inputs_]);
        end
        function C = privGetC(obj)
            [tx, tu, ~, tg] = subvars(obj);
            C = jacobian(tg, tx);
            C = subs(C, [tx; tu], [obj.states_; obj.inputs_]);
        end
        function D = privGetD(obj)
            [tx, tu, ~, tg] = subvars(obj);
            D = jacobian(tg, tu);
            D = subs(D, [tx; tu], [obj.states_; obj.inputs_]);
        end
    end
end
