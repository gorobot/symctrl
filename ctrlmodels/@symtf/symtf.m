classdef (SupportExtensionMethods = true, InferiorClasses = {?sym}) symtf < ctrlmodel
    %SYMTF Construct symbolic transfer function or convert model to
    %symbolic transfer function.
    %
    %   G = SYMTF(expr)
    %   creates a transfer function using a symbolic expression. The
    %   symbolic expression should be a polynomial function of one of the
    %   variables {s, z, p, q}.
    %
    %   G = SYMTF(num, den) creates a transfer function with numerator and
    %   denominator 'num' and 'den'. 'num' and 'den' can be scalar arrays
    %   or symbolic arrays representing the coefficients of a polynomial or
    %   symbolic expressions.
    %
    %   G = SYMTF creates the transfer function G(s) = 1.

    % Transfer Function Properties
    properties (Access = public, Dependent)
        % Numerator
        Numerator
        % Denominator
        Denominator
        % Variable
        Variable
    end

    % Transfer Function
    properties (Hidden, SetAccess = immutable, Dependent)
        tf
    end

    % Internal Properties
    properties (Access = private)
        % Numerator
        num_ = cell.empty
        % Denominator
        den_ = cell.empty
        % Transfer Function Variable
        tfvar_ = sym.empty
    end

    % Constants
    properties (Access = private, Constant)
        allowed = {'s', 'z', 'p', 'q'}
    end

    methods
        function obj = symtf(varargin)
            %SYMTF Construct a symbolic transfer function.
            ni = nargin;

            % Quick copy.
            if ni == 1 && isa(varargin{1}, 'symtf')
                obj = varargin{1};
                return;
            end

            if ni ~= 0
                if ni == 1
                    arg = varargin{1};
                    if isa(arg, 'symss')
                        % Convert state-space to transfer function.
                        obj = symss2symtf(arg);
                    elseif ischar(arg)
                        % Symbolic variable.
                        validateattributes(arg, {'char'}, {'nonempty'});
                        if ~ismember(arg, obj.allowed)
                            error(['Variable must be one of ', ...
                                   '{%c %c %c %c}'], obj.allowed{:});
                        end

                        obj.tfvar_ = sym(arg);
                        obj.num_ = {obj.tfvar_};
                        obj.den_ = {sym(1)};

                    elseif isa(arg, 'sym')
                        validateattributes(arg, {'sym'}, {'scalar'});

                        V = obj.findvar(arg);
                        if ~isempty(V)
                            obj.tfvar_ = V;
                        else
                            obj.tfvar_ = sym('s');
                        end

                        obj.num_ = cell(size(arg));
                        obj.den_ = cell(size(arg));

                        [N, D] = numden(arg);
                        N = expand(N, 'ArithmeticOnly', true);
                        D = expand(D, 'ArithmeticOnly', true);
                        for k = 1:numel(N)
                            obj.num_{k} = coeffs(N(k), obj.tfvar_, 'All');
                            obj.den_{k} = coeffs(D(k), obj.tfvar_, 'All');
                        end
