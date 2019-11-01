classdef (SupportExtensionMethods = true, InferiorClasses = {?sym}) transferfunction < handle
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

    properties (Access = protected, Hidden)
        % C Pointer Handle
        cobj_;
    end

    properties (Dependent)
        % Numerator
        num
        % Denominator
        den
        % Variable
        var
    end

    % Transfer Function
    properties (Hidden, SetAccess = immutable, Dependent)
        tf
    end

    % Constants
    properties (Access = private, Constant)
        allowed = {'s', 'z', 'p', 'q'}
    end

    methods
        function obj = transferfunction(varargin)
            obj.cobj_ = calllib('matctrl', 'ml_transferfunction_new');
        end

        function delete(obj)
            calllib('matctrl', 'ml_transferfunction_free', obj.cobj_);
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

    methods
        function set.var(obj, s)
            s = symctrl.mat2se(s);

            calllib('matctrl', ...
                    'ml_transferfunction_var_set', ...
                    obj.cobj_, ...
                    s);
        end

        function var = get.var(obj)
            c = cell(1);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_transferfunction_var_get', ...
                    obj.cobj_, ...
                    cptr);

            var = symctrl.se2mat(cptr.Value);

            clear('cptr');
        end

        function set.num(obj, s)
            s = symctrl.mat2se(s);

            calllib('matctrl', ...
                    'ml_transferfunction_num_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function num = get.num(obj)
            sz = calllib('matctrl', 'ml_transferfunction_num_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_transferfunction_num_get', ...
                    obj.cobj_, ...
                    cptr);

            num = symctrl.se2mat(cptr.Value);

            clear('cptr');
        end

        function set.den(obj, s)
            s = symctrl.mat2se(s);

            calllib('matctrl', ...
                    'ml_transferfunction_den_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function den = get.den(obj)
            sz = calllib('matctrl', 'ml_transferfunction_den_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_transferfunction_den_get', ...
                    obj.cobj_, ...
                    cptr);

            den = symctrl.se2mat(cptr.Value);

            clear('cptr');
        end
    end

    % Overloaded operators.
    methods
        function C = plus(A, B)
            %PLUS Overloaded to allow for transfer functions to be added
            %without pole-zero cancellations.
            C = transferfunction();
            if ~isa(A, 'transferfunction')
                G = B;
                H = A;
            else
                G = A;
                H = B;
            end

            C.var = G.var;

            if ~isa(H, 'transferfunction')
                if ~isa(H, 'sym')
                    H = sym(H);
                end

                [N, D] = numden(H);
                C.num = G.num*D + N*G.den;
                C.den = G.den*D;
            else
                if G.var ~= H.var
                    error('Transfer functions must have the same variable.');
                end
                C.num = G.num*H.den + H.num*G.den;
                C.den = G.den*H.den;
            end
        end

        function C = mtimes(A, B)
            %MTIMES Overloaded to allow for transfer functions to be
            %multiplied without pole-zero cancellations.
            C = transferfunction();
            if ~isa(A, 'transferfunction')
                G = B;
                H = A;
            else
                G = A;
                H = B;
            end

            C.var = G.var;

            if ~isa(H, 'transferfunction')
                if ~isa(H, 'sym')
                    H = sym(H);
                end

                [N, D] = numden(H);
                C.num = G.num*N;
                C.den = G.den*D;
            else
                if G.var ~= H.var
                    error('Transfer functions must have the same variable.');
                end
                C.num = G.num*H.num;
                C.den = G.den*H.den;
            end
        end

        function C = mrdivide(A, B)
            %MRDIVIDE Overloaded to allow for transfer functions to be
            %divided without pole-zero cancellations.
            C = transferfunction();
            if ~isa(A, 'transferfunction')
                G = B;
                G.num = B.den;
                G.den = B.num;
                H = A;
            else
                G = A;
                H = B;
            end

            C.var = G.var;

            if ~isa(H, 'transferfunction')
                C.num = G.num;
                C.den = G.den*H;
            else
                if G.var ~= H.var
                    error('Transfer functions must have the same variable.');
                end
                C.num = G.num*H.den;
                C.den = G.den*H.num;
            end
        end

        function C = mpower(A, B)
            %MPOWER Overloaded to allow for transfer functions to use the
            %matrix power operator without pole-zero cancellations.
            C = transferfunction();
            if ~isa(A, 'transferfunction')
                G = B;
                H = A;
            else
                G = A;
                H = B;
            end

            C.var = G.var;

            if ~isa(H, 'transferfunction')
                C.num = G.num^H;
                C.den = G.den^H;
            else
                if G.var ~= H.var
                    error('Transfer functions must have the same variable.');
                end

                C.num = G.num^H;
                C.den = G.den^H;
            end
        end
    end
end
