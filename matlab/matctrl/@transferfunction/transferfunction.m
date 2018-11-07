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
        Numerator
        % Denominator
        Denominator
        % Variable
        Variable
    end

    properties (Hidden, SetAccess = immutable, Dependent)
        tf
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
        function set.states(obj, s)
            s = symctrl.mat2se(s);

            calllib('matctrl', ...
                    'ml_statespace_states_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function states = get.states(obj)
            sz = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_states_get', ...
                    obj.cobj_, ...
                    cptr);

            states = symctrl.se2mat(cptr.Value);

            clear('cptr');
        end

        function set.inputs(obj, s)
            s = symctrl.mat2se(s);

            calllib('matctrl', ...
                    'ml_statespace_inputs_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function inputs = get.inputs(obj)
            sz = calllib('matctrl', 'ml_statespace_inputs_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_inputs_get', ...
                    obj.cobj_, ...
                    cptr);

            inputs = symctrl.se2mat(cptr.Value);

            clear('cptr');
        end

        function set.f(obj, s)
            s = symctrl.mat2se(s);

            calllib('matctrl', ...
                    'ml_statespace_f_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function f = get.f(obj)
            sz = calllib('matctrl', 'ml_statespace_f_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_f_get', ...
                    obj.cobj_, ...
                    cptr);

            f = symctrl.se2mat(cptr.Value);

            clear('cptr');
        end

        function set.g(obj, s)
            s = symctrl.mat2se(s);

            calllib('matctrl', ...
                    'ml_statespace_g_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function g = get.g(obj)
            sz = calllib('matctrl', 'ml_statespace_g_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_g_get', ...
                    obj.cobj_, ...
                    cptr);

            g = symctrl.se2mat(cptr.Value);

            clear('cptr');
        end

        function A = get.A(obj)
            n = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);

            c = cell(1, n^2);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_A_get', ...
                    obj.cobj_, ...
                    cptr);

            A = reshape(symctrl.se2mat(cptr.Value), n, n);

            clear('cptr');
        end

        function B = get.B(obj)
            n = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);
            m = calllib('matctrl', 'ml_statespace_inputs_size', obj.cobj_);

            c = cell(1, n*m);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_B_get', ...
                    obj.cobj_, ...
                    cptr);

            B = reshape(symctrl.se2mat(cptr.Value), n, m);

            clear('cptr');
        end

        function C = get.C(obj)
            n = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);
            p = calllib('matctrl', 'ml_statespace_g_size', obj.cobj_);

            c = cell(1, n*p);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_C_get', ...
                    obj.cobj_, ...
                    cptr);

            C = reshape(symctrl.se2mat(cptr.Value), p, n);

            clear('cptr');
        end

        function D = get.D(obj)
            m = calllib('matctrl', 'ml_statespace_inputs_size', obj.cobj_);
            p = calllib('matctrl', 'ml_statespace_g_size', obj.cobj_);

            c = cell(1, m*p);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_D_get', ...
                    obj.cobj_, ...
                    cptr);

            D = reshape(symctrl.se2mat(cptr.Value), p, m);

            clear('cptr');
        end
    end

end
