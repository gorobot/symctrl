classdef symopt < handle
    %SYMOPT Construct symbolic optimization model.
    %   
    %   opt = SYMOPT creates an empty symbolic optimization problem.
    %
    %   opt = SYMOPT(f, x) creates a symolic optimization problem of the
    %   form:
    %
    %   minimize    f(x)
    %       x
    %       s.t.    g(x)
    %
    %   Where f(x) is the objective function, g(x) is a constraint
    %   function, and x is the optimization variable.
    
    %   References:
    %   Boyd, Stephen, and Lieven Vandenberghe. Convex optimization.
    %   Cambridge university press, 2004.
    
    % Optimization variables.
    properties (Dependent)
        % Objective Function
        f
        % Optimization Variable
        vars
        % Constraint Functions
        st
    end
    
    % Hidden utility properties.
    properties (Dependent, Hidden)
        necon
        eqcon
    end
    
    % Internal properties.
    properties (Access = private)
        f_ = sym.empty
        
        vars_ = sym.empty
        
        st_ = sym.empty
    end
    
    % Constructor
    methods
        function obj = symopt(varargin)
            %SYMOPT Construct a symbolic optimization function.
            ni = nargin;
            
            % Quick copy of class.
            if ni == 1 && isa(varargin{1}, 'symopt')
                obj = varargin{1};
                return;
            end
            
            if ni ~= 0
                if isa(varargin{1}, 'sym')
                    args = obj.getvars(varargin{1});
                    
                    obj.f_ = formula(varargin{1});
                    
                    if ni > 1
                        vars = [varargin{2:end}];
                        if ~ismember(args, vars)
                            error(['Objective function must be a ', ...
                                   'function of the minimization ', ...
                                   'variable.']);
                        end
                        
                        obj.vars_ = vars;
                    else
                        obj.vars_ = args;
                    end
                else
                    error(['Objective function must be a ', ...
                          'symbolic expresion.']);
                end
            end
        end
    end
    
    % Internal utility methods.
    methods (Static, Access = private)
        function v = getvars(f)
            if isa(f, 'symfun')
                v = argnames(f);
            else
                v = symvar(f);
            end
        end
        
        function tf = isinequality(f)
            tf = arrayfun(@(x) contains(char(x), {'<', '>'}), f);
        end
    end
	
    % Getters and setters.
    methods
        function obj = set.f(obj, f)
            % Set the objective function.
            obj.f_ = formula(f);
        end
        
        function obj = set.vars(obj, vars)
            % Set the optimization variable.
            vars = reshape(vars, 1, []);
            if ~ismember(vars, obj.getvars(obj.f))
                error('Variable must be a parameter of f.');
            end
            obj.vars_ = vars;
        end
        
        function obj = set.st(obj, st)
            % Set the constraint functions.
            if ~any(arrayfun(@(x) contains(char(x), ...
                    {'<', '>', '<=', '>=', '==', '~='}), st))
                error('Constraint must be a symbolic expression.');
            else
                bl = arrayfun(@(x) contains(char(x), ...
                    {'&', '|'}), st);
                if any(bl)
                    st = [st(~bl); cell2sym({children(st(bl)).'})];
                end
            end
            obj.st_ = reshape(st, [], 1);
        end
        
        function f = get.f(obj)
            f = obj.f_;
        end
        function vars = get.vars(obj)
            vars = obj.vars_;
        end
        function st = get.st(obj)
            st = obj.st_;
        end
        
        function necon = get.necon(obj)
            eq = obj.isinequality(obj.st);
            necon = obj.st(eq);
        end
        function eqcon = get.eqcon(obj)
            eq = ~obj.isinequality(obj.st);
            eqcon = obj.st(eq);
        end
    end
end

