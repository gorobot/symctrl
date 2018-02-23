classdef symss < matlab.mixin.CustomDisplay
    %SYMSS Construct symbolic state-space model or convert model to 
    %symbolic state-space.
    %
    %   Detailed explanation goes here
    
    properties
        % State matrix A
        A
        % Input matrix B
        B
        % Output matrix C
        C
        % Feed-forward matrix D
        D
    end
    
    properties (Access = public, Dependent)
        % State equations.
        f
        % Ouput equations.
        g
    end
    
    methods
        function obj = symss(varargin)
            %SYMSS Construct an instance of this class
            %   Detailed explanation goes here
            ni = nargin;
            
            if ni == 1 
                switch class(varargin{1})
                    case 'symss'
                        sys = varargin{1};

                        obj.A = sys.A;
                        obj.B = sys.B;
                        obj.C = sys.C;
                        obj.D = sys.D;
                        
                    case 'symsv'
                        sv = varargin{1};

                        % Compute the jacobians, A, B, C, and D.
                        f = rhs(sv.Dx);
                        g = rhs(sv.y);
                        x = lhs(sv.x);
                        u = lhs(sv.u);

                        obj.A = jacobian(f, x);
                        obj.B = jacobian(f, u);
                        obj.C = jacobian(g, x);
                        obj.D = jacobian(g, u);
                        
                        % The reason we convert all of the state variables
                        % into the x vector contained within the state
                        % variable class is so that we can compute the
                        % jacobians using this method. Once we have
                        % computed the jacobians, we can convert back to
                        % the initial variables.

                        % Probably need more symbolic substitutions here. 
                        obj.A = subs(obj.A, [lhs(sv.x), lhs(sv.u)], [rhs(sv.x), rhs(sv.u)]);
                        obj.B = subs(obj.B, [lhs(sv.x), lhs(sv.u)], [rhs(sv.x), rhs(sv.u)]);
                        obj.C = subs(obj.C, [lhs(sv.x), lhs(sv.u)], [rhs(sv.x), rhs(sv.u)]);
                        obj.D = subs(obj.D, [lhs(sv.x), lhs(sv.u)], [rhs(sv.x), rhs(sv.u)]);
                        
                    otherwise
                        error('Class type is not supported.');
                end
                
            elseif ni == 4
                for k = 1:ni
                    if ~isa(varargin{k}, 'sym')
                        varargin{k} = sym(varargin{k});
                    end
                end
                
                A = varargin{1};
                B = varargin{2};
                C = varargin{3};
                D = varargin{4};

                % Ensure the matrices have the correct dimensions. 
                if size(A, 1) ~= size(A, 2)
                    error('A should be square.');
                end
                [n, ~] = size(A);
                if size(B, 1) ~= n
                    error('B has insufficient rows.');
                end
                if size(C, 2) ~= n
                    error('C has insufficient columns.');
                end
                [~, m] = size(B);
                [p, ~] = size(C);
                if isscalar(D)
                    D = sym(D*ones(p, m));
                end
                if size(D, 1) ~= p && size(D, 2) ~= m
                    error('D is not the correct size.')
                end
                
                obj.A = A;
                obj.B = B;
                obj.C = C;
                obj.D = D;
                
            end
            
            % Simplify the matrices to avoid unnecessary length. The
            % simplified matrices should be equivalent.
            obj.A = simplify(obj.A);
            obj.B = simplify(obj.B);
            obj.C = simplify(obj.C);
            obj.D = simplify(obj.D);
            
        end
        
        function Value = get.f(obj)
            syms t
            x = sym('x', [size(obj.A, 2), 1]);
            u = sym('u', [size(obj.B, 2), 1]);
            fun = obj.A*x + obj.B*u;
            
            for k = 1:numel(fun)
                fn = symfun(fun(k), [t, x.', u.']);
                Value{k} = fn;
            end
        end
        
        function Value = get.g(obj)
            syms t
            x = sym('x', [size(obj.C, 2), 1]);
            u = sym('u', [size(obj.D, 2), 1]);
            fun = obj.C*x + obj.D*u;
            
            for k = 1:numel(fun)
                fn = symfun(fun(k), [t, x.', u.']);
                Value{k} = fn;
            end
        end
        
        function obj = mtimes(obj, P)
            %MTIMES Operator overloading to implement similarity
            %transformation syntax.
            obj = simtrans(obj, P);
        end
        
    end
    
    methods (Access = protected)
        function header = getHeader(obj)
            if ~isscalar(obj)
                header = getHeader@matlab.mixin.CustomDisplay(obj);
            else
                headerStr = matlab.mixin.CustomDisplay.getClassNameForHeader(obj);
                headerStr = ['Symbolic state space ', headerStr, ' with properties:'];
                header = sprintf('%s\n',headerStr);
            end
        end
   
        function propgrp = getPropertyGroups(obj)
            if ~isscalar(obj)
                propgrp = getPropertyGroups@matlab.mixin.CustomDisplay(obj);
            else
                propList1 = struct('A', obj.A, 'B', obj.B, ...
                                   'C', obj.C, 'D', obj.D);
                % propList2 = struct('f', obj.f, 'g', obj.g);
                
                propgrp(1) = matlab.mixin.util.PropertyGroup(propList1);
                % propgrp(2) = matlab.mixin.util.PropertyGroup(propList2);
            end
        end
    end
end

