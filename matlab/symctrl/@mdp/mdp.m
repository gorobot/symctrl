classdef (SupportExtensionMethods = true) mdp < handle

    properties (Access = protected, Hidden)
        % C Pointer Handle
        cobj_;
    end

    properties (Dependent)
        % Numer of states.
        X
        % Number of inputs.
        U

        % Transition probability matrix.
        P
        % Reward matrix.
        R

        % Discount factor.
        gamma
    end

    methods
        function obj = mdp(varargin)
            obj.cobj_ = calllib('matctrl', 'ml_mdp_new');
        end

        function delete(obj)
            calllib('matctrl', 'ml_mdp_free', obj.cobj_);
        end
    end

    methods
        function set.X(obj, n)
            validateattributes(n, {'numeric'}, {'scalar'});
            calllib('matctrl', 'ml_mdp_set_num_states', obj.cobj_, n);
        end

        function set.U(obj, n)
            validateattributes(n, {'numeric'}, {'scalar'});
            calllib('matctrl', 'ml_mdp_set_num_inputs', obj.cobj_, n);
        end

        function set.gamma(obj, gamma)
            validateattributes(gamma, {'numeric'}, {'scalar'});
            calllib('matctrl', 'ml_mdp_set_gamma', obj.cobj_, gamma);
        end

        function X = get.X(obj)
            X = calllib('matctrl', 'ml_mdp_get_num_states', obj.cobj_);
        end

        function U = get.U(obj)
            U = calllib('matctrl', 'ml_mdp_get_num_inputs', obj.cobj_);
        end

        function gamma = get.gamma(obj)
            gamma = calllib('matctrl', 'ml_mdp_get_gamma', obj.cobj_);
        end

    end
end
