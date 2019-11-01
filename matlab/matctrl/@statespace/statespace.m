classdef (SupportExtensionMethods = true) statespace < handle
    %STATESPACE Construct symbolic state-space model or convert model to
    %symbolic state-space.
    %
    %   sys = STATESPACE creates an empty state-space representation.
    %
    %   A state-space model is defined by state equations and output equations,
    %   given by:
    %
    %       dx/dt = f(t, x, u)
    %           y = g(t, x, u)
    %
    %   In order to define a state-space model, begin with an empty state space
    %   model, define states and inputs, and then define state equations and
    %   output equations.
    %
    %   sys = STATESPACE(A, B, C, D) Creates a state space model using the
    %   matrices A, B, C, D.
    %
    %       dx/dt = Ax(t) + Bx(t)
    %        y(t) = Cx(t) + Du(t)
    %
    %   A must be an nxn matrix, B must be an nxm matrix, and C must be a pxn
    %   matrix. If D is specified, it must be a pxm matrix.
    %
    %   sys = STATESPACE(states, inputs) creates a state space model using the
    %   state variables and input variables provided.
    %
    %   sys = STATESPACE(Ts) creates a discrete state space model with sampling
    %   time Ts.

    %   References:
    %   Antsaklis, Panos J., and Anthony N. Michel. A linear systems
    %   primer. Vol. 1. Boston: Birkhauser, 2007.

    properties (Access = protected, Hidden)
        % C Pointer Handle
        cobj_;
    end

    properties (Dependent)
        % State Variables
        states
        % Input Variables
        inputs
        % State Equations
        f
        % Ouput Equations
        g
    end

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

    methods
        function obj = statespace(varargin)
            obj.cobj_ = calllib('matctrl', 'ml_statespace_new');
        end

        function delete(obj)
            calllib('matctrl', 'ml_statespace_free', obj.cobj_);
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

            w = evalin('caller', 'whos');
            R = {w(strcmp('randomvar', {w.class})).name};

            for k = 1:numel(R)
                RV = evalin('caller', R{k});
                cptr = libpointer('stringPtrPtr', symctrl.mat2se(R{k}));

                calllib('matctrl', 'ml_statespace_random_variable_replace', ...
                        obj.cobj_, ...
                        cptr, ...
                        RV.cobj_);
            end
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

            w = evalin('caller', 'whos');
            R = {w(strcmp('randomvar', {w.class})).name};

            for k = 1:numel(R)
                RV = evalin('caller', R{k});
                cptr = libpointer('stringPtrPtr', symctrl.mat2se(R{k}));

                calllib('matctrl', 'ml_statespace_random_variable_replace', ...
                        obj.cobj_, ...
                        cptr, ...
                        RV.cobj_);
            end
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
