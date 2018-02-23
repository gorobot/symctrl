classdef symsv < matlab.mixin.CustomDisplay
    %SYMSV Construct symbolic state variable model or convert model to
    % symbolic state variables.
    %
    %   Detailed explanation goes here
    
    properties
        % State variables.
        x
        % Derivative of state variables.
        Dx
        % Input variables.
        u
        % Output variables.
        y
    end
    
    properties (Access = public, Dependent)
        % State equations.
        f
        % Ouput equations.
        g
        % System type.
        Type
    end
    
    properties (Access = protected)
        % System type.
        Type_
    end
    
    methods
        function obj = symsv(f, g, varargin)
            %SYMSV Construct an instance of this class
            %   Detailed explanation goes here
            ni = nargin;
            
            p = inputParser;
            validateStates = @(arg) validateattributes(arg, {'cell'}, {'nonempty'});
            validateInputs = @(arg) validateattributes(arg, {'cell'}, {'nonempty'});
            validateOutputs = @(arg) validateattributes(arg, {'cell'}, {'nonempty'});

            addRequired(p, 'f');
            addOptional(p, 'g', {});
            
            addParameter(p, 'States', {}, validateStates);
            addParameter(p, 'Inputs', {}, validateInputs);
            addParameter(p, 'Outputs', {}, validateOutputs);
            
            addParameter(p, 'vars', {});
            
            parse(p, f, g, varargin{:});
            
            f = cell2sym(f);
            g = cell2sym(g);
            
            States = p.Results.States;
            Inputs = p.Results.Inputs;
            Outputs = p.Results.Outputs;
            
%             [states, inputs, outputs] = getStates(f);
            
%             % If the state variables are not defined, use the variables
%             % defined in the equations.
%             if isempty(p.Results.states)
%                 % states = symvar(lhs(f)).';
%                 
%                 [eqns, vars] = getSymbolicFunctions(f);
%             else
%                 states = p.Results.states;
%             end
%             
%             if isempty(p.Results.inputs)
% %                 inputs = symvar(rhs(f)).';
%             else
%                 inputs = p.Results.inputs;
%             end
%             
%             if isempty(p.Results.outputs)
% %                 outputs = symvar(lhs(g)).';
%             else
%                 outputs = p.Results.outputs;
%             end
            
            % Needed for differentiation w/rt 't'.
            syms t
            
            % Convert cell array to array of symbolic functions.
            States = cell2sym(States).';
            Inputs = cell2sym(Inputs).';
            Outputs = cell2sym(Outputs).';
            
            % Initialize the state variables.
            obj.x = sym('x', [numel(States), 1]);
            obj.Dx = sym('Dx', [numel(States), 1]);
            obj.u = sym('u', [numel(Inputs), 1]);
            obj.y = sym('y', [numel(Outputs), 1]);
            
            % Get the preliminary state equations.
            isox = States == obj.x;
            nodiffvars = States(~has(States, {'diff'}));
            
            % Get the derivatives of the state variables.
            isodx = diff(States(:));
            
            for k = 1:numel(States)
                % Check if the current derivative is one of the state
                % variables.
                index = has(States, isodx(k));
                
                % If it is one of the state variables, we set the
                % derivative equation equal to the matching state variable.
                if nnz(index) ~= 0
                    isox(index) = isolate(isox(index), isodx(k));
                    obj.Dx(k) = obj.Dx(k) == rhs(isox(index));
                else
                    % If the system is a differential algebraic equation,
                    % we need to check the differential order of the
                    % equations and separate them into one equation per
                    % higher-order derivative.
                    [rF, rV, R] = reduceDifferentialOrder(f, nodiffvars);
                    % Once the equations are reduced, we can substitute the
                    % variables back into the equations.
                    f = subs(rF, R(:,1), R(:,2)) == 0;

                    for n = 1:numel(f)
                        try
                            obj.Dx(k) = obj.Dx(k) == rhs(isolate(f(n), diff(States(k))));
                            % If the equation is solvable for the variable,
                            % end the for loop, using the first equation
                            % that is solvable for the variable of
                            % interest.
                            break
                        catch ME
                            % If the equation is not solvable for the
                            % variable, catch the error and continue on to
                            % the next equation.
                            switch ME.identifier
                                case 'symbolic:solve:EquationUnsolvableFor'
                                    % Potentially display a warning.
                                    % warning('Equation not solvable for variable.')
                                otherwise
                                    rethrow(ME)
                            end
                            % If the variable of interest is not solvable
                            % in the current set of equations, throw an
                            % error.
                            if n == numel(f)
                                warning(['The variable ', obj.Dx(k), ' is not solvable in the current set of equations.'])
                            end
                        end
                    end
                end
            end
            
            % Cycle through the output equations and solve for the given
            % output variable. In a simple case, the output equations could
            % be formatted:
            % y == x1 + x2
            % This means the output variable is y. 
            for k = 1:numel(Outputs)
                for n = 1:numel(g)
                    try
                        obj.y(k) = obj.y(k) == rhs(isolate(g(n), Outputs(k)));
                        break
                    catch ME
                        switch ME.identifier
                            case 'symbolic:solve:EquationUnsolvableFor'
                                % Potentially display a warning.
                                % warning('Equation not solvable for variable.')
                            otherwise
                                rethrow(ME)
                        end
                    end
                end
            end
            
            % Once we have the Dx vector containing the differentiated
            % state variables, we can substitute the x vector into the
            % right-hand side of Dx, which are the functions f_i(x).
            obj.Dx = lhs(obj.Dx) == subs(rhs(obj.Dx), lhs(isox), rhs(isox));
            obj.Dx = lhs(obj.Dx) == subs(rhs(obj.Dx), Inputs, obj.u);
            
            obj.y = lhs(obj.y) == subs(rhs(obj.y), lhs(isox), rhs(isox));
            obj.y = lhs(obj.y) == subs(rhs(obj.y), Inputs, obj.u);
            
            
            % Check if state equations contain derivatives on the rhs. If
            % so, this set of state variables is not allowable.
            if nnz(has(obj.Dx, {'diff'})) ~= 0
                error('Dx has derivatives in the RHS.');
            end
            
            % Set the states for x variables.
            for k = 1:numel(States)
                obj.x(k) = obj.x(k) == States(k);
            end
            
            % Set the states for u variables.
            for k = 1:numel(Inputs)
                obj.u(k) = obj.u(k) == Inputs(k);
            end
        end
        
        function Value = get.f(obj)
            syms t
            