%                         elseif iscell(varargin{1})
%                             V = obj.findvar(varargin{1});
%                             if ~isempty(V)
%                                 obj.tfvar_ = V;
%                             else
%                                 obj.tfvar_ = sym('s');
%                             end
%
%                             obj.num_ = cell(size(varargin{1}));
%                             obj.den_ = cell(size(varargin{1}));
%
%                             for k = 1:numel(varargin{1})
%                                 obj.num_{k} = coeffs(N(k), obj.tfvar_, 'All');
%                                 obj.den_{k} = coeffs(D(k), obj.tfvar_, 'All');
%                             end
                    end
                elseif ni == 2
                    % Coefficients of numerator and denominator.
                    validateattributes(varargin{1}, ...
                        {'sym', 'numeric', 'cell'}, {'nonempty'});
                    validateattributes(varargin{2}, ...
                        {'sym', 'numeric', 'cell'}, {'nonempty'});
                    obj.tfvar_ = sym('s');
                    obj.Numerator = varargin{1};
                    obj.Denominator = varargin{2};
                end
            else
                % No input arguments.
                obj.tfvar_ = sym('s');
                obj.num_ = {sym(1)};
                obj.den_ = {sym(1)};
            end
        end
    end

    % Utility methods.
    methods (Hidden)
        function S = sym(obj)
            %SYM Helper function to allow functionality with sym class
            %functions.
            S = obj.tf;
        end
    end

    methods (Access = private)
        function Value = findvar(obj, s)
            %FINDVAR Finds the transfer function variable in the list of
            %allowed variables.
            if isempty(obj.tfvar_)
                S = symvar(s);
                m = find(ismember(obj.allowed, S), 1);
                Value = sym(obj.allowed(m));
            else
                Value = obj.tfvar_;
            end
        end
    end

    % Getters and Setters
    methods
        function Value = get.Numerator(obj)
            N = cell(size(obj.num_));
            for k = 1:numel(obj.num_)
                N{k} = poly2sym(obj.num_{k}, obj.tfvar_);
            end
            Value = cell2sym(N);
        end
        function Value = get.Denominator(obj)
            D = cell(size(obj.den_));
            for k = 1:numel(obj.den_)
                D{k} = poly2sym(obj.den_{k}, obj.tfvar_);
            end
            Value = cell2sym(D);
        end

        function obj = set.Numerator(obj, num)
            if isa(num, 'sym') && isscalar(num)
                obj.num_ = {coeffs(num, obj.tfvar_, 'All')};
            elseif ismatrix(num)
                obj.num_ = {sym(num)};
            else
                error('Invalid numerator.');
            end
        end
        function obj = set.Denominator(obj, den)
            if isa(den, 'sym') && isscalar(den)
                obj.den_ = {coeffs(den, obj.tfvar_, 'All')};
            elseif ismatrix(den)
                obj.den_ = {sym(den)};
            else
                error('Invalid numerator.');
            end
        end

        function Value = get.tf(obj)
            N = obj.Numerator;
            D = obj.Denominator;
            T = cell(size(obj.num_));
            for k = 1:numel(obj.num_)
                T{k} = N(k)/D(k);
            end
            Value = cell2sym(T);
        end

        function Value = get.Variable(obj), Value = obj.tfvar_; end

        function obj = set.Variable(obj, v)
            validateattributes(v, {'sym', 'char'}, {'scalar'});
            if isa(v, 'char')
                obj.tfvar_ = sym(v);
            else
                obj.tfvar_ = v;
            end
        end
    end

    % Overloaded operators.
    methods
        function C = plus(A, B)
            %PLUS Overloaded to allow for transfer functions to be added
            %without pole-zero cancellations.
            C = symtf;
            if ~isa(A, 'symtf')
                G = B;
                H = A;
            else
                G = A;
                H = B;
            end

            C.tfvar_ = G.tfvar_;

            if ~isa(H, 'symtf')
                if ~isa(H, 'sym')
                    H = sym(H);
                end

                [N, D] = numden(H);
                C.Numerator = G.Numerator*D + N*G.Denominator;
                C.Denominator = G.Denominator*D;
            else
                if G.tfvar_ ~= H.tfvar_
                    error('Transfer functions must have the same variable.');
                end
                C.Numerator = G.Numerator*H.Denominator + H.Numerator*G.Denominator;
                C.Denominator = G.Denominator*H.Denominator;
            end
        end

        function C = mtimes(A, B)
            %MTIMES Overloaded to allow for transfer functions to be
            %multiplied without pole-zero cancellations.
            C = symtf;
            if ~isa(A, 'symtf')
                G = B;
                H = A;
            else
                G = A;
                H = B;
            end

            C.tfvar_ = G.tfvar_;

            if ~isa(H, 'symtf')
                if ~isa(H, 'sym')
                    H = sym(H);
                end

                [N, D] = numden(H);
                C.Numerator = G.Numerator*N;
                C.Denominator = G.Denominator*D;
            else
                if G.tfvar_ ~= H.tfvar_
                    error('Transfer functions must have the same variable.');
                end
                C.Numerator = G.Numerator*H.Numerator;
                C.Denominator = G.Denominator*H.Denominator;
            end
        end

        function C = mrdivide(A, B)
            %MRDIVIDE Overloaded to allow for transfer functions to be
            %divided without pole-zero cancellations.
            C = symtf;
            if ~isa(A, 'symtf')
                G = B;
                G.Numerator = B.Denominator;
                G.Denominator = B.Numerator;
                H = A;
            else
                G = A;
                H = B;
            end

            C.tfvar_ = G.tfvar_;

            if ~isa(H, 'symtf')
                C.Numerator = G.Numerator;
                C.Denominator = G.Denominator*H;
            else
                if G.tfvar_ ~= H.tfvar_
                    error('Transfer functions must have the same variable.');
                end
                C.Numerator = G.Numerator*H.Denominator;
                C.Denominator = G.Denominator*H.Numerator;
            end
        end

        function C = mpower(A, B)
            %MPOWER Overloaded to allow for transfer functions to use the
            %matrix power operator without pole-zero cancellations.
            C = symtf;
            if ~isa(A, 'symtf')
                G = B;
                H = A;
            else
                G = A;
                H = B;
            end

            C.tfvar_ = G.tfvar_;

            if ~isa(H, 'symtf')
                C.Numerator = G.Numerator^H;
                C.Denominator = G.Denominator^H;
            else
                if G.tfvar_ ~= H.tfvar_
                    error('Transfer functions must have the same variable.');
                end

                C.Numerator = G.Numerator^H;
                C.Denominator = G.Denominator^H;
            end
        end
    end

end
