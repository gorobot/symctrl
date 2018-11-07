classdef (SupportExtensionMethods = true) hybridsystem < handle
    %HYBRIDSYSTEM Construct symbolic hybrid state-space model.
    %
    %   hsys = HYBRIDSYSTEM creates an empty hybrid state-space representation.
    %
    %   A hybrid state-space model is defined by both continuous and discrete
    %   dynamics along with switching conditions and an adjacency matrix.
    %
    %   Define system dynamics by specifying the state equations for each mode.
    %   The first index corresponds to the dynamics of a mode. The second index
    %   defines the equation in the dynamics. For example,
    %                              .
    %       f(1, 3) corresponds to x3 = f3(t, x, u) in mode 1.
    %
    %   The conditions are specified as an inequality matrix, indicating the
    %   guard condition for switching to a new mode. For example,
    %
    %       guard(1, 2) = x < 0 switches from mode 1 to mode 2 when x >= 0.
    %
    %   Discontinuous jump states can be specified by setting the guard
    %   condition along the main diagonal to 0 for the mode. Any nonzero numeric
    %   values along the main diagonal are considered continuous. For example,
    %
    %       guard(1, 1) = 1 specifies that mode 1 is continuous.
    %       guard(2, 2) = 0 specifies that mode 2 is discontinuous.
    %
    %   Additionally, the adjacency matrix defines the modes which are available
    %   from the current mode. For example,
    %
    %       edge(1, 2) = 1 means the system is allowed switch to mode 2 from
    %       mode 1.
    %
    %   By default, all edges are enabled.
    %
    %   If a condition is specified for a specific transition, it also modifies
    %   the adjacency matrix to allow for the transition.
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
    %   See also statespace

    %   References:
    %   Van Der Schaft, Arjan J., and Johannes Maria Schumacher. An introduction
    %   to hybrid dynamical systems. Vol. 251. London: Springer, 2000.
    %
    %   Goebel, Rafal, Ricardo G. Sanfelice, and Andrew R. Teel. "Hybrid
    %   dynamical systems." IEEE Control Systems 29.2 (2009): 28-93.
    %
    %   Savkin, Andrey V., and Robin J. Evans. Hybrid dynamical systems:
    %   controller and sensor switching problems. Springer Science & Business
    %   Media, 2002.

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

        % Guard Conditions
        % The elements of the guard matrix are the guard conditions for
        % staying in a current mode.
        guard

        % Adjacency Matrix
        % The elements of the adjacency matrix represent the availability
        % of switching to another mode.
        edge
    end

    methods
        function obj = hybridsystem(varargin)
            obj.cobj_ = calllib('matctrl', 'ml_hybridsystem_new');
        end

        function delete(obj)
            calllib('matctrl', 'ml_hybridsystem_free', obj.cobj_);
        end
    end

    methods
        % TODO: Fix function access for hybrid system.
        function varargout = subsref(obj, S)
            if strcmp(S(1).type, '.') && strcmp(S(1).subs, 'f')
                if numel(S) == 1
                    error('Not enough input arguments.');
                end

                idx = S(2).subs;
                varargout = {privGetF(obj, idx)};

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