%             x = lhs(obj.x);
%             u = lhs(obj.u);
%             Value = sym('f', [numel(sv.Dx), 1]);
%             Value = empty(numel(sv.Dx), 1);
%             Value = zeros(numel(sv.Dx), 1);
%             Value = sym(Value);
            % Value = symfun(subs(rhs(sv.Dx), [lhs(sv.x), lhs(sv.u)], [rhs(sv.x), rhs(sv.y)]), [t, lhs(sv.x), lhs(sv.u)]);
            
%             Value = symfun(rhs(obj.Dx), ...
%                 intersect(symvar(rhs(obj.Dx)), [t, lhs(obj.x).', lhs(obj.u).']));
            for k = 1:numel(obj.Dx)
%                 fn = symfun(rhs(obj.Dx(k)), [t, lhs(obj.x).', lhs(obj.u).']);
                fn = symfun(rhs(obj.Dx(k)), [t, lhs(obj.x).', lhs(obj.u).']);
                Value{k} = fn;
            end
        end
        
        function Value = get.g(obj)
            syms t
            Value = sym('g', [numel(obj.y), 1]);
            % Value = symfun(subs(rhs(sv.Dx), [lhs(sv.x), lhs(sv.u)], [rhs(sv.x), rhs(sv.y)]), [t, lhs(sv.x), lhs(sv.u)]);
            
            Value = symfun(rhs(obj.y), [t, lhs(obj.x).', lhs(obj.u).']);
%             for k = 1:numel(sv.Dx)
%                 Value(k) = symfun(rhs(sv.Dx(k)), [t, lhs(sv.x).', lhs(sv.u).']);
%             end
        end
    end
    
    methods (Access = protected)
        function header = getHeader(obj)
            if ~isscalar(obj)
                header = getHeader@matlab.mixin.CustomDisplay(obj);
            else
                headerStr = matlab.mixin.CustomDisplay.getClassNameForHeader(obj);
                headerStr = ['Symbolic state variables ', headerStr, ' with properties:'];
                header = sprintf('%s\n',headerStr);
            end
        end
   
        function propgrp = getPropertyGroups(obj)
            if ~isscalar(obj)
                propgrp = getPropertyGroups@matlab.mixin.CustomDisplay(obj);
            else
                propList1 = struct('x', obj.x, 'Dx', obj.Dx, ...
                                   'u', obj.u, 'y', obj.y);
                % propList2 = struct('f', obj.f, 'g', obj.g);
                
                propgrp(1) = matlab.mixin.util.PropertyGroup(propList1);
                % propgrp(2) = matlab.mixin.util.PropertyGroup(propList2);
            end
        end
    end
end
